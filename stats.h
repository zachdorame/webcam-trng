#pragma once
#include <opencv2/opencv.hpp>
#include <list>
std::vector<float> deltaRand(cv::VideoCapture cam, int frames);

//we know that k = 100
//nums -- a forward list of the FREQUENCY with which numbers show up
float chiSquare(int* freqs, int frames);