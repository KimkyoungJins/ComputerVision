#include <iostream>
#include <opencv2/opencv.hpp>


using namespace cv;

// 이미지에 대한 정보를 변수로 받아서 90도 로테이트 
// 포인터로 받으면 좀 더 빠를 듯
void rotate_img(int *rows, int *cols){
    for (int i = 0; i < *rows; i++){
        for (int j = 0; j < *cols; j++)
    

    }
}

int main(){

    // Read an image “lena.png” as a gray-scale image
    // 0은 gray scale으로 읽으라는 것 
    Mat image;
    int *p;
    
    image = imread("lena.png", 0);
    imshow("image before rotation", image);

    int *cols, *rows;
    cols = &image.cols;
    rows = &image.rows;

    for(int i = 0; i < image.rows; i++){
        for (int j = 0; j < image.cols; j++){
            image.at<uchar>()
        }
    }

    // Generate a 90-degree rotated image


    
    // On the generated image, perform negative transformation 
    // if the pixel value is smaller than 127. 
    // Otherwise, perform gamma transformation with gamma as 10
    

    // Display the input and the result on two windows
    // ‘gray image’ for input
    // ‘result’ for result    
    waitKey(0);
    return 0;
}