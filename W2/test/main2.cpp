#include <iostream>
#include <opencv2/opencv.hpp>

int main(){


    // cv 를 이미 선언하면 굳이 안해도 된다. 
    // using pointer to access the pixcel
    cv::Mat image =  cv::imread("lena.png");
    int value_B, value_G, value_R, channels;
    channels = image.channels();
    
    uchar *p;
    p = image.ptr<uchar>(50);
    value_B = p[100 * channels + 0];
    value_G = p[100 * channels + 1];
    value_R = p[100 * channels + 2];
    std::cout << "Value of the 50, 100 is " << value_B << " " << value_G << " " << value_R << std::endl;

    cv::waitKey(0);
    
    return 0;
}