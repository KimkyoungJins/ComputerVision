#include <iostream>
#include <opencv2/opencv.hpp>

int main(){

    cv::Mat image;
    int value_B, value_G, value_R, channels;

    image = cv::imread("lena.png");
    channels = image.channels();
    
    uchar *data = (uchar*)image.data;


    
    return 0;
}