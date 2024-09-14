#ifndef GAUSS_H
#define GAUSS_H

#include <iostream>
#include <vector>
#include <iomanip>

#include <random>

class gaussDataSet {

public:

	int size;

	float mean;
	float sdev;
	float disp;

	std::vector<double> DataSet;

	gaussDataSet();
	gaussDataSet(int size, float mean,  float sdev,  float disp);

	void init();
	void regen(double newSize);
			
	void print();
};

#endif
