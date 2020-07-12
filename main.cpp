#include <iostream>
#include <opencv2/opencv.hpp>
#include "hashing.h"
#include "stats.h"
#include "rand.h"

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


//int main() {
//	const int FRAMES = 256;
//	cv::VideoCapture yeet;
//
//	yeet.open(0);
//	if (yeet.isOpened()) {
//		std::vector<float> rand_dt;
//		rand_dt = deltaRand(yeet, FRAMES);
//
//		for (float i : rand_dt) {
//			std::cout << i << " ";
//		}
//	}
//
//	return 0;
//}

void menu() {
	std::cout << "(a) generate a random number" << std::endl;
	std::cout << "(b) check if source is random" << std::endl;
	std::cout << "(c) randomly scramble an image" << std::endl;
}


int main() { //should open video stream  

	cv::VideoCapture vidStream;
	vidStream.open(0);
	if (vidStream.isOpened()) {
		std::cout << "Camera successfully accessed " << std::endl;
	}
	else {
		std::cout << "Unable to access camera " << std::endl;
		return -1;
	}

	char response;
	bool a_val;
	while (true) {
		menu();
		std::cout << ">> ";
		std::cin >> response;
		response = tolower(response);
		switch (response) {
		case 'a':
			a_val = true;
			std::cout << "(1) to continue or (2) to quit" << std::endl;
			while (a_val) {
				std::cout << "Your random number is " << rand(RAND_MAX, vidStream)%100 << std::endl;
				std::cout << ">> ";
				std::cin >> response;
				if (response == '2') {
					a_val = false;
				}
				
			}
			break;
		case 'b':
			std::cout << "How many numbers between 0-99 will be generated?\n";
			std::cout << ">> ";
			std::cin >> response;
			deltaRand(vidStream, response);
			break;
		case 'c':
			cv::Mat src = cv::imread("C:\\Users\\Zach\\Pictures\\Roblox\\yeet.png", 1); //TODO: allow user to input their own image
			cv::resize(src, src, cv::Size(), 50.0/src.rows, 50.0/src.cols); //50.0/src.cols corresponds to 50 pixels
			imgScramble(src, vidStream);
		}

	}
	return 0;
}