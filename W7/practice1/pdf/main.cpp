#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;


int main() {
    Mat gray = imread("contours.png", 0);
    Mat result;
    

    // 이미지 이진화
    threshold(gray, result, 230, 255, THRESH_BINARY_INV);
    
    // 외곽선 정보를 저장하는 변수이다.
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    
    findContours(result, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    
    putText(result, format("contour count: %d", contours.size()), Point(50, 80), FONT_HERSHEY_SIMPLEX, 1, Scalar(128), 4);
    
    imshow("contours", result);
    waitKey(0);
}

int main() {
    // Mat gray = imread("contours.png", 0);
    // "contours.png" 파일을 흑백(0)으로 로드합니다.
    Mat gray = imread("contours.png", 0);
    Mat result;
    
    // threshold(gray, result, 180, 255, THRESH_BINARY_INV);
    // 이미지 이진화: 픽셀 값 180을 기준으로 반전 이진화(THRESH_BINARY_INV)를 수행하여 객체를 흰색으로 만듭니다.
    threshold(gray, result, 180, 255, THRESH_BINARY_INV);
    
    // vector<vector<Point>> contours;
    // 검출된 외곽선(점들의 리스트)을 저장할 변수입니다.
    vector<vector<Point>> contours;
    // vector<Vec4i> hierarchy;
    // 외곽선들의 계층 구조 정보를 저장할 변수입니다.
    vector<Vec4i> hierarchy;
    
    // findContours(result, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    // 외곽선 검출 함수: 외부 외곽선만 검출(CV_RETR_EXTERNAL)하고, 단순한 방식으로 경계를 근사하여 저장합니다.
    findContours(result, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    
    // defining bounding rectangle
    // vector<Rect> boundRect(contours.size());
    // 검출된 외곽선의 개수만큼 Rect(직사각형) 객체를 저장할 벡터를 생성합니다.
    vector<Rect> boundRect(contours.size());
    
    // for (int i = 0; i < contours.size(); i++)
    // 검출된 모든 외곽선에 대해 반복합니다.
    for (int i = 0; i < contours.size(); i++)
    {
        // boundRect[i] = boundingRect(Mat(contours[i]));
        // i번째 외곽선(contours[i])을 둘러싸는 최소 크기의 경계 직사각형을 계산하여 boundRect[i]에 저장합니다.
        boundRect[i] = boundingRect(Mat(contours[i]));
    }

    // draw rectangles on the contours
    // for (int i = 0; i < contours.size(); i++)
    // 모든 경계 직사각형에 대해 반복합니다.
    for (int i = 0; i < contours.size(); i++)
    {
        // rectangle(result, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 0, 255), 2, 8, 0);
        // result 이미지에 직사각형을 그립니다.
        // - boundRect[i].tl(): 직사각형의 좌상단(Top-Left) 좌표
        // - boundRect[i].br(): 직사각형의 우하단(Bottom-Right) 좌표
        // - Scalar(0, 0, 255): 직사각형의 색상 (BGR 포맷에서 빨간색)
        // - 2: 선의 두께
        rectangle(result, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 0, 255), 2, 8, 0);
    }
    
    // imshow("contours", result);
    // 경계 상자가 그려진 최종 결과 이미지(result)를 표시합니다.
    imshow("contours", result);
    waitKey(0);
}


// Mat image, erosion, dilation;
// 원본 이미지, 침식 결과, 팽창 결과를 저장할 Mat 변수를 선언합니다.
Mat image, erosion, dilation;

// Mat element = getStructuringElement(MORPH_ELLIPSE, Size(10, 10));
// 형태학적 연산에 사용될 커널(Structuring Element)을 생성합니다.
// - MORPH_ELLIPSE: 타원형 모양의 커널을 지정합니다.
// - Size(10, 10): 커널의 크기를 10x10 픽셀로 지정합니다.
Mat element = getStructuringElement(MORPH_ELLIPSE, Size(10, 10));

// //Other options: MORPH_RECT, MORPH_CROSS
// 주석: 다른 커널 모양으로는 사각형(MORPH_RECT)과 십자형(MORPH_CROSS)이 있습니다.

// image = imread("water_coins.jpg", 0);
// "water_coins.jpg" 파일을 흑백(0)으로 로드합니다.
image = imread("water_coins.jpg", 0);

// threshold(image, image, 128, 255, THRESH_BINARY);
// 이진 임계값 처리: 픽셀 값 128을 기준으로 THRESH_BINARY 모드를 적용하여 이미지를 이진화합니다.
// 128보다 크면 255(흰색), 작으면 0(검은색)이 됩니다.
threshold(image, image, 128, 255, THRESH_BINARY);

// erode(image, erosion, element);
// 침식(Erosion) 연산: 원본 이미지(image)의 경계를 얇게 만들고 작은 노이즈를 제거하여 erosion에 저장합니다.
// element(커널)에 의해 정의된 영역만큼 객체 크기가 줄어듭니다.
erode(image, erosion, element);

// dilate(image, dilation, element);
// 팽창(Dilation) 연산: 원본 이미지(image)의 경계를 두껍게 만들고 끊어진 객체를 연결하여 dilation에 저장합니다.
// element(커널)에 의해 정의된 영역만큼 객체 크기가 늘어납니다.
dilate(image, dilation, element);

// imshow("Binary image", image);
// 원본 이진화 이미지를 출력합니다.
imshow("Binary image", image);

// imshow("Erosion", erosion);
// 침식 연산 결과를 출력합니다.
imshow("Erosion", erosion);

// imshow("Dilation", dilation);
// 팽창 연산 결과를 출력합니다.
imshow("Dilation", dilation);

// waitKey(0);
// 키 입력이 있을 때까지 창을 유지합니다.
waitKey(0);