#include <iostream>

struct Array {
	int* arr;
	int size;
	int maxInd;
	int minInd;
	int avg;

	Array(int* arr, int size) {
		this->arr = arr;
		this->size = size;
		maxInd = -1;
		minInd = -1;
		avg = 0;
	}

	void Print(std::ostream& os) {

	}
};