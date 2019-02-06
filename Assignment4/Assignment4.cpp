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
	void constructExpression(char[],char[]);
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
void BinaryTree<T>::constructExpression(char infix[],char postfix[])
{

}

int priority(char op)
{
	switch(op)
	{
		case '^':
			return 6;
		case '/':
			return 5;
		case '*':
			return 5;
		case '+':
			return 4;
		case '-':
			return 3;
		case '!':
			return 2;
		case '(':
			return 0;
		default:
			return -1;
	}
}
char assosivity(char op)
{
	switch(op)
	{
		case '^':
			return 'r';
		default:
			return 'l';
	}
}
void postfix(char exp[],char ans[])
{
	int len=strlen(exp);
	ans=new char(len);
	int k=0;
	Stack<char,max> s;
	for(int i=0;i<len;i++)
	{
		if(priority(exp[i]) == -1)
		{
			if(exp[i]==')')
			{
				char t;
				do
				{
					t=s.pop();
					if(t != '(')
						ans[k++]=t;
				}
				while(t!='(');
			}
			else
				ans[k++]=exp[i];
		}
		else if(priority(exp[i]) == 0)
			s.push(exp[i]);
		else
		{
			while(priority(s.peep()) > priority(exp[i]))
				ans[k++]=s.pop();
			if(priority(s.peep()) == priority(exp[i]) && assosivity(exp[i]) == 'l')
				ans[k++]=s.pop();
			s.push(exp[i]);
		}
	}
	while(!s.isEmpty())
		ans[k++]=s.pop();
}



int main() {
	int choice1,choice2;
	char exp[expsize],postexp[expsize];
	cout<<"Enter Expression to construct an Expression Tree:\n";
	cin.ignore();
	cin.getline(exp,expsize);
	do
	{

		cout<<"Press 2 to display Expression\n";
		cout<<"Press 3 Recursive Traversals\n";
		cout<<"Press 4 Non Recursive Traversals\n";
		cout<<"Press 5 to Exit\n";
		cin>>choice1;
		switch(choice1)
		{
		case 1:
			cout<<"Entered Expression is:";
			cout<<exp;
			break;
		case 2:
			do
			{
				cout<<"\n\nPress 1 for Recursive Pre-order Traversal\n";
				cout<<"Press 2 for Recursive In-Order Traversal\n";
				cout<<"Press 3 for Recursive Post-Order Traversal\n";
				cout<<"Press 4 to Exit";
				cin>>choice2;
				switch(choice2)
				{
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				default:
					cout<<"Enter Valid Option\n";
				}
			}
			while(choice2 != 4);
			break;
		case 3:
			do
			{
				cout<<"\n\nPress 1 for Non-Recursive Pre-order Traversal\n";
				cout<<"Press 2 for Non-Recursive In-Order Traversal\n";
				cout<<"Press 3 for Non-Recursive Post-Order Traversal\n";
				cout<<"Press 4 to Exit";
				cin>>choice2;
				switch(choice2)
				{
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				default:
					cout<<"Enter Valid Option\n";
				}
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
