#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>

using namespace std;
using namespace cv;


int main( int argc, char** argv )
{
    if( argc != 4) {
       cout <<" Usage: heatmaps image1 image2 tile_size" << endl;
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
     
    cout << rows << " " << cols <<endl;
    Mat result;
    Mat image1_roi, image2_roi;
    Rect region;
 
    int count = 1; 
    for (int i = 0; i < rows; i+=tile_size) {
        
        for ( int j = 0; j < cols; j+=tile_size) {
            
            region  = Rect(j, i, min(tile_size, cols-j), min(tile_size, rows-i));
            image1_roi = image1(region);
            image2_roi = image2(region);
            bitwise_and(image1_roi,image2_roi,result);
     
            cout << count << " ";
            ++count;
            cout << countNonZero(image1_roi) << " ";
            cout << countNonZero(image2_roi) << " ";
            cout << countNonZero(result) << endl;
        }
       
    }
    return 0;
}
