#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// 21900066 김경진
// 컴퓨터비전 프로젝트 2


// 차선 이탈을 감지하기 위한 함수
// houghline을 사용하면 된다. 
// 해당 차선 침범을 감지하기 위해서는 
// 차선을 감지 할 줄 알아야 하고
// 감지한 차선이 영상의 중앙부분에 들어가기 시작할때 
// 영상 중앙 부분은 x와 y가 100이라고 차면 x값은 40 ~ 60, y값은 0 10일때 line departure을 작동시킨다. 

void line_departure(Mat frame){
    // Houghlines를 위한 
    Mat image, edge, result;
    vector<Vec4i> lines;

    result = frame.clone();
    Canny(image, edge, 50, 200, 3);



    // 차선 침범한게 확실하면 result를 1으로 한다.
    // 어차피 while문 안에서 반복되기 때문에 초기화 걱정 안해도됨
    int result = 0;

    // line을 detection한다.

    // line departure 텍스트 출력한다.    
    if(result == 1){
        // 프레임 화면에 표시하기
        // 매 프레임마다 출력이 될 것이고, 차선을 벗어나면 없어질 것이다. 
        putText(frame, "Line departure!",Point(150, 100), FONT_HERSHEY_COMPLEX, 1.5, Scalar(0, 0, 255), 2, LINE_AA, false);
    }
}


// start moving
// background subtraction을 사용하면 된다. 
int start_moving(Mat frame){    
    int result;

    if(result == 1){
        // 프레임 화면에 표시하기
        putText(frame, "Start Moving!",Point(150, 100), FONT_HERSHEY_COMPLEX, 1.5, Scalar(0, 0, 255), 2, LINE_AA, false);
    }
   
}

int main(){

    Mat image, edge, result;

    Mat frame;
    double fps;
    int delay;
    VideoCapture cap;

    // 비디오 파일 열기
    cap.open("Project2_video.mp4");

    // 안열리면 끄기
    if(!cap.isOpened()){
        cout << "no file" << endl;
        return -1;
    }
    
    fps = cap.get(CAP_PROP_FPS);
    delay = 1000 / fps;

    // 프레임 재생 성공함
    while(1){

        // 다음 프레임 읽기
        cap >> frame;
        
        // 프레임 끝나면 끄기
        if(frame.empty()){
            break;
        }

        // linedeparture 감지함수
        line_departure(frame);
        
        // Start Moving 감지함수
        start_moving(frame);

        imshow("Project2", frame);
        waitKey(delay);
    }

    return 0;
}




int main() {

    Mat image, edge, result;
    vector<Vec4i> lines;
    image = imread("chess_pattern.png");
    result = image.clone();
    cvtColor(image, image, CV_BGR2GRAY);
    Canny(image, edge, 50, 200, 3);


    //edge: input Mat, lines: output vector of lines
    //1: (rho) distance resolution of the accumulator in pixels
    //CV_PI/180: (theta) angle resolution of the accumulator in radians
    //50: (threshold) accumulator threshold parameter
    //10: (minLineLength) minimum line length.
    //300: (maxLineGap) Maximum allowed gap between points on the sa

    HoughLinesP(edge, lines, 1, CV_PI / 180, 50, 10, 300);

    for (int i = 0; i < lines.size(); i++) {
        Vec4i l = lines[i];
        line(result, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, 8);
    }

    imshow("Input image", image);
    imshow("edge", edge);
    imshow("Hough Transform", result);
    waitKey(0);

    return 0;
}