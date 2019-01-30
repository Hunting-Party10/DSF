/*
 * BinaryTree.cpp
 *
 *  Created on: 02-Jul-2009
 *      Author: e11
 */
#include<iostream>
#include<algorithm>
using namespace std;

template <typename T>
class BinaryTree {
	typedef struct Node
	{
		T data;
		struct Node *left;
		struct Node *right;
	}Node;
	Node *root;
public:
	BinaryTree();
	virtual ~BinaryTree();
	void deleteTree(Node *);
	void display();
	bool clone(BinaryTree);
	void insert(T);
	int depth();
	int getDepth(Node*);
	bool isEmpty();
	void printgivenLevel(Node*,int);
	//void showleaves();
};
template<typename T>
BinaryTree<T>::BinaryTree() {
	root = NULL;
	// TODO Auto-generated constructor stub

}
template<typename T>
BinaryTree<T>::~BinaryTree() {
	//do post order traversal and keep deleting nodes
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
template<typename T>
void BinaryTree<T>::display()
{
	for(int i=1;i<=depth();i++)
	{
		printgivenLevel(root,i);
	}
}
template<typename T>
void BinaryTree<T>::printgivenLevel(Node *t,int level)
{
	if(level == 1)
	{
		cout<<t->data<<" ";
	}
	else
	{
		if(t->left != NULL)
			printgivenLevel(t->left,level-1);
		if(t->right!= NULL)
			printgivenLevel(t->right,level-1);
	}
}
template <typename T>
void BinaryTree<T>::insert(T element)
{
	if(isEmpty())
	{
		root= new Node;
		root->data = element;
		root->left = NULL;
		root->right = NULL;
		return;
	}
	Node *parent=root;
	Node *child=parent;
	bool added = false,left=false;
	while(!added)
	{
		if(child == NULL)
		{
			if(left == true)
			{
				parent->left = new Node;
				parent->left->data=element;
				parent->left->left=NULL;
				parent->left->right=NULL;
			}
			else
			{
				parent->right = new Node;
				parent->right->data=element;
				parent->right->left=NULL;
				parent->right->right=NULL;
			}
			added = true;
		}
		else
		{
			parent= child;
			left=false;
			cout<<"\nCurrent Node : "<<parent->data<<"\n\n";
			char choice='\0';
			do
			{
				cout<<"Do you want to add to the Left or right(L/R) :";
				cin>>choice;
				switch(choice)
				{
				case 'L':
					left = true;
					child=parent->left;
					break;
				case 'R':
					child=parent->right;
					break;
				default:
					cout<<"Invalid  Option\n";
				}
			}
			while(choice != 'L' && choice != 'R');

		}
	}
}
template<typename T>
int BinaryTree<T>::depth()
{
	if(isEmpty())
		return 0;
	return getDepth(root);
}
template<typename T>
int BinaryTree<T>::getDepth(Node *current)
{
	int left=0,right=0;
	if(current->left != NULL)
		left=getDepth(current->left);
	if(current->right != NULL)
		right=getDepth(current->right);
	return (max(left,right)+1);
}
template <typename T>
bool BinaryTree<T>::isEmpty()
{
	return root == NULL;
}

int main()
{
	BinaryTree<int> T,clone;
	int data;
	int choice;
	do
	{
		cout<<"\n\nPress 1 to insert into binary tree\n";
		cout<<"Press 2 to display binary tree\n";
		cout<<"Press 3 for depth of a binary tree\n";
		cout<<"Press 4 to display all leaves\n";
		cout<<"Press 5 to clone binary tree\n";
		cout<<"Press 6 to Exit\n";
		cout<<"Enter Choice:";
		cin>>choice;
		switch(choice)
		{
		case 1:
			cout<<"Enter Data you want to insert:";
			cin>>data;
			cout<<"\n";
			T.insert(data);
			break;
		case 2:
			T.display();
			break;
		case 3:
			cout<<"Depth of Binary Tree is: "<<T.depth();
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		}
	}
	while(choice!=6);
	return 0;
}

