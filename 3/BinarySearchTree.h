#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include<algorithm>
#include<iostream>
using namespace std;
template<typename T>
class btree
{	
public:
		btree() :root(nullptr) {}
		btree(const btree& rhs) : root(clone(rhs.root)){}
		btree(btree&& rhs) :root(rhs.root)
		{
			rhs.root = nullptr;
		}
		~btree()
		{
			delete [] root;
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
		bool isEmpty()const
		{
			return root == nullptr;
		}
		void makeEmpty()
		{
			makeEmpty(root);
		}
		void insert(const T& x)
		{
			insert(x,root);
		}
		void insert(T&& x)
		{
			insert(std::move(x), root);
		}
		void remove(const T& x)
		{
			remove(x, root);
		}
		void inorder()
		{
			inorder(root);
		}
		btree& operator=(const btree& rhs)
		{
			if (this != &rhs) {
				makeEmpty();
				clone(rhs.root);
			}
		}
	private:
		struct Node
		{
			Node* lch;
			Node* rch;
			T data;

			Node() :data(T()), lch(nullptr), rch(nullptr) {}
			Node(const T& d, Node* l = nullptr, Node* r = nullptr) :data(d), lch(l), rch(r) {}
			Node(T&& d, Node* l, Node* r) :data(std::move(d)), lch(l), rch(r) {}
		};
		Node* clone(Node*& t)const
		{
			if (t == nullptr) { return nullptr; }
			return new Node(t->data, clone(t->lch), clone(t->rch));
		}
		void insert(const T& x, Node*& t)
		{
			if (t == nullptr) { t = new Node{ x,nullptr,nullptr }; }
			else if (x > t->data) { insert(x, t->rch); }
			else if (x < t->data) { insert(x, t->lch); }
			else
				;
		}
		void insert(T&& x, Node*& t)
		{
			if (t == nullptr) { t = new Node{ std::move(x),nullptr,nullptr }; }
			else if (x > t->data) { insert(std::move(x), t->rch); }
			else if (x < t->data) { insert(std::move(x), t->lch); }
			else
				;
		}
		void remove(const T& x, Node*& t)
		{
			if (t == nullptr) return;
			if (x > t->data) { remove(x, t->rch); }
			else if (x < t->data) { remove(x, t->rch); }
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
		void inorder(Node*& t)
		{
			if (t!=nullptr)
			{inorder(t->lch);
			cout << t->data;
			inorder(t->rch);
			}
		}
		Node* root;
	};
#endif // !BINARYSEARCHTREE_H

