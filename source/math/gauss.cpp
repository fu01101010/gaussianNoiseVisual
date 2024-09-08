#include "gauss.h"
#include <iostream>

gaussDataSet::gaussDataSet() {}

gaussDataSet::gaussDataSet(int size, float mean = 0.0f, float sdev = 2.0f, float disp = 1.0f) : size(size), mean(mean), sdev(sdev), disp(disp) {

	init();
}

void gaussDataSet::init() {
	
	/*
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(mean, sdev);

	for (int i = 0; i < size; ++i) {

		DataSet.at(i) = distribution(generator);
	}
	*/
}

void gaussDataSet::print() {
	
	/*
	for (int i = 0; i < size(); ++i) {

		std::cout << DataSet.at(i);
	}
	*/
}
