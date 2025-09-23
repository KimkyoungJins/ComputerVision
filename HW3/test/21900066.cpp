#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


/*
21900066 김경진
컴퓨터비전 과제 3
*/

// 왼쪽
Mat left_half(Mat image){

    int rows = image.rows;
    int cols = image.cols;

    Rect left(0, 0, cols / 2, rows);
    Mat left_to = image(left);

    return left_to;
}

// 오른쪽
Mat right_half(Mat image){

    int rows = image.rows;
    int cols = image.cols;

    Rect right(cols / 2, 0, cols / 2, rows);
    Mat right_to = image(right);

    return right_to;
}

// 언샵마스크 로직
Mat unsharp_mask(Mat image){

    Mat gausian_blurr;      // 블러 처리될 이미지
    Mat right_half_image;   // 원본 이미지에서 오른쪽만 남을 것 
    Mat dst;                // 최종 필터된 결과값
    Mat unsharp_mask;       // 언샵마스크


    // 원본 이미지 이미지 반토막 냄
    right_half_image = right_half(image);

    GaussianBlur(right_half_image, gausian_blurr ,Size(3, 3), 0, 0, BORDER_DEFAULT);

    subtract(right_half_image, gausian_blurr, unsharp_mask);

    add(right_half_image,(unsharp_mask * 1), dst); 

    return dst;
}

// 메디안 블러
Mat median_filter(Mat image){

    Mat src = left_half(image);
    Mat dst;

    medianBlur(src, dst, 9);

    return dst;
}

int main(){

    // 이미지 읽어오기 
    Mat moon_image = imread("moon.png", 0);
    Mat salt_image = imread("saltnpepper.png", 0);


    imshow("moon", moon_image);
    imshow("moon_filtered", unsharp_mask(moon_image));

    imshow("saltnpepper", salt_image);
    imshow("saltnpepper_filtered", median_filter(salt_image));

    waitKey(0);
    return 0;
}
