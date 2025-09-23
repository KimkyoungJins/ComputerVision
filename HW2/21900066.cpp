#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

//21900066 김경진 컴퓨터 비전 과제 2

// 이미지에 대한 행렬을 받아서 90도 로테이트
Mat rotate_img_90(Mat image){

    Mat result(image.rows, image.cols, image.type());

        for(int i = 0; i < image.rows; i++){
            for (int j = 0; j < image.cols; j++){
                result.at<uchar>(j, image.rows - 1 - i) = image.at<uchar>(i, j);
            }
        }

    return result;  
}

// 이미지에 대한 행렬을 받아서 image negtive으로 
Mat Negative_Gamma(Mat image){

    Mat result = image.clone();

    for(int i = 0; i < result.rows; i++){
        for (int j = 0; j < result.cols; j++){
            uchar pixel;
            pixel = result.at<uchar>(i, j);
            
            // 127 보다 작다면 Negative transformation
            if(pixel < 127){
                result.at<uchar>(i, j) = 255 - pixel;
            }

            // 다른 경우에는 Gamma transformation
            else {
                float gamma = pixel / 255.0;
                float gamma_trans = pow(gamma_trans, 10.0);
                result.at<uchar>(i, j) = saturate_cast<uchar>(gamma_trans * 255.0);
            }
        }
    }
    return result;
}

int main(){

    // 이미지 파일 읽기
    // 0은 gray scale으로 읽으라는 것 
    Mat image;
    image = imread("lena.png", 0);
    imshow("input image", image);

    Mat rotated_image = rotate_img_90(image);    
    Mat result_image = Negative_Gamma(rotated_image);

    imshow("result image", result_image);
    waitKey(0);
    return 0;
}