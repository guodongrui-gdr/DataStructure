#ifndef LHASH_H
#define LHASH_H
#include<iostream>
#include<vector>
using namespace std;

template<typename T>
class Hash
{
public:
	explicit Hash(int size = 101):arr(nextPrime(size))
	{
		makeEmpty();
	}
	void makeEmpty()
	{
		currentSize = 0;
		for (auto& entry : arr)
			entry.info = EMPTY;
	}
	int hash(T key)
	{
		return key % arr.size();
	}
	bool contains(const T& x)const
	{
		return isActive(findPos(x));
	}
	bool insert(T key)
	{
		int currentPos = findPos(key);
		if (isActive(currentPos))
			return false;
		arr[currentPos].data = key;
		arr[currentPos].info = ACTIVE;
		if (++currentSize > arr.size() / 2)
			rehash();
	}
	bool remove(const T& x)
	{
		int currentPos = findPos(x);
		if (!isActive(x))
			return false;
		arr[currentPos].info = DELETED;
		return true;
	}
	Hash& operator=(const Hash& rhs)
	{
		Hash copy=rhs;
		std::swap(*this, copy);
		return *this;
	}

	int size()const
	{
		return currentSize;
	}
	bool empty()const
	{
		return currentSize == 0;
	}

	enum EntryType { ACTIVE, EMPTY, DELETED };
private:
	struct HashEntry
	{
		T data;
		EntryType info;
		HashEntry(const T& e = T(), EntryType i = EMPTY) :data(e), info(i) {}
		HashEntry(T&& e , EntryType i = EMPTY) :data(std::move(e)), info(i) {}
	};
	vector<HashEntry> arr;
	int currentSize;
		
	bool isActive(int currentPos)
	{
		return arr[currentPos].info == ACTIVE;
	}
	int findPos(const T& x)
	{
		int offset = 1;
		int currentPos = hash(x);
		while (arr[currentPos].info!=EMPTY && arr[currentPos].data!=x)
		{
			currentPos += offset;
			offset += 2;
			if (currentPos >= arr.size())
				currentPos -= arr.size();
		}
		return currentPos;
	}
	void rehash()
	{
		vector<HashEntry> oldArray = arr;
		arr.resize(nextPrime(2 * oldArray.size()));
		for (auto& entry : arr)
			entry.info = EMPTY;
		currentSize = 0;
		for (auto& entry : oldArray)
			if (entry.info == ACTIVE)
				insert(std::move(entry.data));
	}
	static bool isPrime(int x)
	{
		int count = 0;
		for (int i = 2; i < sqrt(x); i++)
		{
			if (x % i == 0)
				count++;
		}
		return count == 0;
		}
	static int nextPrime(int x)
	{
		while (!isPrime(x))
			x++;
		return x;
	}
};
#endif // !LHASH_H
