#include "rand.h"
#include "hashing.h"
int rand(int limit) {
	cv::Mat frame;
	cv::VideoCapture cam;
	cam.open(0); 
	cam >> frame;
	cv::cvtColor(frame, frame, cv::COLOR_RGB2GRAY);
	return quickHash(frame, limit); 
}

int rand(int limit, cv::VideoCapture& cam) {
	if (cam.isOpened()) {
		cv::Mat frame;
		cam >> frame;
		cv::resize(frame, frame, cv::Size(), 100.0 / frame.rows, 100.0 / frame.cols); //might cause errors
		cv::cvtColor(frame, frame, cv::COLOR_RGB2GRAY);
		int asdf = quickHash(frame, limit);
		return asdf;
	}
	return -1; //Error, cam was not opened
}


random::random(cv::VideoCapture& src) : cam(src) {
	cv::Mat frame;
	cam >> frame;
	size = frame.rows * frame.cols;
	nums = new int[size];
	generateRand(frame);
	int i = 0;
}


void random::generateRand(cv::Mat& img) {
	int j = 0;
	cv::cvtColor(img, img, cv::COLOR_RGB2GRAY);
	for (cv::MatConstIterator_<uchar> it = img.begin<uchar>(); it != img.end<uchar>(); ++it) {
		nums[j++] = *it;
	}

	i = 0;
}

int random::getRand() {
	if (i < size) {
		std::time_t scramble = std::time(nullptr);
		return nums[i++]* (scramble % 1000);
	}
	else {
		std::cout << "GENERATING A NEW RANDOM NUMBER " << std::endl;
		std::time_t scramble = std::time(nullptr);
		cv::Mat frame;
		cam >> frame;
		generateRand(frame);
		return nums[i++]*(scramble%1000);
	}
}