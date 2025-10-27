#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    
    Mat image, edge, result;

    image = imread("chess_pattern.png"); // 이미지를 읽어옵니다[cite: 126].
    if (image.empty()) {
        cout << "이미지 파일을 찾을 수 없습니다." << endl;
        return -1;
    }

    result = image.clone();

    cvtColor(image, image, COLOR_BGR2GRAY); // 흑백으로 변환[cite: 128].

    Canny(image, edge, 50, 200, 3); // Canny 엣지 검출.

    vector<Vec4i> lines; // 검출된 선분을 저장할 벡터[cite: 125].

    HoughLinesP(edge, lines, 1, CV_PI / 180, 50, 10, 300); // 확률적 허프 변환 적용[cite: 136].


    // 검출한 모든 라인데 For문을 통해서 접근한다. 
    for (size_t i = 0; i < lines.size(); i++) {

        Vec4i l = lines[i]; // (x1, y1, x2, y2) 좌표를 가져옵니다[cite: 139].
        // 검출된 선분의 두 점을 사용하여 원본 이미지에 빨간색 선을 그립니다[cite: 140].
        line(result, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, 8);
    }

    imshow("HoughLinesP Result", result);
    waitKey(0);
    return 0;
}