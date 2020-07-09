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
		cv::cvtColor(frame, frame, cv::COLOR_RGB2GRAY);
		int asdf = quickHash(frame, limit);
		//std::cout << "YOUR RANDOM NUMBER IS " << asdf << std::endl;
		return asdf;
	}
	return -1; //Error, cam was not opened
}