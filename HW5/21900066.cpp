/*
21900066 김경진
과제 4
*/



#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

// 특정 범위에 있는 라인만 그린다. 
void lines(Mat& img, const vector<Vec2f>& lines, Rect roi_rect, double min_angle, double max_angle) {
    
    for (size_t i = 0; i < lines.size(); i++) {
        float rho = lines[i][0], theta = lines[i][1];
        float angle_deg = theta * 180.0 / CV_PI;

        // 주어진 각도에 있는지 확인해야한다. 
        if (angle_deg > min_angle && angle_deg < max_angle) {
            Point pt1, pt2;
            double a = cos(theta), b = sin(theta);
            double x0 = a * rho, y0 = b * rho;
            pt1.x = cvRound(x0 + 1000 * (-b));
            pt1.y = cvRound(y0 + 1000 * (a));
            pt2.x = cvRound(x0 - 1000 * (-b));
            pt2.y = cvRound(y0 - 1000 * (a));
            line(img, pt1 + Point(roi_rect.x, roi_rect.y), pt2 + Point(roi_rect.x, roi_rect.y), Scalar(0, 0, 255), 1, LINE_AA);
        }
    }
}

int main(){

    VideoCapture cap;
    Mat frame;
    Mat result;
    Mat roi_left;
    Mat roi_right;
    Mat left_canny;
    Mat right_canny;
    int max;
    int count;
    vector<Vec2f> left_lines, right_lines;

    cap.open("Road.mp4");

    max = 20 * 30;
    count = 0;


    while(1){

        cap >> frame;
        result = frame.clone();

        // 좌우측 정의
        Rect left_rect(200, 400, 400, 200);
        Rect right_rect(600, 400, 400, 200);

        roi_left = frame(left_rect);
        roi_right = frame(right_rect);

        // 그레이스케일, 블러, 캐니
        cvtColor(roi_left, left_canny, COLOR_BGR2GRAY);
        GaussianBlur(left_canny, left_canny, Size(5, 5), 5);
        Canny(left_canny, left_canny, 10, 60, 3);

        cvtColor(roi_right, right_canny, COLOR_BGR2GRAY);
        GaussianBlur(right_canny, right_canny, Size(5, 5), 5);
        Canny(right_canny, right_canny, 10, 60, 3);
        
        imshow("Left canny", left_canny);
        imshow("Right canny", right_canny);

        HoughLines(left_canny, left_lines, 1, CV_PI / 180, 50);
        HoughLines(right_canny, right_lines, 1, CV_PI / 180, 50);
        
        // 그리기
        lines(result, left_lines, left_rect, 30, 60);
        lines(result, right_lines, right_rect, 120, 150);

        imshow("Frame", result);

        count++;
        if(waitKey(30) == 'q'){
            break;
        }
    }

    cap.release();  
    
    return 0;
}