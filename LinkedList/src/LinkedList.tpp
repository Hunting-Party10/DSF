//============================================================================
// Name        : LinkedList.cpp
// Author      : Atharva Joshi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "LinkedList.h"
template <typename T,int size>
LinkedList<T,size>::LinkedList() {
	// TODO Auto-generated constructor stub
	head=NULL;
	tail=NULL;
}
template <typename T,int size>
LinkedList<T,size>::~LinkedList() {
	// TODO Auto-generated destructor stub
	while(head!=NULL)
	{
		Node *temp=head;
		head=head->next;
		delete temp;
	}
}
template <typename T,int size>
void LinkedList<T,size>::addtoStart(T n)
{
	Node *newNode=new Node;
	newNode->next=NULL;
	newNode->prev=NULL;
	newNode->data=n;
	newNode->next=head;
	if(head != NULL)
		head->prev=newNode;
	head=newNode;
	if(tail==NULL)
		tail=head;
}
template <typename T,int size>
void LinkedList<T,size>::append(T n)
{
	Node *newNode=new Node;
	newNode->next=NULL;
	newNode->prev=NULL;
	newNode->data=n;
	newNode->prev=tail;
	if(tail!=NULL)
		tail->next=newNode;
	tail=newNode;
	if(head==NULL)
		head=tail;
}
template <typename T,int size>
int LinkedList<T,size>::insertAt(T n,int pos)
{

}
