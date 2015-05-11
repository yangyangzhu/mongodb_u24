#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <unistd.h>
#include <iomanip>
#include <cstdlib> 
#include <ctime>
#include <chrono>

#include "BoundaryFix.h"
#include "resquecommon.h"
#include "statistics.h"

#include <opencv/highgui.h>
#include <opencv/cv.h>

using namespace std;
using namespace cv;

GeometryFactory *gf = NULL;
WKTReader *wkt_reader = NULL;
map<int, std::vector<Geometry*> > polydata;
map<int, map<int, std::vector<const Geometry*> > > tile_poly;
map<int, Geometry*> geom_tiles;
map<int, string> tile_str;
IStorageManager * storage = NULL;
ISpatialIndex * spidx = NULL;
map<int, vector<double> > report_stat;
Jacc_object_cal * jacc_cal = NULL;
Dice_object_cal * dice_cal = NULL;
Dice_tile_cal * dice_tile_cal = NULL;

double min_x = LONG_MAX, max_x = -1, min_y = LONG_MAX, max_y = -1;
int poly_count[2];

void processBoundaryObject(stringstream &instream, int filenumber) {
    string line;
    Geometry *geom = NULL;
    while (instream.good()){
	getline(instream, line, '\n');
	if (!line.empty()) {
	    //cout << line << endl;
            if (line.length() < 2) 
                continue;
            geom = wkt_reader->read(line);
            polydata[filenumber].push_back(geom);
            const Envelope *env = geom->getEnvelopeInternal();

            min_x = min(min_x, env->getMinX());
            min_y = min(min_y, env->getMinY());
            max_x = max(max_x, env->getMaxX()); 
            max_y = max(max_y, env->getMaxY());

            ++poly_count[filenumber-1];
	}
    }
}

/* The first parameter is the filename,
 * the second parameter is optional, if there is a 2nd argument,
 *     the program will perform the boundary fixing/correction.
 */
void getPolygons(char** argv) {
    string line;
    Mat inputImg; /* InputImg */

    /* Read the input mask */
    int filenumber = 0;
    while (filenumber < 2) {
        ++filenumber;
          
        stringstream tmpInStream;
        stringstream tmpOutStream; 
        stringstream finalOutStream;
	  
        inputImg = imread(argv[filenumber], CV_8UC1);
        if (inputImg.data > 0) {
            Mat temp = Mat::zeros(inputImg.size() + Size(2,2), inputImg.type());
            copyMakeBorder(inputImg, temp, 1, 1, 1, 1, BORDER_CONSTANT, 0);

	    std::vector<std::vector<cv::Point> > contours;
	    std::vector<Vec4i> hierarchy;

	    /* Find the contour / boundary of nuclei */
	    findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);
		
	    int counter = 1;
	    if (contours.size() > 0) {
		for (int idx = 0; idx >= 0; idx = hierarchy[idx][0]) {
		    tmpInStream << idx << ": ";
		    for (unsigned int ptc = 0; ptc < contours[idx].size(); ++ptc) {
		        tmpInStream << SPACE << contours[idx][ptc].x << COMMA <<  contours[idx][ptc].y;
		    }
		    tmpInStream << endl;
	        }
	        ++counter;
	    }
	    /* Clear the stream (reset eof and etc.) */
	    tmpInStream.clear();
		
            processBoundaryFixing(tmpInStream, tmpOutStream);
	    tmpOutStream.clear();
	    /* Output the result from boundary fix 2 to std output */
	    processBoundaryFixing2(tmpOutStream, finalOutStream);
	    //finalOutStream.clear();
	    /* Handle the boundary objects and output them to std output  */
            processBoundaryObject(finalOutStream, filenumber);
        }
    } 
}

void releaseData(int k)
{
  if (k <= 0)
    return;
  for (int j = 0; j < k; j++) {
    int delete_index = j+1;
    int len = polydata[delete_index].size();

    for (int i = 0; i < len ; i++)
      delete polydata[delete_index][i];

    polydata[delete_index].clear();
  }

  map<int, Geometry*>::iterator iter;
  for (iter = geom_tiles.begin(); iter != geom_tiles.end(); ++iter) 
    delete iter->second;
  
  delete wkt_reader;
  delete gf;
  delete jacc_cal;
  delete dice_cal;
  delete dice_tile_cal;

  //delete storage;
  //delete spidx;
}

void genTiles(int tile_size) {
  
  int count = 1;
  for (int i = min_x; i <= max_x; i += tile_size) {
    for (int j = min_y; j <= max_y; j += tile_size) {
      stringstream ss;
      ss << shapebegin << i << SPACE << j << COMMA
         << i << SPACE << j+tile_size << COMMA
         << i+tile_size << SPACE << j+tile_size << COMMA
         << i+tile_size << SPACE << j << COMMA
         << i << SPACE << j << shapeend;
      //cout << ss.str() << endl;
      stringstream ss2;
      ss2 << i << SPACE << j << SPACE << i+tile_size << SPACE << j+tile_size;
      geom_tiles[count]= wkt_reader->read(ss.str());
      tile_str[count] = ss2.str();
      ++count;
    }
  }
}

bool buildIndex() {
    id_type indexIdentifier;
    GEOSDataStream stream(&geom_tiles);
    storage = StorageManager::createNewMemoryStorageManager();
    spidx = RTree::createAndBulkLoadNewRTree(RTree::BLM_STR, stream, *storage,
            FillFactor,
            IndexCapacity,
            LeafCapacity,
            2,
            RTree::RV_RSTAR, indexIdentifier);
    return spidx->isIndexValid();
}


void doQuery(Geometry* poly) {
    double low[2], high[2];
    const Envelope * env = poly->getEnvelopeInternal();

    low [0] = env->getMinX();
    low [1] = env->getMinY();

    high [0] = env->getMaxX();
    high [1] = env->getMaxY();

    Region r(low, high, 2);
    hits.clear();

    MyVisitor vis ;
    spidx->intersectsWithQuery(r, vis);
}

void partitionData() {
    int tid;
    for (int i = 1; i < 3; ++i) {
        int count = polydata[i].size();
        for (int j = 0; j < count; ++j) {
            doQuery(polydata[i][j]);
            for (int k = 0; k < hits.size(); ++k) {
                tid = hits[k];
                tile_poly[tid][i].push_back(polydata[i][j]);
            }
        }
    }    
    /*
    map<int, map<int, vector<Geometry*> > >::iterator itr1;
    map<int, vector<Geometry*> >::iterator itr2;
    for (itr1 = tile_poly.begin(); itr1 != tile_poly.end(); itr1++) {
        for (itr2 = (itr1->second).begin(); itr2 != (itr1->second).end(); itr2++) {
            cout << itr1->first << " " << itr2->first << " " << itr2->second.size() << endl;
        }
    }*/
}

void spatialJoin() {
    bool flag;
    map<int, map<int, vector<const Geometry*> > >::iterator itr1;
    
    for (itr1 = tile_poly.begin(); itr1 != tile_poly.end(); itr1++) {
        map<int, vector<const Geometry*> > poly_data = itr1->second; 
        int join_pairs = 0;
        double jacc_val = 0.0 ,dice_val = 0.0;
        
        report_stat[itr1->first].push_back(dice_tile_cal->calculate(poly_data[1], poly_data[2]));
      
        for (int i = 0; i < poly_data[1].size(); ++i) {
            const Geometry* geo1 = poly_data[1][i];
            const Envelope * en1 = geo1->getEnvelopeInternal();

            for (int j = 0; j < poly_data[2].size(); ++j) {
                const Geometry* geo2 = poly_data[2][j];
                const Envelope * en2 = geo2->getEnvelopeInternal();
                flag = en1->intersects(en2) && geo1->intersects(geo2);
                if (flag) {
                    ++join_pairs;
                    std::vector<const Geometry*> g1, g2;
                    g1.push_back(geo1);
                    g2.push_back(geo2);
                    jacc_val += jacc_cal->calculate(g1,g2);
                    dice_val += dice_cal->calculate(g1,g2);
                }
            }
        }
        if (join_pairs > 0) {
            report_stat[itr1->first].push_back(jacc_val/(double)join_pairs);     
            report_stat[itr1->first].push_back(dice_val/(double)join_pairs);
        } else {
            report_stat[itr1->first].push_back(0.0);
            report_stat[itr1->first].push_back(0.0);
        }
    }
    map<int, vector<double> >::iterator itr;
    for (itr = report_stat.begin(); itr != report_stat.end(); ++itr) {
        cout << itr->first << TAB << tile_str[itr->first] << TAB;
        cout << (itr->second)[0] << TAB << (itr->second)[1] << TAB << (itr->second)[2] <<endl;
    }
}

int main (int argc, char **argv){   

    std::chrono::time_point<std::chrono::system_clock> start, s, end;
    start = std::chrono::system_clock::now();
    s = start;

    // initlize the GEOS ibjects    
    gf = new GeometryFactory(new PrecisionModel(),OSM_SRID);
    wkt_reader= new WKTReader(gf);
    //
    jacc_cal = new Jacc_object_cal();
    dice_cal = new Dice_object_cal();
    dice_tile_cal = new Dice_tile_cal();

    getPolygons(argv);
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cerr << min_x << " " << min_y << " " << max_x << " " << max_y << " " <<poly_count[0] << " " << poly_count[1] <<endl;
    std::cerr << "Mask processing time: " << elapsed_seconds.count() << "s\n";    

    start = std::chrono::system_clock::now();

    genTiles(std::atoi(argv[3]));
    if (!buildIndex()) {
      cerr << "Build index failed! "<< endl;
      return -1;
    } else {
      cerr << "Build index succeeded." << endl;
    }
    partitionData();
    end = std::chrono::system_clock::now();
    elapsed_seconds = end-start;
    std::cerr << "Build indexing and partition data time: " << elapsed_seconds.count() << "s\n";    
    
    start = std::chrono::system_clock::now();
    spatialJoin();
    end = std::chrono::system_clock::now();
    elapsed_seconds = end-start;
    std::cerr << "Spatial computation and heatmaps generatation time: " << elapsed_seconds.count() << "s\n";    
    elapsed_seconds = end-s;
    std::cerr << "Total time: " << elapsed_seconds.count() << "s\n";    
    releaseData(2); 
    return 0;
}

