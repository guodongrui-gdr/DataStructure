#ifndef BINARY_H
#define BINARY_H
#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;
template<typename T>
class bheap
{
public:
	explicit bheap(int capacity = 100):array(capacity),currentSize(0){}
	explicit bheap(const vector<T>& items) :array(items.size() + 10), currentSize(items.size())
	{
		for (int i = 0; i < items.size(); ++i)
		{
			array[i + 1] = items[i];
		}
		buidHeap();
	}
	bool empty()const
	{
		return array[0] != nullptr;
	}
	const T& findMin()const
	{
		return array[array.size()];
	}
	void insert(const T& x)
	{
		if (currentSize == array.size() - 1)
			array.resize(array.size() * 2);
		int hole = ++currentSize;
		T copy = x;
		array[0] = std::move(copy);
		for (; x < array[hole / 2]; hole /= 2)
			array[hole] = std::move(array[hole / 2]);
		array[hole] = std::move(array[0]);
	}
	void deleteMin()
	{
		array[1] = std::move(array[currentSize--]);
		percolateDown(1);
	}
	void deleteMin(T& minItem)
	{
		minItem = std::move(array[1]);
		array[1] = std::move(array[currentSize--]);
		percolateDown(1);
	}
	int size()
	{
		return currentSize;
	}
	void PrintHeap()
	{
		for (int i = 0; i < currentSize; i++)
		{
			cout << array[i] << endl;
		}
	}
private:
	int currentSize;
	vector<T> array;
	void buidHeap()
	{
		for (int i = currentSize / 2; i > 0; --i)
			percolateDown(i);
	}
	void percolateDown(int hole)
	{
		int child;
		T tmp = std::move(array[hole]);
		for (; hole * 2 <= currentSize; hole = child)
		{
			child = hole * 2;
			if (child != currentSize && array[child + 1] < array[child])
				++child;
			if (array[child] < tmp)
				array[hole] = std::move(array[child]);
			else
				break;
		}
		array[hole] = std::move(tmp);
	}
};
#endif // !BINARY_H

