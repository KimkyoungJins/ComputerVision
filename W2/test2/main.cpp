#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    // 1. 이미지를 흑백으로 로드
    cv::Mat image = cv::imread("lena.png", cv::IMREAD_GRAYSCALE);

    // 2. 이미지 로드 성공 여부 확인
    if (image.empty()) {
        std::cerr << "Error: Image not found or could not be opened." << std::endl;
        return -1;
    }

    cv::Mat negative_image;

    // 3. OpenCV의 벡터화 연산 'subtract'를 사용하여 음화 변환
    // 255에서 각 픽셀 값을 빼는 연산을 수행합니다.
    cv::subtract(cv::Scalar::all(255), image, negative_image);

    // 4. 결과 출력
    cv::imshow("Original Image", image);
    cv::imshow("Negative Transformation", negative_image);

    cv::waitKey(0);

    return 0;
}