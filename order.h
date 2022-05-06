#ifndef ORDER_H
#define ORDER_H

#include"Customer.h"
#include"Event.h"
#include<deque>

using namespace std;
void merge(deque<Customer>& a, deque<Customer>& tmpArray, int leftPos, int rightPos, int rightEnd)
{
	int leftEnd = rightPos - 1;
	int tmpPos = leftPos;
	int num = rightEnd - leftPos + 1;
	while (leftPos <= leftEnd && rightPos <= rightEnd)
	{
		if (a[leftPos].vip >= a[rightPos].vip)
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

void merge(deque<Event>& a, deque<Event>& tmpArray, int leftPos, int rightPos, int rightEnd)
{
	int leftEnd = rightPos - 1;
	int tmpPos = leftPos;
	int num = rightEnd - leftPos + 1;
	while (leftPos <= leftEnd && rightPos <= rightEnd)
	{
		if (a[leftPos].occur_time <= a[rightPos].occur_time)
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
void mergesort(deque<Customer>& a, deque<Customer>& tmpArray, int left, int right)
{
	if (left < right)
	{
		int center = (left + right) / 2;
		mergesort(a, tmpArray, left, center);
		mergesort(a, tmpArray, center + 1, right);
		merge(a, tmpArray, left, center + 1, right);
	}
}
void mergesort(deque<Event>& a, deque<Event>& tmpArray, int left, int right)
{
	if (left < right)
	{
		int center = (left + right) / 2;
		mergesort(a, tmpArray, left, center);
		mergesort(a, tmpArray, center + 1, right);
		merge(a, tmpArray, left, center + 1, right);
	}
}
template<typename T>
void mergesort(deque<T>& a)
{
	deque<T> tmpArray(a.size());
	mergesort(a, tmpArray, 0, a.size() - 1);
}
#endif // !ORDER_H