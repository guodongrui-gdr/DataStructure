#ifndef LIST_H
#define LIST_H
#include<algorithm>
template <typename Object>
class List
{
private:
	struct Node
	{
		Node *next;
		Node *prev;
		Object data;

		Node(const Object& d = Object(), Node* n = nullptr, Node* p = nullptr) :data(d), next(n), prev(p) {}
	};
public:
	class const_iterator
	{
	public:
		const_iterator():current(nullptr){}
		const Object& operator*()const { return retrieve(); }
		const_iterator& operator++()
		{
			current = current->next;
			return *this;
		}
		const_iterator operator++(int)
		{
			const_iterator old = *this;
			++(*this);
			return	old;
		}
		bool operator==(const const_iterator & rhs)const
		{
			return current == rhs.current;
		}
		bool operator!=(const const_iterator& rhs)const
		{
			return !(*this==rhs);
		}

	protected:
		Node* current;
		Object& retrieve()const { return current->data; }
		const_iterator(Node *p):current(p){}
		friend class List<Object>;
	};
	class iterator : public const_iterator
	{
	public:
		iterator(){}
		Object & operator*()
		{
			return const_iterator::retrieve();
		}
		const Object & operator*()const
		{
			return const_iterator::operator*();
		}
		iterator& operator++()
		{
			this->current = this->current->next;
			return *this;
		}
		iterator operator++(int)
		{
			iterator old = *this;
			++(*this);
			return old;
		}
	protected:
		iterator(Node *p):const_iterator(p){}
		friend class List<Object>;
	};
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
	
	iterator begin()
	{
		return (head->next);
	}
	const_iterator begin()const
	{
		return (head->next);
	}
	iterator end()
	{
		return rear;
	}
	const_iterator end()const
	{
		return rear;
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

	iterator insert(iterator itr, const Object& x)
	{
		Node* p = itr.current;
		theSize++;
		return (p->prev = p->next = new Node(x, p->prev, p));
	}
	iterator erase(iterator itr)
	{
		Node *p = itr.current;
		iterator retVal(p->next);
		while (p)
		{
			p->prev->next = p->next;
			p->next->prev = p->prev;
		}
		delete p;
		theSize--;
		return retVal;
	}
	void push_front(const Object& x)
	{
		insert(begin(), x);
	}
	void push_back(const Object& x)
	{
		insert(end(), x);
	}
	void pop_front()
	{
		erase(begin());
	}
	void pop_back()
	{
		erase(--end());
	}
	~List()
	{
		clear();
		delete head;
		delete rear;
	}
};

#endif // LIST_H