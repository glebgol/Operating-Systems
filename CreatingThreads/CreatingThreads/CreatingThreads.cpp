#include <iostream>

struct Array {
	int size;
	int* p;

	int indexOfMin;
	int indexOfMax;
	int average;
	Array(int _size) {
		p = new int[_size];
		size = _size;
		indexOfMin = 0;
		indexOfMax = 0;
		average = 0;
	}
	~Array() {
		delete[] p;
	}
};

int main()
{
}
