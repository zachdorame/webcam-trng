#pragma once
#include <opencv2/opencv.hpp>
#include <list>
std::vector<float> deltaRand(cv::VideoCapture cam, int frames);

//we know that k = 100
//nums -- a forward list of the FREQUENCY with which numbers show up
float chiSquare(int* freqs, float frames);

//swaps two pixels on an image
void cvSwap(cv::Mat& src, int x1, int y1, int x2, int y2);

void imgScramble(const cv::Mat& src, cv::VideoCapture& cam);