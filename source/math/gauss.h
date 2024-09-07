#ifndef GAUSS_H
#define GAUSS_H

#include <iostream>
#include <vector>

#include <random>

class gaussDataSet {

public:

	int size;

	float mean;
	float sdev;
	float disp;

	std::vector<double> DataSet(size);

	gaussDataSet();

	void init();

	void print();
}

#endif
