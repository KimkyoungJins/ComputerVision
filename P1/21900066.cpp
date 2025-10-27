#include <iostream>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;


/*
21900066 김경진 컴퓨터 비전 프로젝트 1
*/


// 네거티브 로직
void negative_transformation(Mat& current, Mat& change){ 

    change = current.clone();
    for(int y = 0; y <current.rows; ++y){
        for(int x = 0; x < current.cols; ++x){
            Vec3b& pixel = current.at<Vec3b>(y, x);
            pixel[0] = 255 - pixel[0];
            pixel[0] = 255 - pixel[1];
            pixel[0] = 255 - pixel[2];
        }
    }
    
}

// 감마
void gamma_transformation(Mat& current, Mat& change){

    // 2.5로 해야함
    float gamma = 2.5;
    unsigned char pix[256];

    for(int i = 0; i < 256; i++){
        pix[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0);

    }
        change = current.clone();

        for(int y = 0; y < current.rows; y++){
            for(int x = 0; x < current.cols; x++){
                Vec3b& pixel = change.at<Vec3b>(y, x);
                    pixel[0] = pix[pixel[0]];
                    pixel[1] = pix[pixel[1]];
                    pixel[2] = pix[pixel[2]];
                }
        }
}
    

// 히스토그램
void histogram_equalization(Mat current, Mat& changed) {

    Mat ycrcb;      // ycrcb으로 변환하기 위함
    cvtColor(current, ycrcb, COLOR_BGR2YCrCb); 
    vector<Mat> channels;
    split(ycrcb, channels); 

    equalizeHist(channels[0], channels[0]);

    merge(channels, ycrcb); 
    cvtColor(ycrcb, changed, COLOR_YCrCb2BGR);
}


// 컬러 슬라이싱함. 
void color_slicing(const Mat& current, Mat& changed) {
    Mat hsv;

    cvtColor(current, hsv, COLOR_BGR2HSV); 

    vector<Mat> channels;

    split(hsv, channels);   // 채널 분리

    
    for (int j = 0; j < hsv.rows; j++) {
        for (int i = 0; i < hsv.cols; i++) {
            
            uchar hue = channels[0].at<uchar>(j, i);

            if (hue > 9 && hue < 23) {
            
            } else {
                
                channels[1].at<uchar>(j, i) = 0;
            }
        }
    }

    merge(channels, hsv); // 채널 병합
    cvtColor(hsv, changed, COLOR_HSV2BGR); // 다시 BGR로
}

// 컬러 채인지
void color_change(const Mat& current, Mat& changed) {
    Mat hsv;
    cvtColor(current, hsv, COLOR_BGR2HSV); 
    vector<Mat> channels;
    split(hsv, channels); 


    for (int j = 0; j < hsv.rows; j++) {
        uchar* h = channels[0].ptr<uchar>(j);
        for (int i = 0; i < hsv.cols; i++) {
            if (h[i] > 129) {
                h[i] = h[i] - 129;
            } else {
                h[i] = h[i] + 50;
            }
        }
    }
    merge(channels, hsv); 
    cvtColor(hsv, changed, COLOR_HSV2BGR); // 다시 BGR로 변환 [cite: 729]
}

// 평군 필터
void average_filtering(const Mat& current, Mat& changed) {
    
    blur(current, changed, Size(9, 9));
}

// 언샵 마스킹 로직
void unsharp_masking(const Mat& current, Mat& changed) {
    Mat blurred;
    Mat mask;

    blur(current, blurred, Size(9, 9));
    
    subtract(current, blurred, mask);
    
    double k = 1.5; 

    scaleAdd(mask, k, current, changed);
}


// 화이트 밸런싱 로직
void white_balancing(const Mat& current, Mat& changed) {
    changed = current.clone();
    vector<Mat> bgr_channels;
    split(changed, bgr_channels); 

    for (int k = 0; k < 3; k++) {
        double avg = mean(bgr_channels[k])[0]; 
        if (avg == 0) continue;
        double scale = 128.0 / avg;
        
        for (int i = 0; i < changed.rows; i++) {
            for (int j = 0; j < changed.cols; j++) {
                uchar& pixel = bgr_channels[k].at<uchar>(i, j);
                pixel = saturate_cast<uchar>(pixel * scale); 
            }
        }
    }
    merge(bgr_channels, changed); 
}


// 원래대로
void reset_image(const Mat& current, Mat& changed) {
    current.copyTo(changed);
}



int main(){

    VideoCapture cap;
    Mat frame, changed;
    int fps;
    int delay;
    int current_mode;   // 현재 진행되고 있는 모드를 표현하고 그것으로 재생하는 것이 필요함. 

    // 비디오 오픈
    if(cap.open("video.mp4") == 0){
        cout << "not such file!\n" << endl;
        waitKey(0);   
    }

    fps = cap.get(CAP_PROP_FPS);
    delay = 1000 / fps;

    while(1) {

        cap >> frame;

        if(frame.empty()) {
            cout << "end of video" << endl;
            break;
        }

        // 사용자의 입력을 받는다. 
        char input = waitKey(delay);

        // 사용자의 입력을 받고 그 입력한 값이 현재 모드가 되어야 함. 
        // 중간에 재생중에 누르면 바뀌어야 하기 때문에 switch 두번 사용함

        switch (input)
        {
            case 'n':
                current_mode = 1;
                break;
            case 'g':
                current_mode = 2;
                break;
            case 'h':
                current_mode = 3;
                break;
            case 's':
                current_mode = 4;
                break;
            case 'c':
                current_mode = 5;
                break;
            case 'a':
                current_mode = 6;
                break;
            case 'u':
                current_mode = 7;
                break;
            case 'w':
                current_mode = 8;
                break;
            case 'r':
                current_mode = 9;
                break;
        }

        changed = frame.clone();

        // 그리고 나서 그 모드로 재생한다. 
            switch (current_mode)
        {
            case 1:
                negative_transformation(frame, changed);
                break;

            case 2:
                gamma_transformation(frame, changed);
                break;

            case 3:
                histogram_equalization(frame, changed);
                break;

        
            case 4:
                color_slicing(frame, changed);
                break;

        
            case 5:
                color_change(frame, changed);
                break;

        
            case 6:
                average_filtering(frame, changed);
                break;

        
            case 7:
                unsharp_masking(frame, changed);
                break;

        
            case 8:
                white_balancing(frame, changed);
                break;

        
            case 9:
                reset_image(frame, changed);
                break;
        }

        imshow("video.mp4", changed);
        
    }

    return 0;

}