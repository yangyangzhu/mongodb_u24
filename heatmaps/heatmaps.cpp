#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;
using namespace cv;

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

int main( int argc, char** argv )
{
    if( argc != 8) {
       cout <<" Usage: heatmaps image1 image2 tile_size image_width image_height cancer_type store_path" << endl;
       return -1;
    }
    
    Mat image1, image2;
    image1 = imread(argv[1], CV_8UC1);
    image2 = imread(argv[2], CV_8UC1);
    int tile_size = atoi(argv[3]);
    
    if (!image1.data || !image2.data) {
        cout << "Could not open images!" << endl;
        return 2;
    }
    if (tile_size != 128 && tile_size != 256 && tile_size != 512) {
        cout << "Tile size is not correct" << endl;
        return 2;
    }

    int rows, cols;
    
    if (image1.rows != image2.rows || image1.cols != image2.cols) {
        cout << "Images are not the same size" << endl;
        return 3;
    } else {
        rows = image1.rows;
        cols = image1.cols;
    }
    
    int image_width = atoi(argv[4]);
    int image_height = atoi(argv[5]);
    
    string cancer_type(argv[6]);
    string store_path(argv[7]);
  
    //filename like:
    //TCGA-VM-A8CD-01Z-00-DX1.F33FFB83-3DC7-4543-A496-1EC738188DE0_appMag_40_9_19-seg.png
   
    string file = std::string(argv[1]);
    string filename = file.substr(file.find_last_of("/") + 1);
    string image_caseid = filename.substr(0,filename.find_first_of("."));
    std::vector<std::string> elems = split(filename,'_');
    string image_url = elems[0];
    string image_objective = elems[2];
    int big_tile_col = stoi(elems[3]);
    int big_tile_row = stoi(elems[4].substr(0,elems[4].find_first_of("-")));

    //cout << image_caseid <<endl;
    //cout << image_url << endl;
    //cout << image_objective << " " << big_tile_col << " " << big_tile_row << endl;

/*
 {
        "_id" : ObjectId("5512f0e291905d7c77473eec"),
        "analysis_execution_id" : "yi:vad:jacc",
        "x" : 0.7093381023806776,
        "tile_id" : 4621,
        "y" : 0.18015801811709548,
        "loc" : [
                0.7093381023806776,
                0.18015801811709548
        ],
        "w" : 0.00984577516249375,
        "h" : 0.014817816108586809,
        "normalized" : true,
        "type" : "heatmap",
        "color" : "red",
        "features" : {
                "Area" : 262144,
                "Metric" : 0.871143,
                "MetricType" : "jacc"
        },
        "image" : {
                "heigth" : 34553,
                "cancer_type" : "gbm",
                "uri" : "TCGA-02-0001-01Z-00-DX3.2836ce55-491f-4d86-99b1-668946927af8",
                "caseid" : "TCGA-02-0001-01Z-00-DX3",
                "width" : 52002,
                "objective" : 20,
                "mpp_y" : 0.5015,
                "mpp_x" : 0.5015
        }
}    
*/  
    
    Mat result;
    Mat image1_roi, image2_roi;
    Rect region;
 
    int count = 1;

    int col_count = (cols + tile_size - 1) / tile_size;
    int row_count = (rows + tile_size - 1) / tile_size; 
    for (int i = 0; i < col_count; ++i) {
        for ( int j = 0; j < row_count; ++j) {
            string tile_id =  to_string((long long)big_tile_col) + "_" + to_string((long long)big_tile_row) 
                              + "_" + to_string((long long)i) + "_" + to_string((long long)j); 
            int local_col = i*tile_size;
            int local_row = j*tile_size;
            int global_col = big_tile_col*4096 + local_col;
            int global_row = big_tile_row*4096 + local_row;

            int local_width = min(tile_size, cols-local_col);
            int local_height = min(tile_size, rows-local_row);
   
            region  = Rect(local_col, local_row, local_width, local_height);
            image1_roi = image1(region);
            image2_roi = image2(region);
            bitwise_and(image1_roi,image2_roi,result);
     
            double x = global_col/(double)image_width;
            double y = global_row/(double)image_height;
            double w = local_width/(double)image_width;            
            double h = local_height/(double)image_width;

            int area = local_width*local_height;
            double tile_dice = 2.0*countNonZero(result)/(countNonZero(image1_roi) + countNonZero(image2_roi));
             
            std::stringstream jstrm;
            
            jstrm << "{"
                  << "\"analysis_execution_id\":\"v1:v1a:tile_dice\","
                  << "\"tile_id\":" << tile_id << ","
                  << "\"loc\":[" << x << "," << y << "],"
                  << "\"w\":" << w << ","
                  << "\"h\":" << h << ","
                  << "\"normalized\":true,"
                  << "\"type\":\"heatmap\","
                  << "\"color\":\"red\","
                  << "\"x\":" << x << ",\"y\":" << y << ","
                  << "\"features\":{"
                               << "\"Area\":" << area << ","
                               << "\"Metric\":" << tile_dice << ","
                               << "\"MetricType\":\"tile_dice\"},"
                               << "\"image\":{"
                               << "\"heigth\":" << image_height << ","
                               << "\"cancer_type\":\"" << cancer_type << "\","
                               << "\"width\":" << image_width << ","
                               << "\"uri\":\"" << image_url << "\","
                               << "\"caseid\":\"" << image_caseid << "\","
                               << "\"objective\":" << image_objective << "}"
                  << "}";
            //cout << jstrm.str() << endl;
            std::ofstream out(store_path+"/tile_dice_"+tile_id+".json");
            out << jstrm.str() << endl;
        } 
    }
    return 0;
}
