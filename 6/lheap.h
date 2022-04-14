#ifndef LHEAP_H
#define LHEAP_H
#include<queue>
#include<string>
#include<iostream>
using namespace std;
int xx;
template<typename T>
class lheap
{
public:
	lheap() :root(nullptr) {};
	lheap(const lheap& rhs) :root(root) { clone(rhs.root); }
	lheap(lheap&& rhs) :root(rhs.root)
	{
		rhs.root = nullptr;
	}
	~lheap()
	{
		makeEmpty();
	}
	lheap& operator=(const lheap& rhs)
	{
		lheap copy = rhs;
		std::swap(*this, copy);
		return *this;
	}
	lheap& operator=(lheap&& rhs)
	{
		std::swap(root, rhs.root);
		return *this;
	}
	bool empty()const
	{
		return root == nullptr;
	}
	const T& findMin()const
	{
		if (empty()) return;
		return root->data;
	}
	void insert(const T& x)
	{
		root = merge(new Node(x), root);
	}
	void insert(T&& x)
	{
		root = merge(new lheap(std::move(x)), root);
	}
	void deleteMin()
	{
		Node* oldNode = root;
		root = merge(root->left, root->right);
		delete oldNode;
	}
	void deleteMin(T& minItem)
	{
		minItem = findMin();
		deleteMin();
	}
	void makeEmpty()
	{
		reclaimMemory(root);
		root = nullptr;
	}
	void merge(lheap& rhs)
	{
		if (this == rhs)return;
		root = merge(root, rhs.root);
		rhs.root = nullptr;
	}
	void swap(lheap& rhs)
	{
		std::swap(*this, rhs);
	}
	
private:
	struct Node
	{
		Node* left;
		Node* right;
		T data;
		int npl;

		Node() :data(T()), left(nullptr), right(nullptr),npl(0) {}
		Node(const T& d, Node* l = nullptr, Node* r = nullptr,int np=0) :data(d), left(l), right(r),npl(np) {}
		Node(T&& d, Node* l, Node* r, int np = 0) :data(std::move(d)), left(l), right(r),npl(np) {}
	};
	Node* root;

	Node* clone(Node*& t)const
	{
		if (t == nullptr) { return nullptr; }
		return new Node(t->data, clone(t->left), clone(t->right),t->npl);
	}
	Node* merge(Node* h1, Node* h2)
	{
		if (h1 == nullptr)return h2;
		if (h2 == nullptr)return h1;
		if (h1->data < h2->data)return merge1(h1, h2);
		else return merge1(h2, h1);
	}
	Node* merge1(Node* h1, Node* h2)
	{
		if (h1->left == nullptr) h1->left = h2;
		else
		{
			h1->right = merge(h1->right, h2);
			if (h1->left->npl < h1->right->npl)
				swapChildren(h1);
			h1->npl = h1->right->npl + 1;
		}
		return h1;
	}
	void swapChildren(Node* t)
	{
		Node* tmp = t->left;
		t->left = t->right;
		t->right = tmp;
	}
	void reclaimMemory(Node* t)
	{
		if (t != nullptr) {
			reclaimMemory(t->left);
			reclaimMemory(t->right);
			delete t;
		}
	}
};
#endif // !LHEAP_H
