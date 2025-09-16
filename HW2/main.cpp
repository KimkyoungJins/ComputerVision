#include <iostream>
#include <opencv2/opencv.hpp>


using namespace cv;

// 이미지에 대한 정보를 변수로 받아서 90도 로테이트 
Mat rotate_90_img(Mat image){
        for(int i = 0; i < image.rows; i++){
            for (int j = 0; j < image.cols; j++){
                image.at<uchar>(j, image.rows - 1 - i) = image.at<uchar>(i, j);
            }
        }
    return image;
}

int main(){

    // Read an image “lena.png” as a gray-scale image
    // 0은 gray scale으로 읽으라는 것 
    Mat image;
    image = imread("lena.png", 0);
    imshow("image before rotation", image);

    // Generate a 90-degree rotated image
    Mat rotated_image = rotate_90_img(image);
    imshow("Rotated image", rotated_image);
    
    // On the generated image, perform negative transformation 
    // if the pixel value is smaller than 127. 
    // Otherwise, perform gamma transformation with gamma as 10
    Mat negative_image = rotated_image.clone();
    
    

    // Display the input and the result on two windows
    // ‘gray image’ for input
    // ‘result’ for result    
    waitKey(0);
    return 0;
}