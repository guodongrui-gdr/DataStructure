#include"vector.h"
#include<assert.h>
#include<iostream>
using namespace std;
typedef unsigned long size_type;
template<typename T>
Vector<T>::Vector()
{
	theSize = 10;
	theCapacity = 20;
	a = new T[theCapacity];
}
template<typename T>
Vector<T>::Vector(size_type siz)
{
	this->theSize = siz;
	this->theCapacity = siz + 20;
	this->a = new T[theCapacity];
}
template<typename T>
Vector<T>::Vector(size_type siz, T& rhs)
{
	this->theSize = siz;
	this->theCapacity = siz + 20;
	this->a = new T[theCapacity];
	for (int i = 0; i < this->theSize; i++)
	{
		this->a[i] = rhs;
	}
}
template<typename T>
Vector<T>::Vector(const Vector<T>& rhs)
{
	theSize = rhs.theSize;
	theCapacity = rhs.theCapacity;
	a = new T[theCapacity];
	for (int k = 0; k < theSize; ++k)
		a[k] = rhs.a[k];
}
template<typename T>
Vector<T>::Vector(Vector<T>& rhs) {
	theSize = rhs.theSize;
	theCapacity = rhs.theCapacity;
	a = new T[theCapacity];
	rhs.theSize = rhs.theCapacity = 0;
	rhs.a = nullptr;
}
template<typename T>
Vector<T>::~Vector()
{	
	theSize = theCapacity = 0;
	a = nullptr;
}
template<typename T>
T& Vector<T>::operator=(Vector<T>& rhs)
{
	theSize = rhs.theSize;
	theCapacity = rhs.theCapacity;
	for (int i = 0; i < theSize; i++)
		a[i] = rhs.a[i];
	return *this;
}
template<typename T>
const T& Vector<T>::operator[](int idx)const
{
	return a[idx];
}
template<typename T>
T & Vector<T>::operator[](int idx)
{
	return a[idx];
}
template<typename T>
const T& Vector<T>::at(int idx)const
{
	assert(idx >= 0 && idx < theSize);
	return a[idx];
}
template<typename T>
bool Vector<T>::empty()const
{
	return size() == 0;
}
template<typename T>
size_type Vector<T>::size()const
{
	return theSize;
}
template<typename T>
size_type Vector<T>::capacity()const
{
	return theCapacity;
}
template<typename T>
void Vector<T>::reserve(size_type newCapacity)
{
	T* tmp = new T[newCapacity];
	if (newCapacity <= theSize) {
		for (int i = 0; i < newCapacity; ++i) {
			tmp[i] = a[i];
		}
	}
	else {
		for (int i = 0; i < theSize; ++i) {
			tmp[i] = a[i];
		}
	}
	delete[] a;
	a = tmp;
}
template<typename T>
T& Vector<T>::back()const
{
	return a[theSize - 1];
}
template<typename T>
T& Vector<T>::front()const
{
	return a[0];
}
template<typename T>
void Vector<T>::push_back(const T& x)
{
	if (theSize == theCapacity)
	{
		reserve(2 * theCapacity + 1);
	}
	a[theSize++] = x;
}
template<typename T>
void Vector<T>::pop_back()
{
	--theSize;
}
template<typename T>
void Vector<T>::push_front(const T& x)
{
	if (theSize == theCapacity)
	{
		reserve(2 * theCapacity + 1);
	}
	theSize++;
	for (int i = theSize - 1; i > 0; i--) {
		a[i] = a[i - 1];
	}
	a[0] = x;
}
template<typename T>
void Vector<T>::pop_front()
{
	for (int i = 0; i < theSize - 1; i++) {
		a[i] = a[i + 1];
	}
	--theSize;
}
template<typename T>
void Vector<T>::clear()
{
	theCapacity = theSize = 0;
	delete[] a;
	a = nullptr;
}
template<typename T>
void Vector<T>::insert(pos_type pos, const T& x)
{
	if (theSize == theCapacity) {
		T* t = new T[2 * theCapacity + 1];
		for (int i = 0; i < theSize; ++i) {
			t[i] = move(a[i]);
		}
		delete[] a;
		a = t;
	}
	if (pos >= 0 && pos <= theSize) {
		for (int i = theSize; i > pos; --i) {
			a[i] = a[i - 1];
		}
		a[pos] = x;
		++theSize;
	}
}
template<typename T>
void Vector<T>::erase(pos_type pos)
{
	if (pos < theSize) {
		--theSize;
		for (int i = pos; i < theSize; ++i) {
			a[i] = a[i + 1];
		}
	}
}
template<typename T>
void Vector<T>::swap(Vector<T>& rhs)
{
	Vector<T> copy = rhs;
	rhs.theSize = theSize;
	theSize = copy.theSize;
	rhs.theCapacity = theCapacity;
	theCapacity = copy.theCapacity;
	rhs.a = a;
	a = copy.a;
	copy.~Vector();
}
template<typename T>
void Vector<T>::resize(size_type newSize)
{
	if (newSize > theCapacity)
		reserve(newSize * 2);
	theSize = newSize;
}
template<typename T>
void Vector<T>::display()
{
	for (unsigned long i = 0; i < size(); i++) {
		cout << at(i) << " ";
	}
	cout << endl;
}


template<typename T>
bool Vector<T>::iterator::operator!=(iterator& itr)
{
	return !(*this==itr);
}
template<typename T>
bool Vector<T>::iterator::operator==(iterator& itr)
{
	return current == itr.current;
}
template<typename T>
void Vector<T>::iterator::operator++()
{
	++current;
}
template<typename T>
T& Vector<T>::iterator::operator*()
{
	return *current;
}
template<typename T>
bool Vector<T>::const_iterator::operator!=(const_iterator const& itr)const
{
	return !(*this == itr);
}
template<typename T>
bool Vector<T>::const_iterator::operator==(const_iterator const& itr)const
{
	return current == itr.current;
}
template<typename T>
const T& Vector<T>::const_iterator::operator*()const 
{
	return *current;
}
template<typename T>
void Vector<T>::const_iterator::operator++()
{
	++current;
}
template<typename T>
bool Vector<T>::reverse_iterator::operator!=(reverse_iterator& itr)
{
	return !(*this == itr);
}
template<typename T>
bool Vector<T>::reverse_iterator::operator==(reverse_iterator& itr)
{
	return current == itr.current;
}
template<typename T>
T& Vector<T>::reverse_iterator::operator*()
{
	return *current;
}
template<typename T>
void Vector<T>::reverse_iterator::operator++()
{
	++current;
}
template<typename T>
bool Vector<T>::const_reverse_iterator::operator!=(const_reverse_iterator const& itr)const
{
	return !(*this == itr);
}
template<typename T>
bool Vector<T>::const_reverse_iterator::operator==(const_reverse_iterator const& itr)const
{
	return current == itr.current;
}
template<typename T>
T& Vector<T>::const_reverse_iterator::operator*()const
{
	return *current;
}
template<typename T>
void Vector<T>::const_reverse_iterator::operator++()
{
	++current;
}
template<typename T>
typename Vector<T>::iterator Vector<T>::begin()
{
	return iterator(a);
}
template<typename T>
typename Vector<T>::const_iterator Vector<T>::begin()const
{
	return const_iterator(a);
}
template<typename T>
typename Vector<T>::iterator Vector<T>::end()
{	

	return iterator(&back());
}
template<typename T>
typename Vector<T>::const_iterator Vector<T>::end()const
{
	return const_iterator(&back());
}
template<typename T>
typename Vector<T>::reverse_iterator Vector<T>::rbegin()
{
	return reverse_iterator(&back());
}
template<typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::rbegin()const
{
	return const_reverse_iterator(&back());
}
template<typename T>
typename Vector<T>::reverse_iterator Vector<T>::rend()
{
	return reverse_iterator(a);
}
template<typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::rend()const
{
	return const_reverse_iterator(a);
}