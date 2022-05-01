#ifndef MERGESORT_H
#define MERGESORT_H

#include<vector>
#include<iostream>
#include <time.h>
#include <cstdlib>
using namespace std;
template<typename T>
void merge(vector<T>& a, vector<T>& tmpArray, int leftPos, int rightPos, int rightEnd)
{
	int leftEnd = rightPos - 1;
	int tmpPos = leftPos;
	int num = rightEnd - leftPos + 1;
	while (leftPos <= leftEnd && rightPos <= rightEnd)
	{
		if (a[leftPos] <= a[rightPos])
			tmpArray[tmpPos++] = std::move(a[leftPos++]);
		else
			tmpArray[tmpPos++] = std::move(a[rightPos++]);
	}
	while (leftPos <= leftEnd)
	{
		tmpArray[tmpPos++] = std::move(a[leftPos++]);
	}
	while (rightPos <= rightEnd)
	{
		tmpArray[tmpPos++] = std::move(a[rightPos++]);
	}
	for (int i = 0; i < num; ++i, --rightEnd)
		a[rightEnd] = std::move(tmpArray[rightEnd]);
}

template<typename T>
void mergeSort(vector<T>& a, vector<T>& tmpArray, int left, int right)
{
	if (left < right)
	{
		int center = (left + right) / 2;
		mergeSort(a, tmpArray, left, center);
		mergeSort(a, tmpArray, center + 1, right);
		merge(a, tmpArray, left, center + 1, right);
	}
}
template<typename T>
void mergesort(vector<T>& a)
{
	vector<T> tmpArray(a.size());
	mergeSort(a, tmpArray, 0, a.size() - 1);
}

int main()
{
	unsigned seed = 0;
	srand(seed);

	vector<int> a(1000000);
	for (int i = 0; i < 1000000; ++i)
	{
		int r = rand();
		a[i] = r;
	}

	clock_t start, end;
	start = clock();
	mergesort(a);
	end = clock();
	cout << double(end - start) / CLOCKS_PER_SEC << endl;
}

#endif // !MERGESORT_H