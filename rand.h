#pragma once
#include <opencv2/opencv.hpp>

//uses video stream to generate a random number
//NOTE: handle case where video stream does not open
int rand(int limit);

//caller opens video stream and sends it
int rand(int limit, cv::VideoCapture& cam);