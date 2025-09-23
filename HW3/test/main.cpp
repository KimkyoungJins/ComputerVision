#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// 왼쪽 보여줌
Mat left_half(Mat image){

    int rows = image.rows;
    int cols = image.cols;

    Rect left(0, 0, cols / 2, rows);
    Mat left_to = image(left);

    return left_to;
}

// 오른쪽 보여줌
Mat right_half(Mat image){

    int rows = image.rows;
    int cols = image.cols;

    Rect right(cols / 2, 0, cols / 2, rows);
    Mat right_to = image(right);

    return right_to;
}

// // 언샵마스크 로직
// Mat unsharp_mask(Mat image){

//     Mat gausian_blurr;      // 블러 처리된 이미지 저장
//     Mat right_half_image;


// }

// 메디안 필터적용
Mat median_filter(){
    Mat image = imread("saltpepper.png", 0);
    Mat src = left_half(image);
    Mat dst;
    medianBlur(src, dst, 9);
    return dst;
}

int main(){

    Mat image;              // 원래 이미지  저장
    Mat changed_origin_image;
    Mat gausian_blurr;      // 블러 처리된 이미지 저장
    Mat right_half_image;
    Mat result;
    Mat unsharp_mask;

    // 이미지 읽어오기 
    image = imread("moon.png", 0);
    imshow("moon", image);

    // 이미지를 반쪽내기
    right_half_image = right_half(image);
    image = right_half(image);

    // 블러적용하기 
    GaussianBlur(right_half_image, gausian_blurr ,Size(3, 3), 0, 0, BORDER_DEFAULT);
    
    // 적용한 해당값을 빼기
    subtract(right_half_image, gausian_blurr, unsharp_mask);

    add(image,(unsharp_mask * 1), result); 

    imshow("moon_filtered", result);
    imshow("saltnpepper",median_filter());

    waitKey(0);
    return 0;
}
