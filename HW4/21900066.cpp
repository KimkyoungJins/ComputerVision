#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

// 21900066 김경진
// 컴퓨터 비전 과제 4

int main(){

    VideoCapture cap;
    Mat image;
    Mat frame;      // 프레임
    Mat result;     // 결과값 저장
    Mat roi_left;   // roi 왼쪽
    Mat roi_right;  // roi 오른쪽

    // 캐니 한 후에 저장
    Mat canny_left;
    Mat canny_right;

    // 라인을 잡기 위한 
    vector<Vec4i> lines_left, lines_right;

    // 비디오 열기
    cap.open("Road.mp4");

    // 프레임 측정하기 
    double fps = cap.get(CAP_PROP_FPS);
    int delay = 1000 / fps;

    // 좌우측을 정사각형을 정의한다.
    Rect left_rect(200, 400, 400, 200);     // draw_line 400, height 200이다. 
    Rect right_rect(600, 400, 400, 200);    // with는 400, height 200이다. 

    while(1){

        // 동영상에서 한 프레임을 읽어온다. 
        cap >> frame;
        result = frame.clone();

        // 비디오 끝나면 스탑
        if(frame.empty()){
            break;
        }

        // 정의한 정사각형을 프레임에 넣는다. 
        roi_left = frame(left_rect);
        roi_right = frame(right_rect);

        // 두개의 사각형에 그레이스케일 블러 캐니를 적용시킨다. 
        // 왼쪽 
        cvtColor(roi_left, canny_left, COLOR_BGR2GRAY);
        GaussianBlur(canny_left, canny_left, Size(5, 5), 5);
        Canny(canny_left, canny_left, 10, 60, 3);
        // 오른쪽
        cvtColor(roi_right, canny_right, COLOR_BGR2GRAY);
        GaussianBlur(canny_right, canny_right, Size(5, 5), 5);
        Canny(canny_right, canny_right, 10, 60, 3);

        // // 라인 형성을 위해서 전체 이미지에도 가우시안과 캐니를 적용한다.
        // GaussianBlur(frame, result, SIz, 60, 3);

        // 레프트
        namedWindow("Left canny");
        moveWindow("Left canny", 200, 0);
        imshow("Left canny", canny_left);

        // 롸이트
        namedWindow("Right canny");
        moveWindow("Right canny", 600, 0);
        imshow("Right canny", canny_right);

        // 라인 탐색
        HoughLinesP(canny_left, lines_left, 1, CV_PI / 180, 50, 30, 10);
        HoughLinesP(canny_right, lines_right, 1, CV_PI / 180, 50, 30, 10);

        // 왼쪽 라인 그리기
        for (size_t i = 0; i< lines_left.size(); i++){
            Vec4i l = lines_left[i];
            line(result, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255),3, 8);
        }

        // 오른쪽
        for (size_t i = 0; i < lines_right.size(); i++){
            Vec4i l = lines_right[i];
            line(result, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255),3, 8);
        }

        // imshow("Frame", result);
        imshow("video", result);

        waitKey(delay);
    }

    cap.release();

    return 0;
}