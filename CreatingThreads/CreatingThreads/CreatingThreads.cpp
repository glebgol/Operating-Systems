#include <iostream>
#include <Windows.h>

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

DWORD WINAPI MinMax(LPVOID lpParameters)
{
	std::cout << "MinMax thread is started.\n";
	Array* arr = (Array*)lpParameters;

	int max = arr->p[0];
	int min = arr->p[0];

	for (int i = 0; i < arr->size; i++) {
		if (arr->p[i] > max) {
			max = arr->p[i];
			arr->indexOfMax = i;
			Sleep(7);
		}
		else if (arr->p[i] < max) {
			min = arr->p[i];
			arr->indexOfMin = i;
			Sleep(7);
		}
	}
	std::cout << "Max number in array: " << max << std::endl;
	std::cout << "Min number in array: " << min << std::endl;

	return 0;
}

DWORD WINAPI Average(LPVOID lpParameters)
{
	std::cout << "Average thread is started.\n";
	Array* arr = (Array*)lpParameters;

	int average = 0;
	for (int i = 0; i < arr->size; i++) {
		average += arr->p[i];
		Sleep(12);
	}
	arr->average = average / arr->size;

	std::cout << "Average number in array: " << arr->average << std::endl;
	return 0;
}

int main()
{
}
