#ifndef BQUEUE_H
#define BQUEUE_H
#include<iostream>
#include<vector>
using namespace std;
template<typename T>
class bqueue
{
public:
	bqueue() :theTrees(DEFAULT_TREES),currentSize(0){}
	bqueue(const T& item) :theTrees(DEFAULT_TREES), currentSize(1)
	{
		theTrees[0] = new Node{ item,nullptr,nullptr };
	}
	bqueue(const bqueue& rhs) :theTrees(rhs.theTrees.size()), currentSize(rhs.currentSize)
	{
		for (int i = 0; i < rhs.theTrees.size(); ++i)
		{
			theTrees[i] = clone(rhs.theTrees[i]);
		}
	}
	bqueue(bqueue&& rhs) :theTrees(std::move(rhs.theTrees)),currentSize(rhs.currentSize){}
	~bqueue()
	{
		makeEmpty();
	}
	bqueue& operator=(const bqueue& rhs)
	{
		bqueue copy = rhs;
		std::swap(*this, copy);
		return *this;
	}
	bqueue& operator=(const bqueue&& rhs)
	{
		std::swap(theTrees, rhs.theTrees);
		std::swap(currentSize, rhs.currentSize);
		return *this;
	}
	bool empty()const
	{
		return currentSize == 0;
	}
	const T& findMin()const
	{
		return theTrees[findMinIndex()]->data;
	}
	void insert(const T& x)
	{
		bqueue oneItem(x);
		merge(oneItem);
	}
	void insert(T&& x)
	{
		bqueue oneItem(std::move(x));
		merge(oneItem);
	}
	void deleteMin()
	{
		T x;
		deleteMin(x);
	}
	void deleteMin(T& minItem)
	{
		int minIndex = findMinIndex();
		minIndex = theTrees[minIndex]->data;
		Node* oldroot = theTrees[minIndex];
		Node* deletedTree = oldroot->lch;
		delete oldroot;
		bqueue deletedqueue;
		deletedqueue.theTrees.resize(minIndex + 1);
		deletedqueue.currentSize = (1 << minIndex) - 1;
		for (int j = minIndex - 1; j >= 0; --j)
		{
			deletedqueue.theTrees[j] = deletedTree;
			deletedTree = deletedTree->nextSibling;
			deletedqueue.theTrees[j]->nextSibling = nullptr;
		}
		theTrees[minIndex] = nullptr;
		currentSize -= deletedqueue.currentSize + 1;

		merge(deletedqueue);
	}
	void makeEmpty()
	{
		currentSize = 0;
		for (auto& root : theTrees)
			makeEmpty(root);
	}
	int size()
	{
		return currentSize;
	}
	void merge(bqueue& rhs)
	{
		if (this == &rhs)return;
		currentSize += rhs.currentSize;
		if (currentSize > capacity())
		{
			int oldNumTrees = theTrees.size();
			int newNumTrees = max(theTrees.size(), rhs.theTrees.size()) + 1;
			theTrees.resize(newNumTrees);
			for (int i = oldNumTrees; i < newNumTrees; ++i)
			{
				theTrees[i] = nullptr;
			}
			Node* carry = nullptr;
			for (int i = 0, j = 1; j < currentSize; ++i, j *= 2)
			{
				Node* t1 = theTrees[i];
				Node* t2 = i < rhs.theTrees.size() ? rhs.theTrees[i] : nullptr;
				int whichcase = t1 == nullptr ? 0 : 1;
				whichcase += t2 == nullptr ? 0 : 2;
				whichcase += carry == nullptr ? 0 : 4;
				switch (whichcase)
				{
				case 0:
				case 1:
					break;
				case 2:
					theTrees[i] = t2;
					rhs.theTrees[i] = nullptr;
					break;
				case 4:
					theTrees[i] = carry;
					carry = nullptr;
					break;
				case 3:
					carry = conbineTrees(t1, t2);
					theTrees[i] = rhs.theTrees[i] = nullptr;
					break;
				case 5:
					carry = conbineTrees(t1, carry);
					theTrees[i] = nullptr;
					break;
				case 6:
					carry = conbineTrees(t2, carry);
					theTrees[i] = nullptr;
					break;
				case 7:
					theTrees[i] = carry;
					carry = conbineTrees(t1, t2);
					rhs.theTrees[i] = nullptr;
					break;
				}
			}
			for (auto& root : rhs.theTrees)
				root = nullptr;
			rhs.currentSize = 0;
		}
	}
private:
	struct Node
	{
		Node* lch;
		Node* nextSibling;
		T data;

		Node() :data(T()), lch(nullptr), nextSibling(nullptr) {}
		Node(const T& d, Node* l = nullptr, Node* n = nullptr) :data(d), lch(l), nextSibling(n) {}
		Node(T&& d, Node* l, Node* n) :data(std::move(d)), lch(l), nextSibling(n) {}
	};
	const static int DEFAULT_TREES = 1;
	vector<Node*>theTrees;
	int currentSize;

	int findMinIndex()const
	{
		int i;
		int minIndex;
		for (i = 0; theTrees[i] == nullptr; ++i);
		for (minIndex = i; i < theTrees.size(); ++i)
			if (theTrees[i] != nullptr && theTrees[i]->data < theTrees[minIndex]->data)
				minIndex = i;
		return minIndex;
	}
	int capacity()
	{
		return (1 << theTrees.size()) - 1;
	}
	Node* conbineTrees(Node* t1, Node* t2)
	{
		if (t2->data < t1->data) return conbineTrees(t2, t1);
		t2->nextSibling = t1->lch;
		t1->lch = t2;
		return t1;
	}
	void makeEmpty(Node*& t)
	{
		if (t != nullptr) 
		{
			makeEmpty(t->lch);
			makeEmpty(t->nextSibling);
			delete t;
			t = nullptr;
		}
	}
	Node* clone(Node* t)const
	{
		if (t == nullptr)
			return nullptr;
		else
			return new Node{ t->element, clone(t->leftchild), clone(t->nextSibling) };
	}
};
#endif // !BQUEUE_H

