#include <iostream>
#include <opencv2/opencv.hpp>

int main() {

    // Use Mat object
    cv::Mat image, image_gray;

    // int channels and the BGR,
    int value, value_B, value_G, value_R, channels;


    // Mat 안에 있는 cv:: 
    image = cv::imread("lena.png");

    // <> 안에 접근하고자 하는 데이터 타입의 값을 정확하게 입력 해야한다. 
    value = image_gray.at<uchar>(50, 10);

    //Value 값을 보여준다. 
    std::cout << "Value: " << value << std::endl;

    value_B = image.at<cv::Vec3b>(50, 100)[0];

    value_G = image.at<cv::Vec3b>(50, 100)[1];

    value_R = image.at<cv::Vec3b>(50, 100)[2];

    std:: cout << "value at (100, 50): " << value_B << " " << value_G << " " << value_R << std::endl;
    cv::waitKey(0);
    
    return 0;

}
