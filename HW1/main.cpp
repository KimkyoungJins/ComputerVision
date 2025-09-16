#include <iostream>
#include <opencv2/opencv.hpp>


// 21900066 Computer vision 2분반 김경진 과제 1

int main() {
    using namespace cv;
    using namespace std;

    VideoCapture cap;
    Mat frame;      

    double fps;              
    int total_frames;        
    int delay;              


    // Read the video background.mp4
    if(cap.open("background.mp4") == 0){
        cout << "no file" << endl;
        return -1;
    }

    fps = cap.get(CAP_PROP_FPS);                            // frame of video 
    total_frames = cap.get(CAP_PROP_FRAME_COUNT);           // total frames


    delay = 1000 / fps;                                     // parameter for waitKey()

    // To display the video for 3 seconds, 
    // get the frame of the video and multiply 3
    double three_sec = fps * 3;
    for (int i = 0; i < three_sec; i++){
        cap >> frame;

        if(frame.empty()) {
            cout << "end of video" << endl;
            return -1;
        }

        imshow("video", frame);

        // print out the number of current frame and the total number of frames
        std::cout << "Current Frame  " << i + 1 << " / " << total_frames << std::endl;

        waitKey(delay);         // find out the proper input parameter for waitkey()
    }

    return 0;
}