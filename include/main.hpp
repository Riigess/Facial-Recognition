#include <iostream>
#include <opencv4/opencv2/dnn.hpp>
#include <opencv2/opencv.hpp>

#ifndef VISUALS_FACEDETECTOR_H
#define VISUALS_FACEDETECTOR_H

class FaceDetector {
    public:
        explicit FaceDetector();
        /// Detect faces in an image frame
        /// \param frame Image to detect faces in
        /// \return Vector of detected faces
        std::vector<cv::Rect> detect_face_rectangles(const cv::Mat &frame);
    private:
        /// Face detection network
        cv::dnn::Net network_;
        ///Input image width
        const int input_image_width_;
        const int input_image_height_;
        const double scale_factor_;
        const cv::Scalar mean_values_;
        cont float confidence_threshold_;
}
#endif //VISUALS_FACEDETECTOR_H