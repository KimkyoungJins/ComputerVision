#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
 
    return 0;
}

void test_2(void){

    int w = 150;
    int h = 100;

    Mat image(h, w, CV_8UC1, Scalar(255));
    cout << "size : " << image.size().height << 
    "," << image.size().width << endl;
    imshow("image", image);

    waitKey(0);
}

void test_1(void){
        // 1. Mat(int rows, int cols, int type)을 사용한 선언
    // 3x3 크기의 32비트 부동소수점(float) 행렬 생성 
    Mat mtx_float(3, 3, CV_32F); 
    cout << "mtx_float (3x3, CV_32F):\n" << mtx_float << endl;

    // 2. Mat(Size size, int type)을 사용한 선언
    // 1920x1080 크기의 8비트 3채널(컬러) 이미지 생성 
    Mat img_color(Size(1920, 1080), CV_8UC3);
    cout << "\nimg_color (1920x1080, CV_8UC3):\n" << img_color.size() << endl;

    // 3. Mat(const Mat &m)을 사용한 선언 (얕은 복사)
    // 기존 행렬을 사용하여 새로운 행렬 선언 [cite: 98]
    Mat mtx_copy = mtx_float;
    cout << "\nmtx_copy (shallow copy):\n" << mtx_copy << endl;
    
    // 얕은 복사임을 확인하기 위해 mtx_float의 값을 변경해봅니다.
    mtx_float.setTo(Scalar(1.0));
    cout << "\nAfter changing mtx_float:\n" << mtx_float << endl;
    cout << "mtx_copy also changes:\n" << mtx_copy << endl;

    // 4. Mat(Size size, int type, const Scalar& s)을 사용한 선언
    // 100x150 크기의 8비트 1채널(흑백) 이미지 생성 및 모든 픽셀을 흰색(255)으로 초기화 
    int w = 150, h = 100;
    Mat image_white(h, w, CV_8UC1, Scalar(255)); 
    cout << "\nimage_white (100x150, CV_8UC1, all 255):\n" << image_white.size() << endl;
    
    // 이 이미지를 화면에 표시합니다.
    imshow("White Image", image_white);

    // 5. 깊은 복사(Deep Copy) 예시
    Mat mtx_deep_copy = mtx_float.clone();
    mtx_float.setTo(Scalar(2.0));
    cout << "\nAfter changing mtx_float again:\n" << mtx_float << endl;
    cout << "mtx_deep_copy does NOT change:\n" << mtx_deep_copy << endl;
    
    // 키 입력 대기
    waitKey(0);


}