#ifndef GAUSS_H
#define GAUSS_H

#include <iostream>
#include <vector>

#include <random>

class gaussDataSet {

public:

	int size;

	int mean;
	int sdev;
	int disp;

	std::vector<double> DataSet(size);

	gaussDataSet();

	void init();

	void print();
}

#endif
