#include <iostream>
#include <vector> // vector 사용을 위해 추가
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

/*
21900066 김경진 컴퓨터 비전 프로젝트 1
제공된 PDF 자료 기반 코드 완성본
*/

// 'n' 키: 네거티브 변환
void negative_transformation(Mat current, Mat& changed) {
    // PDF 로직 응용
    // 컬러 이미지(Vec3b)에 대해 각 채널(B, G, R)에 네거티브 변환 적용
    changed = current.clone();
    for (int y = 0; y < current.rows; ++y) {
        for (int x = 0; x < current.cols; ++x) {
            Vec3b& pixel = changed.at<Vec3b>(y, x);
            pixel[0] = 255 - pixel[0]; // Blue
            pixel[1] = 255 - pixel[1]; // Green
            pixel[2] = 255 - pixel[2]; // Red
        }
    }
}

// 'g' 키: 감마 변환
void gamma_transformation(Mat current, Mat& changed) {
    // PDF 로직 응용
    // 컬러 이미지의 각 채널에 동일한 감마 변환 조회 테이블(LUT) 적용
    float gamma = 2.5; // 요구사항에 명시된 감마 값
    unsigned char pix[256];
    for (int i = 0; i < 256; i++) {
        pix[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f);
    }

    changed = current.clone();
    for (int y = 0; y < current.rows; y++) {
        for (int x = 0; x < current.cols; x++) {
            Vec3b& pixel = changed.at<Vec3b>(y, x);
            pixel[0] = pix[pixel[0]];
            pixel[1] = pix[pixel[1]];
            pixel[2] = pix[pixel[2]];
        }
    }
}

// 'h' 키: 히스토그램 평활화
void histogram_equalization(Mat current, Mat& changed) {
    // PDF 이론 및 함수 응용
    // 컬러 이미지의 밝기 채널에만 평활화 적용
    Mat ycrcb;
    cvtColor(current, ycrcb, COLOR_BGR2YCrCb); // YCrCb 컬러 공간으로 변환
    vector<Mat> channels;
    split(ycrcb, channels); // 채널 분리

    equalizeHist(channels[0], channels[0]); // Y 채널(밝기)에만 평활화 적용

    merge(channels, ycrcb); // 채널 병합
    cvtColor(ycrcb, changed, COLOR_YCrCb2BGR); // 다시 BGR로 변환
}

// 's' 키: 컬러 슬라이싱 (주황색 추출)
void color_slicing(Mat current, Mat& changed) {
    // PDF 로직 응용
    // HSV 공간에서 주황색(Hue: 9-23)을 제외한 나머지 색상의 채도(Saturation)를 0으로 만듦
    Mat hsv;
    cvtColor(current, hsv, COLOR_BGR2HSV);
    vector<Mat> channels;
    split(hsv, channels);

    for (int j = 0; j < hsv.rows; j++) {
        uchar* h = channels[0].ptr<uchar>(j);
        uchar* s = channels[1].ptr<uchar>(j);
        for (int i = 0; i < hsv.cols; i++) {
            if (h[i] > 9 && h[i] < 23) {
                // 주황색 범위 내에 있으면 채도를 유지
            }
            else {
                s[i] = 0; // 그 외에는 채도를 0으로 만들어 무채색으로 변경
            }
        }
    }
    merge(channels, hsv);
    cvtColor(hsv, changed, COLOR_HSV2BGR);
}

// 'c' 키: 색상 변환
void color_change(Mat current, Mat& changed) {
    // PDF 로직 응용
    // 모든 픽셀의 색상(Hue) 값을 50씩 이동시켜 전체적인 색감을 변경
    Mat hsv;
    cvtColor(current, hsv, COLOR_BGR2HSV);
    vector<Mat> channels;
    split(hsv, channels);

    for (int j = 0; j < hsv.rows; j++) {
        uchar* h = channels[0].ptr<uchar>(j);
        for (int i = 0; i < hsv.cols; i++) {
            if (h[i] + 50 > 179) { // OpenCV의 Hue 범위는 0-179
                h[i] = h[i] + 50 - 179; // 범위를 넘어가면 순환
            }
            else {
                h[i] = h[i] + 50;
            }
        }
    }
    merge(channels, hsv);
    cvtColor(hsv, changed, COLOR_HSV2BGR);
}

// 'a' 키: 평균 필터링
void average_filtering(Mat current, Mat& changed) {
    // PDF 함수 응용
    blur(current, changed, Size(5, 5));
}

// 'u' 키: 언샵 마스킹
void unsharp_masking(Mat current, Mat& changed) {
    // PDF 이론 응용
    // g(x,y) = f(x,y) + k * (f(x,y) - f_blurred(x,y))
    Mat blurred;
    GaussianBlur(current, blurred, Size(5, 5), 1.5);
    // 위 공식은 addWeighted를 사용하여 g = (1+k)*f - k*f_blurred 로 표현 가능
    double k = 1.0;
    addWeighted(current, 1 + k, blurred, -k, 0, changed);
}

// 'w' 키: 화이트 밸런싱
void white_balancing(Mat current, Mat& changed) {
    // PDF 코드 로직 응용 (Gray World Assumption 기반)
    changed = current.clone();
    vector<Mat> bgr_channels;
    split(changed, bgr_channels);

    for (int c = 0; c < 3; c++) {
        double avg = mean(bgr_channels[c])[0];
        if (avg == 0) continue; // 0으로 나누는 것을 방지
        double scale = 128.0 / avg;

        // 각 채널에 스케일 적용
        for (int i = 0; i < changed.rows; i++) {
            uchar* p = bgr_channels[c].ptr<uchar>(i);
            for (int j = 0; j < changed.cols; j++) {
                p[j] = saturate_cast<uchar>(p[j] * scale);
            }
        }
    }
    merge(bgr_channels, changed);
}

// 'r' 키: 원본 이미지로 리셋
void reset_image(Mat current, Mat& changed) {
    current.copyTo(changed);
}


int main() {
    VideoCapture cap;
    Mat frame, changed;
    int fps;
    int delay;
    int current_mode = 9; // 현재 진행되고 있는 모드 (9는 원본)

    // 비디오 오픈
    if (cap.open("video.mp4") == 0) {
        cout << "not such file!\n" << endl;
        waitKey(0);
        return -1; // 파일이 없을 경우 종료
    }

    fps = cap.get(CAP_PROP_FPS);
    delay = 1000 / fps;

    cout << "--- 조작 키 ---" << endl;
    cout << "'n': 네거티브" << endl;
    cout << "'g': 감마 변환" << endl;
    cout << "'h': 히스토그램 평활화" << endl;
    cout << "'s': 컬러 슬라이싱" << endl;
    cout << "'c': 색상 변환" << endl;
    cout << "'a': 평균 필터링" << endl;
    cout << "'u': 언샵 마스킹" << endl;
    cout << "'w': 화이트 밸런싱" << endl;
    cout << "'r': 원본으로 리셋" << endl;
    cout << "ESC: 종료" << endl;
    cout << "---------------" << endl;


    while (1) {
        cap >> frame;

        if (frame.empty()) {
            cout << "end of video" << endl;
            break;
        }

        // 사용자의 입력을 받는다.
        int input = waitKey(delay);
        if (input == 27) break; // ESC 키 누르면 종료

        // 사용자의 입력을 받고 그 입력한 값이 현재 모드가 되어야 함.
        switch (input) {
        case 'n': current_mode = 1; break;
        case 'g': current_mode = 2; break;
        case 'h': current_mode = 3; break;
        case 's': current_mode = 4; break;
        case 'c': current_mode = 5; break;
        case 'a': current_mode = 6; break;
        case 'u': current_mode = 7; break;
        case 'w': current_mode = 8; break;
        case 'r': current_mode = 9; break;
        }

        // 그리고 나서 그 모드로 재생한다.
        switch (current_mode) {
        case 1: // negative
            negative_transformation(frame, changed);
            break;
        case 2: // gamma
            gamma_transformation(frame, changed);
            break;
        case 3: // Histogram
            histogram_equalization(frame, changed);
            break;
        case 4: // color slicing
            color_slicing(frame, changed);
            break;
        case 5: // color change
            color_change(frame, changed);
            break;
        case 6: // average filtering
            average_filtering(frame, changed);
            break;
        case 7: // unsharp masking
            unsharp_masking(frame, changed);
            break;
        case 8: // white balancing
            white_balancing(frame, changed);
            break;
        case 9: // regular mode (reset)
            reset_image(frame, changed);
            break;
        default: // 이전 상태 유지
            // changed 이미지가 비어있을 경우에만 초기화
            if (changed.empty()) {
                reset_image(frame, changed);
            }
            break;
        }

        imshow("Project Video - Press Keys to Change Mode", changed);
    }

    cap.release(); // 비디오 캡쳐 객체 해제
    destroyAllWindows(); // 모든 창 닫기

    return 0;
}