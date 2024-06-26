#include "../include/main.hpp"
#include <iostream>

FaceDetector::FaceDetector() :
    confidence_threshold_(0.5),
    input_image_height_(300),
    input_image_width_(300),
    scale_factor_(1.0),
    mean_values_({104.,177.0,123.0}) {
        network_ = cv::dnn::readNetFromCaffe(FACE_DETECTION_CONFIGURATION, FACE_DETECTION_WEIGHTS);
        if(network_.empty()) {
            std::ostringstream ss;
            ss << "Failed to load network with the following settings:\n" << "Configuration: " + std::string(FACE_DETECTION_CONFIGURATION) + "\n" << "Binary: " + std::string(FACE_DETECTION_WEIGHTS) + "\n";
            throw std::invalid_argument(ss.str());
        }
    }

std::vector<cv::Rect> FaceDetector::detect_face_rectangles(const cv::Mat &frame) {
    cv::Mat input_blob = cv::dnn::blobFromImage(frame,
        scale_factor_,
        cv::Size(input_image_width_, input_image_height_),
        mean_values_,
        false,
        false);
    network_.setInput(input_blob, "data");
    cv::Mat detection = network_.forward("detection_out");
    cv::Mat detection_matrix(detection.size[2],
        detection.size[3],
        CV_32F,
        detection.ptr<float>());
    std::vector<cv::Rect> faces;
    for(int i = 0; i < detection_matrix.rows; i++) {
        float confidence = detection_matrix.at<float>(i, 2);
        if(confidence < confidence_threshold_) {
            continue;
        }
        int x_left_bottom = static_cast<int>(detection_matrix.at<float>(i, 3) * frame.cols);
        int y_left_bottom = static_cast<int>(detection_matrix.at<float>(i, 4) * frame.rows);
        int x_right_top = static_cast<int>(detection_matrix.at<float>(i, 5) * frame.cols);
        int y_right_top = static_cast<int>(detection_matrix.at<float>(i, 6) * frame.rows);
        faces.emplace_back(x_left_bottom, y_left_bottom, (x_right_top - x_left_bottom), (y_right_top - y_left_bottom));
    }
    return faces;
}

int main(int argc, char **argv) {
    std::cout << "You have entered " << argc << " arguments:" << std::endl;
    bool isFaceDetection = false;
    bool isShowLines = false;
    for(int i = 0; i < argc; i++) {
        std::cout << "\t" << argv[i] << std::endl;
        if(strcmp(argv[i], "--face-detection") == 0) {
            isFaceDetection = true;
        }
        if(strcmp(argv[i], "--show-lines") == 0) {
            isShowLines = true;
        }
    }

    cv::VideoCapture vCap;
    if(!vCap.open(0)) {
        return 0;
    }
    if(isFaceDetection) {
        FaceDetector face_detector;
        //Create Mat to hold the frame and display it (in an infinite loop)
        cv::Mat frame;
        while(true) {
            vCap >> frame;
            
            auto rectangles = face_detector.detect_face_rectangles(frame);
            cv::Scalar color(0,105,205);
            int frame_thickness = 4;
            for(const auto & r : rectangles) {
                cv::rectangle(frame, r, color, frame_thickness);
            }
            cv::imshow("Image", frame);
            const int esc_key = 27;
            if(cv::waitKey(10) == esc_key) {
                break;
            }
        }
    } else if(isShowLines) {
        cv::Mat frame, edges;
        cv::namedWindow("edges", cv::WINDOW_AUTOSIZE);

        for(;;) {
            vCap >> frame;
            cv::cvtColor(frame, edges, cv::COLOR_BGR2GRAY);
            cv::GaussianBlur(edges, edges, cv::Size(7,7), 1.5, 1.5);
            cv::Canny(edges, edges, 0, 30, 3);
            cv::imshow("edges", edges);
            if(cv::waitKey(30) >= 0) break;
        }
    } else {
        std::cout << "No options selected. Please add an option and try again." << std::endl;
    }
    cv::destroyAllWindows();
    vCap.release();
    return 0;
}
