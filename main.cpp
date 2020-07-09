#include <iostream>
#include <opencv2/opencv.hpp>
#include "hashing.h"
#include "stats.h"

// take a video source
// analyze it for randomness
// display this as a gui somehow
//MIGHT HAVE TO DOWNSCALE VIDEO
//cvsize(x,y)

//todo (7/5/20)
// -- add a gui interface, CLEAN UP CODOE
// -- maybe add a shuffling algorithm to demonstrate randomness

//todo (7/8/2020)
// --visual studio seems to throw random read access violations... not sure how to handle those

void containsRepeats(int* arr, int len) {
	if (len == 0) return;
	int reps = 0;
	for (int i = 0; i < len - 1; ++i) {
		if (arr[i] == arr[i + 1]) {
			std::cout << "arr[" << i << "] = " << arr[i] << " and ";
			std::cout << "arr[" << i + 1 << "] = " << arr[i + 1] << std::endl;
			++reps;
		}
	}

	std::cout << "I counted " << reps << " repeats." << std::endl;
	std::cout << "Proportion repeated " << ((double)reps / len) * 100 << "%" << std::endl;
}


int main() {
	const int FRAMES = 256;
	cv::VideoCapture yeet;

	yeet.open(0);
	if (yeet.isOpened()) {
		std::vector<float> rand_dt;
		rand_dt = deltaRand(yeet, FRAMES);

		for (float i : rand_dt) {
			std::cout << i << " ";
		}
	}

	return 0;
}