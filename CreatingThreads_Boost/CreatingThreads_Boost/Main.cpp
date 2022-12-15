#include <iostream>
#include <conio.h>
#include <boost/thread.hpp>
#include <boost/random.hpp>
#include <boost/chrono.hpp>
#include "Array.h";

void min_max(Array* args) {
	int n = args->size;
	int* arr = args->arr;
	int maxInd, minInd;
	maxInd = minInd = 0;
	for (int i = 1; i < n; i++) {
		if (arr[maxInd] < arr[i]) {
			maxInd = i;
		}
		if (arr[minInd] > arr[i]) {
			minInd = i;
		}
		boost::this_thread::sleep_for(boost::chrono::milliseconds(7));
	}
	args->maxInd = maxInd;
	args->minInd = minInd;
	std::cout << "Max element: " << arr[maxInd] << std::endl;
	std::cout << "Min element: " << arr[minInd] << std::endl;
}

void average(Array* args) {
	int n = args->size;
	int* arr = args->arr;
	int sum = 0;
	for (int i = 0; i < n; i++) {
		sum += arr[i];
		boost::this_thread::sleep_for(boost::chrono::milliseconds(12));
	}
	args->avg = sum / n;
	printf("Average value: %d \n", args->avg);
}

void printArr(int* arr, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
}

int main() 
{
	const int MIN_DISTRIB_1 = 5;
	const int MAX_DISTRIB_1 = 15;
	const int MIN_DISTRIB_2 = 0;
	const int MAX_DISTRIB_2 = 35000;

	typedef boost::mt19937 RNGType;
	RNGType rng(time(0));
	boost::uniform_int<> arraySize(MIN_DISTRIB_1, MAX_DISTRIB_1);
	boost::variate_generator<RNGType, boost::uniform_int<>> dice(rng, arraySize);
	int n = dice();

	boost::uniform_int<> arrayElem(MIN_DISTRIB_2, MAX_DISTRIB_2);
	dice.distribution() = arrayElem;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		arr[i] = dice();
	}
	printf("Generated array of %d elements: \n", n);
	printArr(arr, n);
	printf("\n\n");

	Array* args = new Array(arr, n);

	boost::thread min_maxThread(min_max, args);
	boost::thread averageThread(average, args);
	min_maxThread.join();
	averageThread.join();

	arr[args->minInd] = arr[args->maxInd] = args->avg;
	std::cout << "\nChanged array: " << std::endl;

	args->Print(std::cout);
	_getch();
	return 0;
}