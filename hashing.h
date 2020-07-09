#pragma once
#include <opencv2/opencv.hpp>
#include<forward_list>


// src -- a black and white opencv array
// limit -- specifies the maximum hash value
// hashes a single frame to an integer
int hashMat(const cv::Mat& src, int limit);


//safe to use with apparently random video sources
double quickHash(cv::Mat& src, int limit);

