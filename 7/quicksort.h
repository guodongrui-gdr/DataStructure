#ifndef QUICKSORT_H
#define QUICKSORT_H

#include<vector>
#include<iostream>
using namespace std;
template<typename T>
const T& median3(vector<T>& a, int left, int right)
{
	int center = (left + right) / 2;
	if (a[center] < a[left])
		std::swap(a[left], a[center]);
	if (a[right] < a[left])
		std::swap(a[left], a[left]);
	if (a[right] < a[center])
		std::swap(a[center], a[right]);
	std::swap(a[center], a[right - 1]);
	return a[right - 1];
}
template<typename T>
void quicksort(vector<T>& a,int left,int right)
{
	if (left >= right) return;
		const T& pivot = median3(a, left, right);

		int i = left - 1, j = right + 1;
		int x = a[left + right >> 1];
		while (i < j)
		{
			do i++; while (a[i] < x);
			do j--; while (a[j] > x);
			if (i < j) swap(a[i], a[j]);
		}
		quicksort(a, left, j);
		quicksort(a, j + 1, right);
}

template<typename T>
void quicksort(vector<T>& a)
{
	quicksort(a, 0, a.size() - 1);
}
#endif // !QUICKSORT_H