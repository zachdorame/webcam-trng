#include "stats.h"
#include "rand.h"
float chiSquare(int* freqs, int frames) { //NOTE: freqs is of known size 100, since k = 100
	float chiSq = 0;
	int i = 0;
	float expectVal = frames/100; //This function will only be used to test hash-values from 0-99
	//std::cout << expectVal << " ";
	while(i != 100) {
		//std::cout << i << " : " << *freqs << " " << std::endl;
		chiSq += ((double)((*freqs - expectVal) * (*freqs++ - expectVal))) / expectVal;
		++i;
	}

	return chiSq;
}

//this function is meant to be exited by user, but we'll just run it a hundred times.... TODO!!!
//TODO: display video live
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

	//init with 100 values
	while (k < 100) {
		current_num = rand(100, cam); //might be ambiguous
		++freqs[current_num];
		nums.push_front(current_num);
		++k;
	}

	k = 0; //arbitrarily run 100 times
	int chiSq;
	while (k < 100) {
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