#include <iostream>
#include <opencv2/opencv.hpp>
#include "hashing.h"
#include "stats.h"
#include "rand.h"


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

void menu() {
	std::cout << "(a) generate a random number" << std::endl;
	std::cout << "(b) check if source is random" << std::endl;
	std::cout << "(c) randomly scramble an image" << std::endl;
	std::cout << "(q) quit" << std::endl;
}

int main() {  

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
	bool b_val = true;
	while (b_val) {
		menu();
		std::cout << ">> ";
		std::cin >> response;
		response = tolower(response);
		switch (response) {
		case 'a':
		{
			a_val = true;
			std::cout << "(1) to continue or (2) to quit" << std::endl;
			while (a_val) {
				std::cout << "Your random number is " << rand(RAND_MAX, vidStream) % 100 << std::endl;
				std::cout << ">> ";
				std::cin >> response;
				if (response == '2') {
					a_val = false;
				}

			}
			break;
		}
		case 'b':
		{
			std::cout << "How many numbers will we test?\n";
			std::cout << ">> ";
			std::cin >> response;
			std::cout << "(Result from Chi-Square Test) :( Our determination if the input is good enough to be random)" << std::endl;
			deltaRand(vidStream, (float)response);
			break;
		}
		case 'c':
		{
			std::cout << "Enter full path of the image you'd like to scramble: " << std::endl;
			std::string fullPath;
			std::cin >> fullPath;
			cv::Mat src = cv::imread(fullPath, 1); 
			cv::resize(src, src, cv::Size(), 256.0 / src.rows, 256.0 / src.cols); //50.0/src.cols corresponds to 50 pixels
			imgScramble(src, vidStream);
			break;
		}
		case 'q':
		{
			b_val = false;
			break;
		}
		default:
		{
			std::cout << "Invalid input" << std::endl;
			break;
		}
		}

	}
	return 0;
}