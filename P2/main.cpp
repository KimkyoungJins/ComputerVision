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
// 영상 중앙 부분은 x와 y가 100이라고 차면 x값은 40 ~ 60, y값은 0 20일때 line departure을 작동시키는 것으로 한다. 
// 가우시안 블러를 통하여서 노이즈를 제거하고
// 캐니엣지 적용시켜서 라인인 것을 확확인하고
// 허프변환 통하여서 차선인 것을 인식시킨다. 
// 그 후에 결과값의 참/거짓을 통하여서 Line departure 출력여부 결정한다
void line_departure(Mat frame){
    
    Mat line;                   // 허프변환을 위한 
    int roi_x, roi_y;           // 정해진 roi값 내에서 감지를 해야한다.
    Mat blur;                   // 가우시안 블러 저장 변수
    vector<Vec4i> lines;        // 허브변환 벡터값

    // 해당 이미지의 전체 x값과 y값을 모른다. 
    roi_x = frame.cols;
    roi_y = frame.rows;

    // p1의 값을 원하는 계산으로 구하기
    // 둘다 최대가 100이라고 치면
    // p1의 위치는 x의 40부분, y의 90부분
    float p1_x = (roi_x / 10);
    float p1_y = (roi_y / 10);

    // 원하는 ROI부분 설정하기
    Rect rect(p1_x * 4, p1_y * 9, p1_x * 2, p1_y);

    // roi부분을 frame에 넣기
    Mat roi = frame(rect);

    // 해당 부분을 가우시안해서 명확하게 바꾸기 그 다음에 blur에 저장
    GaussianBlur(roi, blur, Size(5, 5), 5, 5, BORDER_DEFAULT);
    
    // 블러한 이미지를 케니엣지를 통 하여서 선을 구한다. 
    // blur - > line
    Canny(blur, line, 60, 180, 3);

    // 캐니로 구한 선을 허프 변환 
    HoughLinesP(line, lines, 1, CV_PI / 180, 50, 10, 300);

    // 허프변환이 리턴한 lines 백터의 사이즈가 1이상 0일때가 있을 것이다. 
    // 차선을 감지한다면 line는 1이상일 것이고 차선을 감지하지 못한다면 lines의 값은 0일것이다.
    // 정해진 ROI에서 차선을 감지했으니 Line daparture 출력한다.
    if(lines.size() >= 1){
        putText(frame, "Line departure!", Point(150, 100), FONT_HERSHEY_COMPLEX, 1.5, Scalar(0, 0, 255), 2, LINE_AA, false);
    }
}


// // start moving
// // background subtraction을 사용하면 된다. 
// int start_moving(Mat frame){    
//     int result;

//     if(result == 1){
//         // 프레임 화면에 표시하기
//         putText(frame, "Start Moving!",Point(150, 100), FONT_HERSHEY_COMPLEX, 1.5, Scalar(0, 0, 255), 2, LINE_AA, false);
//     }  
// }

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
        
        // // Start Moving 감지함수
        // start_moving(frame);

        imshow("Project2", frame);
        waitKey(delay);
    }

    return 0;
}