#include "gauss.h"

gaussDataSet::gaussDataSet() {}
gaussDataSet::gaussDataSet(int size, float mean = 0.0f, float sdev = 2.0f, float disp = 1.0f) : size(size), mean(mean), sdev(sdev), disp(disp) {

	init();
}

void gaussDataSet::init() {

	std::default_random_engine generator;
	std::normal_distribution<double> distribution(mean, sdev);

	for (int i = 0; i < size; ++i) {

		DataSet.push_back(distribution(generator));
	}
	
}

void gaussDataSet::regen(double newSize) {
	
	size = newSize;	
	DataSet.clear();

	std::default_random_engine generator;
	std::normal_distribution<double> distribution(mean, sdev);
	
	for (int i = 0; i < size; ++i) {

		DataSet.push_back(distribution(generator));
	}
}

void gaussDataSet::print() {
	
	int pCount = 0;
	int nCount = 0;

	double meanD = 0.0;
	
	for (int i = 0; i < size; ++i) {
		
		meanD += DataSet.at(i);

		std::cout << std::setw(2) << i;
	       	if(DataSet.at(i) >= 0)	{
			pCount++;
			std::cout << "  " << std::fixed << std::showpoint << std::setprecision(4) << DataSet.at(i) << " +" << pCount << " -" << nCount;
			
		}
		else {
			nCount++;
			std::cout << ' '  << std::fixed << std::showpoint << std::setprecision(4) << DataSet.at(i) << " +" << pCount << " -" << nCount;

		}

		if(meanD >= 0) {
			std::cout << "  " << std::fixed << std::showpoint << std::setprecision(4) << meanD << std::endl;
		}
		else {
			std::cout << ' ' << std::fixed << std::showpoint << std::setprecision(4) << meanD << std::endl;
		}
	}

}
