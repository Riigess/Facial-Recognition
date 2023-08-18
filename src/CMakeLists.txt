cmake_minimum_required(VERSION 3.21)
project(FaceDetection LANGUAGES CXX)

find_package(OpenCV REQUIRED)

# set( TARGET ${PROJECT_NAME} )
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_CXX_STANDARD 20)
# set( SOURCE_PATH "${PROJECT_SOURCE_DIR}/src")
# set( INCLUDE_PATH "${PROJECT_SOURCE_DIR}/include")

# file( GLOB_RECURSE HS "${INCLUDE_PATH}/*.h")
# file( GLOB_RECURSE CPPS "${SOURCE_PATH}/*.cpp")

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC "include/")

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
# target_compile_options(${TARGET} PRIVATE -Wall -Wextra -Wshadow -Wconversion -Wsign-conversion -Wunused-parameter -Wno-long-long -pedantic)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
