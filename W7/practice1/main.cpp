#include <iostream>
#include <opencv2/opencv.hpp>

// using namespace cv; 를 이미 사용하고 있으므로 std::를 붙여주는 대신 using namespace std; 추가
using namespace cv;
using namespace std; 

// int main(){

//     // 1. 비디오 캡처 객체 생성
//     VideoCapture capture("background.mp4");

//     // 영상 파일이 제대로 열렸는지 확인
//     if (!capture.isOpened()) {
//         cout << "Error: 영상을 열 수 없습니다!" << endl;
//         return -1;
//     }

//     // 변수 선언: 배경, 현재 컬러 프레임, 현재 흑백 프레임, 마스크, 전경 이미지
//     Mat background, image, gray, foregroundMask, foregroundImg;

//     // 2. 초기 배경 설정
//     // set the first frame as background
//     capture >> background;
    
//     // 3. 배경 이미지를 흑백으로 변환 (반복문 밖에서 한 번만 수행)
//     cvtColor(background, background, CV_BGR2GRAY); 

//     cout << "배경 차감 시작. ESC를 눌러 종료하세요." << endl;

//     while(true){ // 무한 루프 시작

//         // 4. 프레임 캡처 및 읽기 (grab과 retrieve 분리 사용)
//         if(capture.grab() == false){ // grab()은 성공 시 true를 반환
//             break; // 더 이상 프레임이 없으면 종료
//         }

//         // 오타 수정: cpature -> capture
//         capture.retrieve(image); 

//         // 5. 현재 프레임을 흑백으로 변환 (background가 아닌 image를 gray로 변환)
//         cvtColor(image, gray, CV_BGR2GRAY);


//         // 6. 핵심 연산: 배경 차감 및 전경 분리
//         absdiff(background, gray, foregroundMask);
//         threshold(foregroundMask, foregroundMask, 50, 255, THRESH_BINARY); // CV_ 접두어 제거
        
//         // gray 이미지에서 마스크(foregroundMask)에 해당하는 영역만 foregroundImg에 복사
//         // foregroundImg 변수의 데이터 타입과 크기를 맞추기 위해 초기화 필요
//         foregroundImg = Mat::zeros(gray.size(), gray.type()); // foregroundImg를 검은색으로 초기화
//         gray.copyTo(foregroundImg, foregroundMask); 
    
//         // 7. 결과 출력 (창 이름 중복 및 오타 수정)
//         imshow("Foreground Image", foregroundImg);
//         imshow("Foreground Mask", foregroundMask);
//         imshow("Static Background", background);
        

//         if(waitKey(33) == 27){ // ESC 키(아스키코드 27)를 누르면 종료
//             break;
//         }
//     }
    
//     // 8. 자원 해제
//     capture.release();
//     destroyAllWindows();

//     return 0;
// }



// // 또 다른 메인 예시 
// // 배경 차감 효과의 예시이다. 
// int main(){

//     // 비디오 캡쳐 객체
//     VideoCapture capture("background.mp4");
//     // 이미지, 모은거, 평균 값
//     Mat image;
//     Mat sum;    // 
//     Mat avg;    // 초기 프레임을 읽어와서 avg 변수에 할당한다. 
//     Mat frame;

//     int cnt = 2;

//     // 동영상의 첫 번째 프레임을 변수에 저장한다. 
//     // 해당 이미지는 평군 계산의 시작점이다.
//     capture >> avg;

//     while(1){

//         if(!capture.read(image)){
//             break;
//         }

//         add(image / cnt,avg*(cnt - 1) / cnt, avg);

//         imshow("avg", avg);
//         cnt++;
//         waitKey(33);
//     }

//     return 0;
// }


int main(){

    // 1. 비디오 캡처 객체 생성
    VideoCapture capture("background.mp4");

    // 영상 파일이 제대로 열렸는지 확인
    if (!capture.isOpened()) {
        cout << "Error: 영상을 열 수 없습니다!" << endl;
        return -1;
    }

    // 변수 선언: 배경, 현재 컬러 프레임, 현재 흑백 프레임, 마스크, 전경 이미지
    Mat background, image, gray, foregroundMask, foregroundImg;

    // 2. 초기 배경 설정
    // set the first frame as background
    capture >> background;
    
    // 3. 배경 이미지를 흑백으로 변환 (반복문 밖에서 한 번만 수행)
    cvtColor(background, background, COLOR_BGR2GRAY); 

    cout << "배경 차감 시작. ESC를 눌러 종료하세요." << endl;

    while(true){ // 무한 루프 시작

        // 4. 프레임 캡처 및 읽기 (grab과 retrieve 분리 사용)
        if(capture.grab() == false){ // grab()은 성공 시 true를 반환
            break; // 더 이상 프레임이 없으면 종료
        }

        // 오타 수정: cpature -> capture
        capture.retrieve(image); 

        // 5. 현재 프레임을 흑백으로 변환 (background가 아닌 image를 gray로 변환)
        cvtColor(image, gray, COLOR_BGR2GRAY);


        // 6. 핵심 연산: 배경 차감 및 전경 분리
        absdiff(background, gray, foregroundMask);
        threshold(foregroundMask, foregroundMask, 50, 255, THRESH_BINARY); 
        
        // gray 이미지에서 마스크(foregroundMask)에 해당하는 영역만 foregroundImg에 복사
        foregroundImg = Mat::zeros(gray.size(), gray.type()); // foregroundImg를 검은색으로 초기화
        gray.copyTo(foregroundImg, foregroundMask); 
    
        // 7. 결과 출력 (창 이름 중복 및 오타 수정)
        imshow("Foreground Image", foregroundImg);
        imshow("Foreground Mask", foregroundMask);
        imshow("Static Background", background);
        

        if(waitKey(33) == 27){ // ESC 키(아스키코드 27)를 누르면 종료
            break;
        }
    }
    
    // 8. 자원 해제
    capture.release();
    destroyAllWindows();

    return 0;
}


