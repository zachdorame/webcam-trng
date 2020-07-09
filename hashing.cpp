#include "hashing.h"
#include <iostream>


//this is extremely slow :(
int hashMat(const cv::Mat& src, int limit) {
	std::string hashString;

	for (cv::MatConstIterator_<char> it = src.begin<char>(); it != src.end<char>(); ++it) {
		hashString += *it;
	}

	std::hash<std::string> hash;

	return hash(hashString)%(limit);
}


//MUCH faster

//behavior: repeated hashes for unmoving images
// < 2% repeated hashes ---> a moving image
//double quickHash(const cv::Mat& src, int limit)
double quickHash(cv::Mat& src, int limit) {
	double hash = 0.0;
	
	//could be done faster with pointer accesses???
	//char temp = 0;
	//std::cout << "DISPLAYING WORK\n";

	//for (cv::MatConstIterator_<char> it = src.begin<char>(); it != src.end<char>(); ++it) {
	//	//std::cout << *it << " ";
	//	hash = (hash + *it & limit) & limit;
	//}

	//std::cout << std::endl;
	//std::cout << "BEGIN DUMP" << std::endl; // dump
	for (int row = 0; row < src.rows; ++row) {
		const int* ptr = src.ptr<int>(row);
		for (int col = 0; col < src.cols; ++col) {
			//std::cout << *ptr << " "; // dump
			//hash = (hash + (*ptr++)) & limit;
			hash = abs(fmod(((*ptr++) + hash), limit)); //this seems to work as intended
		}
	}

	//std::cout << "END DUMP" << std::endl;

	return hash;

}