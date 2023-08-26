cmake_minimum_required(VERSION 3.21)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

project(FaceDetection LANGUAGES CXX)

# set(OpenCV_DIR /opt/homebrew/Cellar/opencv/4.8.0_1/include/opencv4)
set(FACE_DETECTION_CONFIGURATION "${PROJECT_SOURCE_DIR}/../assets/deploy.prototxt")
set(FACE_DETECTION_WEIGHTS "${PROJECT_SOURCE_DIR}/../assets/res10_300x300_ssd_iter_140000_fp16.caffemodel")
set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp)

find_package(OpenCV REQUIRED)

# include_directories("/opt/homebrew/Cellar/opencv/4.8.0_1/include/opencv4")

target_include_directories(${PROJECT_NAME} PUBLIC "include/")

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_compile_definitions(${PROJECT_NAME} PRIVATE FACE_DETECTION_CONFIGURATION="${FACE_DETECTION_CONFIGURATION}")
target_compile_definitions(${PROJECT_NAME} PRIVATE FACE_DETECTION_WEIGHTS="${FACE_DETECTION_WEIGHTS}")
