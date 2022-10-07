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

DWORD WINAPI Main(LPVOID lpParameters)
{
	std::cout << "Main thread is started." << std::endl;
	std::cout << "Enter the size of array: ";
	int size = 0;
	std::cin >> size;
	Array* array = new Array(size);
	std::cout << "Enter " << size << " elements: ";
	for (int i = 0; i < size; i++) {
		std::cin >> array->p[i];
	}
	HANDLE hThread1;
	DWORD IDThread1;
	hThread1 = CreateThread(NULL, 0, MinMax, array, 0, &IDThread1);
	if (hThread1 == NULL) {
		return GetLastError();
	}

	HANDLE hThread2;
	DWORD IDThread2;
	hThread2 = CreateThread(NULL, 0, Average, array, 0, &IDThread2);
	if (hThread2 == NULL) {
		return GetLastError();
	}

	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE);
	CloseHandle(hThread1);
	CloseHandle(hThread2);

	int indexOfMin = array->indexOfMin;
	int indexOfMax = array->indexOfMax;
	int average = array->average;

	array->p[indexOfMin] = average;
	array->p[indexOfMax] = average;

	for (int i = 0; i < size; i++) {
		std::cout << array->p[i] << ' ';
	}
	return 0;
}

int main()
{
	HANDLE hThread;
	DWORD IDThread;
	hThread = CreateThread(NULL, 0, Main, NULL, 0, &IDThread);

	if (hThread == NULL) {
		return GetLastError();
	}

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);

	return 0;
}
