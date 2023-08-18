#include "../include/main.hpp"

int main() {
    cv::VideoCapture vCap;
    if(!vCap.open(0)) {
        return 0;
    }
    //Create Mat to hold the frame and display it (in an infinite loop)
    cv::Mat frame;
    for(;;) {
        cv::vCap >> frame;
        imshow("Image", frame);
        const int esc_key = 27;
        if(cv::waitKey(10) == esc_key) {
            break;
        }
    }
    cv::destroyAllWindows();
    vCap.release();
    return 0;
}