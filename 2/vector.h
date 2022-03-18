#ifndef VECTOR_H
#define VECTOR_H
#define FILE_BUFFER_LENGTH 30000
#include<algorithm>
#include<assert.h>

template<typename T>
class Vector
{
public:
	typedef int pos_type;
	typedef unsigned long size_type;

	Vector();
	Vector(size_type siz);
	Vector(size_type siz, T& rhs);
	Vector(const Vector& rhs);
	Vector(Vector<T>& rhs);
	~Vector();

	T& operator=(Vector& rhs);
	const T& operator[](int idx)const;
	T& operator[](int idx);
	const T& at(int idx)const;

	bool empty()const;
	size_type size()const;
	size_type capacity()const;
	void reserve(size_type newCapacity);

	T& back()const;
	T& front()const;

	void push_back(const T& x);
	void pop_back();
	void push_front(const T& x);
	void pop_front();
	void clear();
	void insert(pos_type pos, const T& x);
	void erase(pos_type pos);
	void swap(Vector& a);
	void resize(size_type newSize);
	void display();

public:
	class iterator
	{
		friend class Vector<T>;
	public:
		iterator(T* p=nullptr) :current(p) {}
		bool operator!=(iterator& itr);
		bool operator==(iterator& itr);
		void operator++();
		T& operator*();
	protected:
		T* current;
	};
	class const_iterator
	{
		friend class Vector<T>;
	public:
		const_iterator(T* p) :current(p) {}
		bool operator!=(const_iterator const& itr) const;
		bool operator==(const_iterator const& itr) const;
		void operator++();
		const T& operator*()const;
	protected:
		T* current;	
	};
	class reverse_iterator
	{
		friend class Vector<T>;
	public:
		reverse_iterator(T* p = nullptr) :current(p) {}
		bool operator!=(reverse_iterator& itr);
		bool operator==(reverse_iterator& itr);
		void operator++();
		T& operator*();
	protected:
		T* current;
	};
	class const_reverse_iterator
	{
		friend class Vector<T>;
	public:
		const_reverse_iterator(T* p = nullptr) :current(p) {}
		bool operator!=(const_reverse_iterator const& itr)const;
		bool operator==(const_reverse_iterator const& itr)const;
		void operator++();
		T& operator*()const;
	protected:
		T* current;
	};
	iterator begin();
	iterator end();
	const_iterator begin()const;
	const_iterator end()const; ;
	reverse_iterator rbegin();
	reverse_iterator rend();
	const_reverse_iterator rbegin()const;
	const_reverse_iterator rend()const;


public:
	size_type theSize;
	size_type theCapacity;
	T* a;
};
#endif // !VECTOR_H


