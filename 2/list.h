#ifndef LIST_H
#define LIST_H
#include"Node.h"



template <typename Object>
class List
{
private:
	int theSize;
	Node* head;
	Node* rear;
	void init()
	{
		theSize = 0;
		head = new Node;
		rear = new Node;
		head->next = rear;
		head->prev = head;
	};
public:
	List()
	{
		init();
	}
	List(const List& rhs)
	{
		init();
		for (auto& x : rhs)
			push_back(x);
	}
	List& operator=(const List& rhs)
	{
		List copy = rhs;
		std::swap(*this, copy);
		return *this;
	}
	List(List&& rhs) :theSize(rhs.theSize), head(rhs.head), rear(rhs.rear)
	{
		rhs.theSize = 0;
		rhs.head = nullptr;
		rhs.rear = nullptr;
	}
	List& operator=(List&& rhs)
	{
		std::swap(theSize, rhs.theSize);
		std::swap(head, rhs.head);
		std::swap(rear, rhs.rear);
		return *this;
	}
	int size()const
	{
		return theSize;
	}
	bool empty()const
	{
		return size() == 0;
	}
	void clear()
	{
		while (!empty())
			pop_front();
	}
	Object& front()
	{
		return *begin();
	}
	const Object& front()const
	{
		return *begin();
	}
	Object& back()
	{
		return --end();
	}
	const Object& back()const
	{
		return --end();
	}
	void push_front(const Object& x)
	{

	}
	void push_front(Object&& x);
	void push_back(const Object& x);
	void push_back(Object&& x);
	void pop_front();
	void pop_back();
	~List()
	{
		clear();
		delete head;
		delete rear;
	}
};

#endif // LIST_H
