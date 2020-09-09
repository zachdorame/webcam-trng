#include "stats.h"
#include "rand.h"
float chiSquare(int* freqs, float frames) { 
	float chiSq = 0;
	int i = 0;
	float expectVal = frames/100; //This function will only be used to test hash-values from 0-99
	while(i != 100) {
		//std::cout << i << " : " << *freqs << " " << std::endl;
		chiSq += ((double)((*freqs - expectVal) * (*freqs++ - expectVal))) / expectVal;
		++i;
	}

	return chiSq;
}


std::vector<float> deltaRand(cv::VideoCapture cam, int frames) {
	//k = 100
	float ALPHA = 123.225;
	int k = 0;
	int current_num;
	std::vector<float> deltaRand; //randomness over time
	//std::vector<int> freqs; //frequency for which numbers appear
	int freqs[101]; //TODO: tidy
	for (int i = 0; i < 101; ++i) {
		freqs[i] = 0;
	}

	//DEBUG
	//std::cout << "DELTA RAND FREQS " << std::endl;
	//for (int i = 0; i != 100; ++i) {
	//	std::cout << freqs[i] << " ";
	//}
	//DEBUG

	std::list<int> nums; //list of numbers
	//cam.open(0);

	//init with frames values
	while (k < frames) {
		current_num = rand(100, cam); //might be ambiguous
		++freqs[current_num];
		nums.push_front(current_num);
		++k;
	}

	k = 0; //arbitrarily run frames times
	int chiSq;
	while (k < frames) {
		chiSq = chiSquare(freqs, frames);
		chiSq < ALPHA ? std::cout << chiSq << " : " << " RANDOM" << std::endl : std::cout << chiSq << " : " << " NOT RANDOM" << std::endl;
		deltaRand.push_back(chiSq);

		//produce another random number
		--freqs[nums.front()];
		nums.pop_back();
		current_num = rand(100, cam);
		++freqs[current_num];
		nums.push_front(current_num);
		++k;
	}

	//delete[] freqs;
	return deltaRand;
}

void cvSwap(cv::Mat& src, int x1, int y1, int x2, int y2) {
	if (false) {
		std::cout << "SIZE DUMP" << std::endl;
		std::cout << "src dims\n";
		std::cout << src.rows << " x " << src.cols << std::endl;
		std::cout << x1 << std::endl;
		std::cout << y1 << std::endl;
		std::cout << x2 << std::endl;
		std::cout << y2 << std::endl;
	}
	cv::Vec3b* src_ptr = src.ptr<cv::Vec3b>(x1);
	src_ptr += y1;
	cv::Vec3b* src2_ptr = src.ptr<cv::Vec3b>(x2);
	src2_ptr += y2;
	cv::Vec3b temp = *src_ptr;
	*src_ptr = *src2_ptr;
	*src2_ptr = temp;


//	int temp = src.at<uchar>(x1, y1);
//	src.at<uchar>(x1, y1) = src.at<uchar>(x2, y2);
//	src.at<uchar>(x2, y2) = temp;
}

void imgScramble(const cv::Mat& src, cv::VideoCapture& cam) { 
	cv::Mat dest = src; //copy src to dest
	cv::namedWindow("Scramble", cv::WINDOW_AUTOSIZE);
	int max = (src.cols * src.rows);

	random ranum(cam);

	cv::imshow("Scramble", dest);
	cv::waitKey(1);

	int rand_num;
	for (int i = 0; i < src.rows; ++i) {
		for (int j = 0; j < src.cols; ++j) {
			cv::imshow("Scramble", dest);
			cv::waitKey(1);
			//rand_num = rand(RAND_MAX, cam);
			rand_num = ranum.getRand();
			//cvSwap(dest, i, j, rand_num%src.rows, rand_num%src.cols);
			cvSwap(dest, i, j, ranum.getRand()%src.rows, ranum.getRand() % src.cols); //CURRENTLY WORKS BEST
			//cvSwap(dest, ranum.getRand() % src.rows, ranum.getRand() % src.cols, ranum.getRand() % src.rows, ranum.getRand() % src.cols);
			//cvSwap(dest, i, j, rand()%src.rows, rand()%src.cols); //<-- compete with this
		}
	}
}