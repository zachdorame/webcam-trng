#pragma once
#include <opencv2/opencv.hpp>

//uses video stream to generate a random number
int rand(int limit);

//caller opens video stream and sends it
int rand(int limit, cv::VideoCapture& cam);

class random {
public:
	random(cv::VideoCapture& src);
	~random() { delete[] nums; }
	void generateRand(cv::Mat& img);
	int getRand();
private:
	int* nums;
	cv::VideoCapture& cam;
	int i = 0;
	int size;
};