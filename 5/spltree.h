#ifndef AVLTREE_H
#define AVLTREE_H
#include<algorithm>
#include<iostream>
#include<queue>
#include<string>
using namespace std;
int xx;
template<typename T>
class avltree
{
public:
	avltree() :root(nullptr) {}
	avltree(avltree& rhs) : root(clone(rhs.root)) {}
	avltree(avltree&& rhs) :root(rhs.root)
	{
		rhs.root = nullptr;
	}
	~avltree()
	{
		delete[] root;
	}

	const T& findMin()const
	{
		return findMin(root)->data;
	}
	const T& findMax()const
	{
		return findMax(root)->data;
	}
	bool contain(const T& x)const
	{
		return contains(x, root);
	}
	bool empty()const
	{
		return root == nullptr;
	}
	int size()
	{
		return Size(root);
	}
	void makeEmpty()
	{
		makeEmpty(root);
	}
	bool insert(const T& x)
	{	
		int siz = size();
		insert(x, root);
		return size() != siz;
	}
	bool remove(const T& x)
	{
		int siz = size();
		remove(x, root);
		return size() != siz;
	}
	void inorder()
	{
		inorder(root);
	}
	void Display()
	{
		Display(root);
	}
	avltree& operator=(const avltree& rhs)
	{
		if (this != &rhs) {
			makeEmpty();
			clone(rhs.root);
		}
		return *this;
	}
	avltree& operator=(avltree& rhs)
	{
		if (this != &rhs) {
			makeEmpty();
			root = rhs.root;
			rhs.root = nullptr;
		}
		return *this;
	}
private:
	struct Node
	{
		Node* lch;
		Node* rch;
		T data;
		int height;

		Node() :data(T()), lch(nullptr), rch(nullptr) {}
		Node(const T& d, Node* l = nullptr, Node* r = nullptr,int h=0) :data(d), lch(l), rch(r),height(h) {}
		Node(T&& d, Node* l, Node* r,int h) :data(std::move(d)), lch(l), rch(r),height(h) {}
		Node(const Node&) = delete;
	};
	Node* clone(Node*& t)const
	{
		if (t == nullptr) { return nullptr; }
		return new Node(t->data, clone(t->lch), clone(t->rch));
	}
	int height(Node* t)const
	{
		return t == nullptr ? -1 :t->height;
	}
	void insert(const T& x, Node*& t)
	{
		if (t == nullptr) { t =new Node{ x,nullptr,nullptr,}; }
		else if (x > t->data) { insert(x, t->rch); }
		else if (x < t->data) { insert(x, t->lch); }
		balance(t);
	}
	void insert(T&& x, Node*& t)
	{
		if (t == nullptr) { t = new Node{ std::move(x),nullptr,nullptr }; }
		else if (x > t->data) { insert(std::move(x), t->rch); }
		else if (x < t->data) { insert(std::move(x), t->lch); }
		balance(t);
	}
	static const int ALLOW_IMBALANCE = 1;
	void balance(Node*& t)
	{
		if (t == nullptr) return;
		if (height(t->lch) - height(t->rch) > ALLOW_IMBALANCE)
		{
			if (height(t->lch->lch) >= height(t->lch->rch))
			{
				rotatelch(t);
			}
			else
				doublerotatelch(t);
		}
		else if (height(t->rch) - height(t->lch) > ALLOW_IMBALANCE)
		{
			if (height(t->rch->rch) >= height(t->rch->lch))
			{
				rotaterch(t);
			}
			else
				doublerotaterch(t);
		}
		t->height = max(height(t->lch), height(t->rch)) + 1;
	}
	void remove(const T& x, Node*& t)
	{
		if (t == nullptr) return;
		if (x > t->data) { remove(x, t->rch); }
		else if (x < t->data) { remove(x, t->lch); }
		else if (t->rch != nullptr && t->lch != nullptr)
		{
			t->data = findMin(t->rch)->data;
			remove(t->data, t->rch);
		}
		else
		{
			Node* old = t;
			t = (t->lch != nullptr) ? t->lch : t->rch;
			delete old;
		}
		balance(t);
	}
	void rotatelch(Node*& t)
	{
		Node* k1 = t->lch;
		t->lch = k1->rch;
		k1->rch = t;
		t->height = max(height(t->lch), height(t->rch)) + 1;
		k1->height = max(height(k1->lch), t->height) + 1;
		t = k1;
	}
	void rotaterch(Node*& t)
	{
		Node* k1 = t->rch;
		t->rch = k1->lch;
		k1->lch = t;
		t->height = max(height(t->lch), height(t->rch)) + 1;
		k1->height = max(height(k1->rch), t->height) + 1;
		t = k1;
	}
	void doublerotatelch(Node*& t)
	{
		rotaterch(t->lch);
		rotatelch(t);
	}
	void doublerotaterch(Node*& t)
	{
		rotatelch(t->rch);
		rotaterch(t);
	}
	Node* findMin(Node* t)const
	{
		if (t == nullptr) { return nullptr; }
		if (t->lch == nullptr) { return t; }
		else findMin(t->lch);
	}
	Node* findMax(Node* t)const
	{
		if (t == nullptr) { return nullptr; }
		if (t->rch == nullptr) { return t; }
		else findMax(t->rch);
	}
	bool contains(const T& x, Node* t)const
	{
		if (t == nullptr) { return false; }
		else if (x > t->data) { contains(x, t->rch); }
		else if (x < t->data) { contains(x, t->lch); }
		else return true;
	}
	void makeEmpty(Node*& t)
	{
		if (t != nullptr)
		{
			makeEmpty(t->lch);
			makeEmpty(t->rch);
			delete t;
		}
		t = nullptr;
	}
	int Size(Node*& t)
	{
		if (!t) return NULL;
		return (Size(t->lch) + Size(t->rch)+1);
	}
	void inorder(Node*& t)
	{
		if (!t) return;
		inorder(t->lch);
		cout << t->data<<endl;
		inorder(t->rch);
	}
	void Display(Node*& t)
	{
		xx = 0;      //中序遍历前把xx设置成0
		inorder(t);     //中序遍历
		if (!xx) printf("    NULL");
		queue<Node*>q;
		if (t) q.push(t);
		while (!q.empty()) {//层序遍历
			int k = q.size(), p = 0;
			while (k--) {   //一次打印一层的节点，k表示一层的节点
				t = q.front();
				q.pop();
				if (t->lch) q.push(t->lch);
				if (t->rch) q.push(t->rch);
				string str = "";
				while (p < t->height) {
					str += " ";   //在节点的x坐标前打印空格
					p++;
				}p += to_string(t->data).size();
				printf("%s%d", str.c_str(), t->data);
			}
			printf("\n\n");
		}
	}
	
	Node* root;
};
#endif // !AVLTREE_H

