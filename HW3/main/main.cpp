#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;


// // 이미지에 대한 행렬을 받아서 90도 로테이트
// Mat rotate_img_90(Mat image){

//     Mat result(image.rows, image.cols, image.type());

//         for(int i = 0; i < image.rows; i++){
//             for (int j = 0; j < image.cols; j++){
//                 result.at<uchar>(j, image.rows - 1 - i) = image.at<uchar>(i, j);
//             }
//         }

//     return result;  
// }


// Mat left_half(Mat image){

//     Mat result(image.rows, image.cols, image.type());
//     Rect rec(100, 30, 250, 300);
// }
// Mat right_half(Mat image){

//     Mat result(image.rows, image.cols, image.type());
//     if(image.rows % 2 == 0){
        
//     }

// }


// Mat left_half(Mat image){

// }



int main()
{

    Mat image;
    // Mat laplacian, abs_laplacian, sharpening;
    Mat gausian_blurr;
    Mat unsharp;
    Mat result;
    
    image = imread("moon.png", 0);
    imshow("before", image);

    GaussianBlur(image, gausian_blurr, Size(3, 3), 0, 0, BORDER_DEFAULT);
    unsharp = image - gausian_blurr;
    result = image + (unsharp * 1);

    imshow("result", result);

    // Laplacian(image, laplacian, CV_16S, 1, 1, 0);
    // convertScaleAbs(laplacian, abs_laplacian);
    // sharpening = abs_laplacian + image;
    // imshow("after", sharpening);

    waitKey(0);
    return 0;
}