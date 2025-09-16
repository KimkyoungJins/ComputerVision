#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    // 1. 이미지를 흑백으로 로드
    cv::Mat image = cv::imread("lena.png", cv::IMREAD_GRAYSCALE);

    if (image.empty()) {
        std::cerr << "Error: Image file not found or could not be opened." << std::endl;
        return -1;
    }

    // 2. 감마 값 설정 (gamma > 1은 어둡게, gamma < 1은 밝게)
    float gamma = 0.5f;

    // 3. 256개 픽셀 값에 대한 감마 보정 룩업 테이블(LUT) 생성
    cv::Mat lookUpTable(1, 256, CV_8U);
    unsigned char* p = lookUpTable.ptr();
    for (int i = 0; i < 256; ++i) {
        // 감마 변환 공식: (i / 255.0)^gamma * 255
        p[i] = cv::saturate_cast<unsigned char>(pow(i / 255.0, gamma) * 255.0);
    }

    // 4. LUT를 이미지에 적용하여 감마 보정 수행
    cv::Mat gamma_image;
    cv::LUT(image, lookUpTable, gamma_image);

    // 5. 결과 출력
    cv::imshow("Original Image", image);
    cv::imshow("Gamma Transformation", gamma_image);

    cv::waitKey(0);

    return 0;
}