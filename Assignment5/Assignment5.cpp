#include<iostream>
#include"Stack.h"
#include<limits>
using namespace std;


class BST
{
private:
	struct Node
	{
		struct Node *left;
		struct Node *right;
		int data;
	};	
	Node *root;
	bool invert;
	void destroyTree(Node*);
	void fixBST(Node **,Node **);
	void printgivenLevel(Node*,int);
	int getDepth(Node*);
	
public:
	BST(){root = NULL; invert = false;}
	~BST(){destroyTree(root);}
	int insert(int);
	void NRinorder();
	int search(int);
	int Delete(int);
	void display();
	int depth();
	void mirrorTree();
	void mirror(Node*);
};


void BST::destroyTree(Node *root)
{
	if(root == NULL)
		return;
	destroyTree(root->left);
	destroyTree(root->right);
	delete root;
}

int BST::insert(int data)
{
	if(root == NULL)
	{
		root = new Node;
		root->left = NULL;
		root->right = NULL;
		root->data = data;
		return 1;
	}	
	Node *current = root;
	while(true)
	{
		if(data == current->data)
			return 0;
		if(invert == false)
		{
			if( data > current->data)
			{
				if(current->right != NULL)
					current = current->right;
				else
				{
					Node *temp = new Node;
					temp->data = data;
					temp->left = NULL;
					temp ->right = NULL;
					current->right = temp;
					return 1;
				}		
			}
			else
			{
				if(current->left != NULL)
					current = current->left;
				else
				{
					Node *temp = new Node;
					temp->data = data;
					temp->left = NULL;
					temp ->right = NULL;
					current->left = temp;
					return 1;
				}
			}
		}
		else
		{
			if( data > current->data)
			{
				
				if(current->left != NULL)
					current = current->left;
				else
				{
					Node *temp = new Node;
					temp->data = data;
					temp->left = NULL;
					temp ->right = NULL;
					current->left = temp;
					return 1;
				}		
			}
			else
			{
				if(current->right != NULL)
					current = current->right;
				else
				{
					Node *temp = new Node;
					temp->data = data;
					temp->left = NULL;
					temp ->right = NULL;
					current->right = temp;
					return 1;
				}
			}
		}
	}
}

void BST::NRinorder()
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

int BST::search(int data)
{
	if(root == NULL)
		return 0;
	Node *current = root;
	while(true)
	{
		if(data == current->data)
			return 1;
		if( data > current->data)
		{
			if(current->right != NULL)
				current = current->right;
			else
				return 0;		
		}
		else
		{
			if(current->left != NULL)
				current = current->left;
			else
				return 0;
		}
	}
}

int BST::Delete(int data)
{
	if(root == NULL)
		return 0;
	Node *current = root;
	Node *previous;
	while(true)
	{
		if(data == current->data)
		{
			fixBST(&current,&previous);
			return 1;
		}
		if( data > current->data)
		{
			if(current->right != NULL)
			{
				previous = current;
				current = current->right;
				
			}
			else
				return 0;		
		}
		else
		{
			if(current->left != NULL)
			{
				previous = current;
				current = current->left;
			}
			else
				return 0;
		}
	}
}

void BST::fixBST(Node **current,Node **previous)
{
	if((*current)->left == NULL && (*current)->right == NULL)
	{
		if((*previous)->left == *current)
			(*previous)->left = NULL;
		else
			(*previous)->right = NULL;
		delete *current;
		return;
	}
	if((*current)->left != NULL && (*current)->right != NULL)
	{
		Node *predecessor = (*current)->left;
		Node *predecessor_parent;
		while(predecessor->right != NULL)
		{
			predecessor_parent = predecessor;
			predecessor = predecessor->right;
		}
		int t = predecessor->data;
		predecessor->data = (*current)->data;
		(*current)->data = t;
		fixBST(&predecessor,&predecessor_parent);
		return;
	}
	else
	{
		Node *temp;
		if((*current)->left != NULL)
			temp=(*current)->left;
		else
			temp= (*current)->right;
		if((*previous)->left == *current)
			(*previous)->left = temp;
		else
			(*previous)->right = temp;
		delete *current;
		return;	
	}
}

void BST::display()
{
	for(int i=1;i<=depth();i++)
	{
		cout<<"Level "<<i<<":";
		printgivenLevel(root,i);
		cout<<"\n";
	}
}


void BST::printgivenLevel(Node *t,int level)
{
	if(level == 1)
		cout<<t->data<<" ";
	else
	{
		if(t->left != NULL)
			printgivenLevel(t->left,level-1);
		if(t->right!= NULL)
			printgivenLevel(t->right,level-1);
	}
}

int BST::depth()
{
	if(root == NULL)
		return 0;
	return getDepth(root);
}

int BST::getDepth(Node *current)
{
	int left=0,right=0;
	if(current->left != NULL)
		left=getDepth(current->left);
	if(current->right != NULL)
		right=getDepth(current->right);
	return (max(left,right)+1);
}

void BST::mirrorTree()
{
	mirror(root);
	if(invert == false)
		invert = true;
	else
		invert = false;
}

void BST::mirror(Node *root)
{
	if(root != NULL)
	{
		mirror(root->left);
		mirror(root->right);

		Node *temp = root->left;
		root->left = root->right;
		root->right = temp;
	}
}

int main()
{
	int choice;
	int data;
	int flag;
	BST T;
	do
	{
		cout<<"\n\nPress 1 to insert Element\n";
		cout<<"Press 2 to delete Element\n";
		cout<<"Press 3 to search Element\n";
		cout<<"Press 4 for Mirrored BST\n";
		cout<<"Press 5 for Level order display\n";
		cout<<"Press 6 for In-Order display\n";
		cout<<"Press 7 to Exit\n";
		cout<<"Enter Choice:";
		cin>>choice;
		switch(choice)
		{
			case 1:
				cout<<"\nEnter Data to be Added:";
				cin>>data;
				flag = T.insert(data);
				if(flag == 0)
					cout<<"\nData Already Exists\n";
				else
					cout<<"\nElement Inserted\n";
				break;
			case 2:
				cout<<"\nEnter Data to be Deleted:";
				cin>>data;
				flag = T.Delete(data);
				if(flag == 0)
					cout<<"\nData does not Exist\n";
				else
					cout<<"\nData Deleted\n";
				break;
			case 3:
				cout<<"\nEnter Data to be searched:";
				cin>>data;
				flag = T.search(data);
				if(flag == 0)
					cout<<"\nData does not Exist\n";
				else
					cout<<"\nData found\n";
				break;
			case 4:
				T.mirrorTree();
				cout<<"Tree Mirrored\n";
				break;
			case 5:
				T.display();
				break;
			case 6:
				T.NRinorder();
				break;
			case 7:
				break;
			default:
				cout<<"\nEnter Valid choice\n";
		}
	}
	while(choice != 7);
	return 0;
}














