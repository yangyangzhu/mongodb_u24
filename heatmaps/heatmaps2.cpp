#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;
using namespace cv;

int main( int argc, char** argv )
{
    if( argc != 5) {
       cout <<" Usage: heatmaps image1 image2 tile_size store_path" << endl;
       return -1;
    }
    
    Mat image1, image2;
    image1 = imread(argv[1], CV_8UC1);
    image2 = imread(argv[2], CV_8UC1);
    int tile_size = atoi(argv[3]);
    
    if (!image1.data && !image2.data) {
        cout << "Could not open images!" << endl;
        return 2;
    }
    if (tile_size != 128 && tile_size != 256 && tile_size != 512) {
        cout << "Tile size is not correct" << endl;
        return 2;
    }

    bool missOneMask = false;
    if (!image1.data || !image2.data)  missOneMask = true;
    
    Mat image = image1;
    if (!image1.data) image = image2;

    int rows, cols;
    if (!missOneMask && (image1.rows != image2.rows || image1.cols != image2.cols)) {
        cout << "Images are not the same size" << endl;
        return 3;
    } else {
        rows = image.rows;
        cols = image.cols;
    }
  
    if (rows > 4096 || cols > 4096) {
        cout << "Image out of 4K X 4K" << endl;
        return 4;
    }
    
    string store_path(argv[4]);
   
    Mat result;
    Mat image1_roi, image2_roi;
    Rect region;
 
    int count = 1;

    int col_count = (cols + tile_size - 1) / tile_size;
    int row_count = (rows + tile_size - 1) / tile_size;
    for (int i = 0; i < col_count; ++i) {
        for ( int j = 0; j < row_count; ++j) {
            string tile_id = to_string((long long)i) + "_" + to_string((long long)j); 
            int local_col = i*tile_size;
            int local_row = j*tile_size;
            int local_width = min(tile_size, cols-local_col);
            int local_height = min(tile_size, rows-local_row);
            double tile_dice;
            region  = Rect(local_col, local_row, local_width, local_height);
            
            if (missOneMask && !countNonZero(image(region))) {
                continue;
            } else if (missOneMask) {
                int c = countNonZero(image(region));
                if (c/2.0 > 200)
                    tile_dice = 0.0; 
                else
                    continue;
            } else {
            
                image1_roi = image1(region);
                image2_roi = image2(region);
            
                int c1 = countNonZero(image1_roi);
                int c2 = countNonZero(image2_roi);
                if ((c1+c2)/2.0 <= 200)
                    continue;
                else {
                    if (c1!=0 && c2!=0) {
                        bitwise_and(image1_roi,image2_roi,result);
                        tile_dice = 2.0*countNonZero(result)/(c1 + c2);
                    } else if (c1==0 && c2==0){
                        continue;
                    } else {
                        tile_dice = 0.0;
                    }
                }
            }

            std::stringstream jstrm;
            
            jstrm << "{"
                  << "\"tile_id\":\"" << tile_id << "\","
                  << "\"w\":" << local_width << ","
                  << "\"h\":" << local_height << ","
                  << "\"type\":\"tile_dice\","
                  << "\"value\":" << tile_dice << ","
                  << "\"x\":" << local_row << ",\"y\":" << local_col
                  << "}";
                //cout << jstrm.str() << endl;
            std::ofstream out(store_path+"/tile_dice_"+tile_id+".json");
            out << jstrm.str() << endl;
        } 
    }
    return 0;
}
