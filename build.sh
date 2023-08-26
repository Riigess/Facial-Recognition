#!/bin/bash
rm -rf build
mkdir build
cmake CMakeLists.txt -S src -B build
if [ -f build/FaceDetction]; then
	build/FaceDetection $1
else
	cd build
    make
    ./FaceDetection $1
fi
