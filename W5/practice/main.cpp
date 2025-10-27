#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(){

    Mat image, canny;
    image = imread("lena.png", 0);

    Canny(image, canny, 190, 200, 3);

    imshow("input", image);
    imshow("output", canny);

    waitKey(0);
    
    return 0;
}