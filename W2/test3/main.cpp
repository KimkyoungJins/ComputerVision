#include <iostream>
#include <opencv2/opencv.hpp>


// Log transformation
int main() {
    // 1. 이미지를 흑백으로 로드
    cv::Mat image = cv::imread("lena.png", cv::IMREAD_GRAYSCALE);

    if (image.empty()) {
        std::cerr << "Error: Image file not found or could not be opened." << std::endl;
        return -1;
    }

    // 2. 이미지를 float 타입으로 변환 (로그 변환을 위해)
    cv::Mat float_img;
    image.convertTo(float_img, CV_32F);

    // 3. 로그 변환 수행: log(1 + I)
    // 픽셀 값에 1을 더한 후 로그를 취합니다.
    cv::Mat log_transformed_img;
    cv::log(1 + float_img, log_transformed_img);

    // 4. 결과를 0-255 범위로 정규화
    // 시각화를 위해 픽셀 값을 0-255 범위로 스케일링합니다.
    cv::Mat normalized_img;
    cv::normalize(log_transformed_img, normalized_img, 0, 255, cv::NORM_MINMAX);

    // 5. 8비트 unsigned char 타입으로 변환
    // imshow() 함수는 보통 8비트 또는 16비트 정수형을 사용하므로,
    // 정규화된 float 이미지를 다시 8비트 정수형으로 변환합니다.
    cv::Mat final_log_img;
    normalized_img.convertTo(final_log_img, CV_8U);

    // 6. 결과 출력
    cv::imshow("Original Image", image);
    cv::imshow("Log Transformation", final_log_img);

    cv::waitKey(0);

    return 0;
}