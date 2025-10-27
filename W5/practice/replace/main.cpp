#include <opencv2/opencv.hpp>

using namespace cv;

int main(){

    Mat image, blur, grad_x, grad_y, abs_grad_x, abs_grad_y, result;

    // 이미지를 그레이 스케일로 불러온다. 
    image = imread("lena.png", 0);

    // 가우시안 블러
    // 노이즈를 줄인다.
    // 이미지의 노이즈를 줄인다. 
    GaussianBlur(image, blur, Size(5, 5), 5, 5, BORDER_DEFAULT);

    // 편미분은 이미지에 있는 수직선 형태의 에지를 검출하는데 사용된다. 
    // 수직 방향의 에지를 탐색하여서 grad_x에 저장한다. 
    Sobel(blur, grad_x, CV_16S, 1, 0, 3);

    // grad_x를 화면에 표시할 수 있는 8비트 이미지로 변환하는 역할을 한다. 
    // 절댓값을 계산하고 
    // 8비트로 변환한다. 
    // grad_x를 시각적으로 표현 가능한 abs_grad_x로 최종변환 시킨다. 
    convertScaleAbs(grad_x, abs_grad_x);


    // 축 방향 에지 검출 수평선 코드.
    Sobel(blur, grad_y, CV_16S, 0, 1, 3);
    convertScaleAbs(grad_y, abs_grad_y);

    // 수직과 수평 에지를 각각 50퍼의 비율으로 합쳐서 최종 에지 이미지를 보여준다. 
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, result);

    // 결과 화면에 표시하기 
    imshow("X", abs_grad_x);
    imshow("Y", abs_grad_y);
    imshow("Input image", image);
    imshow("Soble edge detector", result);

    waitKey(0);

    return 0;
}