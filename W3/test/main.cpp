#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

// this is for the histogram equalization
void draw_histogram(){
    
}


void make_reck(Mat image){
    // 왼쪽 위의 꼭짓점을 중심으로 x, y, width, height를 뜻한다. 
    Rect rect = Rect(10, 10, 100, 100);

    // image the image that you draw
    // rectangle object
    // Scalar -> 사각형 선의 색깔을 BGR 포맷으로 지정
    // 4 -> 선의 두께
    // 선의 종류임, 8이라고 생각하면 됨
    // 0 사각형의 꼭짓점을 사용하는 인자인데 사용 안함.
    rectangle(image, rect, Scalar(255,0, 0), 4, 8, 0);   
}


void make_line(Mat image){
    // 2개의 좌표를 만든다 constructor으로 
    Point p1(25, 25), p2(100, 50);
    line(image, p1, p2, Scalar(255, 0, 0), 3, 8, 0);
}


// 나중에
void make_polygon(){    

    Mat image = Mat::zeros(400, 400, CV_8UC3);
    int w = 400;

    Point trapezoid[1][4];
}

void write_text(Mat image){
    image = Mat::zeros(400, 600, CV_8UC3);
    int w = image.cols;
    int h = image.rows;

    // image -> image
    // format - >sprintf와 비슷함
    // Point(50, 50) -> 시작될 위치임
    // FONT+HERSHEY_SIMPLEX 사용할 글꼴
    // 글자의 크기
    // Scalar BGR 포맷임
    // 4는 글자의 두께이다. 
    putText(image, format("width: %d, height: %d", w, h), 
    Point(50, 80), FONT_HERSHEY_SCRIPT_SIMPLEX, 1, Scalar(0, 200, 200), 4);

    imshow("image", image);
}


int main() {

    Mat image;
    Mat hist_equalized_image;
    Mat hist_graph;
    Mat hist_equlized_graph;

    image = imread("lena.png", 0);
    
    // 사각형 만들기 
    make_reck(image);
    make_line(image);
    equalizeHist(image, hist_equalized_image); // histogram equalization

    hist_graph = draw_histogram(image);
    hist_equlized_graph = draw_histogram;

    // 1번째가 인풋, 2번째가 아웃풋이다. 
    // equalizeHist(image, his_equalized_image);
    // imshow("input image", image);
    // imshow("hst equlized image", his_equalized_image);
    imshow("image", image);

    waitKey(0);
    return 0;
}
