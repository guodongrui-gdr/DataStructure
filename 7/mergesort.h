#ifndef MERGESORT_H
#define MERGESORT_H

#include<deque>
#include<iostream>
#include <time.h>
#include <cstdlib>
using namespace std;
template<typename T>
void merge(deque<T>& a, deque<T>& tmpArray, int leftPos, int rightPos, int rightEnd)
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
void mergesort(deque<T>& a, deque<T>& tmpArray, int left, int right)
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
void mergesort(deque<T>& a)
{
	deque<T> tmpArray(a.size());
	mergeSort(a, tmpArray, 0, a.size() - 1);
}
#endif // !MERGESORT_H