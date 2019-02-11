//============================================================================
// Name        : Assignment4.cpp
// Author      : Atharva Joshi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Stack.h"
#include<string.h>
#define expsize 30
#define max 64
using namespace std;


template <typename T>
class BinaryTree {
	struct Node
	{
		T data;
		struct Node *left;
		struct Node *right;
	};
	Node *root;
public:
	BinaryTree();
	~BinaryTree();
	void deleteTree(Node*);
	void constructExpression(char[]);
	void Rpreorder();
	void Rpostorder();
	void Rinorder();
	void inorder(Node*);
	void preorder(Node*);
	void postorder(Node*);
	void NRpreorder();
	void NRpostorder();
	void NRinorder();
};

template<typename T>
BinaryTree<T>::BinaryTree() {
	root = NULL;
	// TODO Auto-generated constructor stub
}
template<typename T>
BinaryTree<T>::~BinaryTree() {
	//do post order traversal and keep deleting Nodes
	deleteTree(root);
	// TODO Auto-generated destructor stub
}
template<typename T>
void BinaryTree<T>::deleteTree(Node *r) {
	if(r == NULL)
		return;
	deleteTree(r->left);
	deleteTree(r->right);
	delete r;
}

template <typename T>
void BinaryTree<T>::constructExpression(char postfix[])
{
	Stack<Node*> s;
	for (int i = 0; i < strlen(postfix); ++i)
	{
		//cout<<postfix[i];
		if(isalnum(postfix[i]))
		{
			Node *temp = new Node;
			temp->data = postfix[i];
			temp->left = NULL;
			temp->right = NULL;
			s.push(temp);
		}
		else
		{
			Node *t1 = s.pop();
			Node *t2 = s.pop();
			Node *parent = new Node;
			parent->data = postfix[i];
			parent->left = t2;
			parent->right = t1;
			s.push(parent);
		}
	}
	root = s.pop();
}

template<typename T>
void BinaryTree<T>::Rinorder()
{
	cout<<"[ ";
	inorder(root);
	cout<<" ]";
}
template <typename T>
void BinaryTree<T>::Rpreorder()
{
	cout<<"[ ";
	preorder(root);
	cout<<" ]";
}
template <typename T>
void BinaryTree<T>::Rpostorder()
{
	cout<<"[ ";
	postorder(root);
	cout<<" ]";
}


template<typename T>
void BinaryTree<T>::inorder(Node *root)
{
	if(root != NULL)
	{
		inorder(root->left);
		cout<<root->data<<" ";
		inorder(root->right);
	}
}
template <typename T>
void BinaryTree<T>::preorder(Node *root)
{
	if(root != NULL)
		{
			cout<<root->data<<" ";
			inorder(root->left);
			inorder(root->right);
		}
}
template <typename T>
void BinaryTree<T>::postorder(Node *root)
{
	if(root != NULL)
	{
		inorder(root->left);
		inorder(root->right);
		cout<<root->data<<" ";
	}
}

template <typename T>
void BinaryTree<T>::NRpreorder()
{
	Stack<Node*> s;
	s.push(root);
	cout<<"[";
	while(!s.isEmpty())
	{
		Node *temp = s.pop();
		cout<<temp->data<<" ";
		if(temp->left != NULL)
			s.push(temp->left);
		if(temp->right != NULL)
			s.push(temp->right);
	}
	cout<<"]";
}

template <typename T>
void BinaryTree<T>::NRpostorder()
{
	if(root == NULL)
		return;
	cout<<"[ ";
	Stack<Node*> s1;
	Stack<Node*> s2;
	s1.push(root);
	Node *temp;
	while(!s1.isEmpty())
	{
		temp = s1.pop();
		s2.push(temp);
		if(temp->left != NULL)
			s1.push(temp->left);
		if(temp->right != NULL)
			s2.push(temp->right);
	}
	while(!s2.isEmpty())
	{
		temp = s2.pop();
		cout<<temp->data<<" ";
	}
	cout<<"]";
}

template <typename T>
void BinaryTree<T>::NRinorder()
{
	Stack<Node*> s;
	cout<<"[ ";
	Node *temp = root;
		
	while(temp != NULL || !s.isEmpty())
	{
		while(temp !=NULL)
		{
			s.push(temp);
			temp = temp->left;
		}
		temp = s.pop();
		cout<<temp->data<<" ";
		temp = temp->right;
	}
	cout<<"]";
}




int main() {
	int choice1,choice2;
	char postexp[expsize];
	BinaryTree<char> B;
	cout<<"Enter Expression to construct an Expression Tree:";
	cin.getline(postexp,expsize);
	cout<<"\n";
	B.constructExpression(postexp);
	do
	{

		cout<<"\n\nPress 1 to display Expression\n";
		cout<<"Press 2 Recursive Traversals\n";
		cout<<"Press 3 Non Recursive Traversals\n";
		cout<<"Press 4 to Exit\n";
		cout<<"Enter Choice:";
		cin>>choice1;
		switch(choice1)
		{
		case 1:
			cout<<"Entered Expression is:";
			cout<<postexp;
			break;
		case 2:
			do
			{
				cout<<"\n\nPress 1 for Recursive Pre-order Traversal\n";
				cout<<"Press 2 for Recursive In-Order Traversal\n";
				cout<<"Press 3 for Recursive Post-Order Traversal\n";
				cout<<"Press 4 to Exit\n";
				cout<<"Enter Choice:";
				cin>>choice2;
				switch(choice2)
				{
				case 1:
					B.Rpreorder();
					break;
				case 2:
					B.Rinorder();
					break;
				case 3:
					B.Rpostorder();
					break;
				case 4:
					break;
				default:
					cout<<"Enter Valid Option\n";
				}
				cout<<"\n\n";
			}
			while(choice2 != 4);
			break;
		case 3:
			do
			{
				cout<<"\n\nPress 1 for Non-Recursive Pre-order Traversal\n";
				cout<<"Press 2 for Non-Recursive In-Order Traversal\n";
				cout<<"Press 3 for Non-Recursive Post-Order Traversal\n";
				cout<<"Press 4 to Exit\n";
				cout<<"Enter Choice:";
				cin>>choice2;
				switch(choice2)
				{
				case 1:
					B.NRpreorder();
					break;
				case 2:
					B.NRinorder();
					break;
				case 3:
					B.NRpostorder();
					break;
				case 4:
					break;
				default:
					cout<<"Enter Valid Option\n";
				}
				cout<<"\n\n";
			}
			while(choice2 != 4);
			break;
		case 4:
			break;
		default:
			cout<<"Enter valid Choice\n";
		}
	}
	while(choice1 != 4);
}
