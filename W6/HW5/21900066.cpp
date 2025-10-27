#include <iostream>
#include <opencv2/opencv.hpp>

// 21900066 김경진
// 컴퓨터 비전 과제 5

using namespace cv;
using namespace std;

int main(){

    // gray으로 읽는다. 
    Mat image1 = imread("finger_print.png", 0);
    Mat image1_dst;

    Mat image2 = imread("adaptive_1.jpg", 0);
    Mat image2_dst;

    Mat image3 = imread("adaptive.png", 0);
    Mat image3_dst;

    //For ‘finger_print.png’, set finger print region to 0 and background region to 255
    threshold(image1, image1_dst, 160, 255, THRESH_BINARY);
    
    

    //For ‘adatpve_1.jpg’, and ‘adaptive.png’, set character region to 0 and background region to 255
    adaptiveThreshold(image2, image2_dst, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 85, 15);
    adaptiveThreshold(image3, image3_dst, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 85, 15);

    imshow("finger_print", image1_dst);
    imshow("adaptive_1", image2_dst);
    imshow("adaptive", image3_dst);
    
    waitKey(0);
    return 0;
}