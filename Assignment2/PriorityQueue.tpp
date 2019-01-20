/*
 * PriorityQueue.cpp
 *
 *  Created on: 15-Jan-2019
 *      Author: e11
 */

#include "PriorityQueue.h"
#include<iostream>
using namespace std;
template<typename T>
PriorityQueue<T>::PriorityQueue() {
	// TODO Auto-generated constructor stub
	front = NULL;
	rear = NULL;
}
template<typename T>
PriorityQueue<T>::~PriorityQueue() {
	// TODO Auto-generated destructor stub
	Node *t;
	while(front != NULL)
	{
		t=front;
		front=front->next;
		delete(t);
	}
	rear=NULL;
}

template<typename T>
void PriorityQueue<T>::enqueue(T data,int priority)
{
	Node *temp= new Node;
	temp->priority = priority;
	temp->data = data;
	temp->next = NULL;
	if(isEmpty())
	{
		front=temp;
		rear=temp;
	}
	else
	{
		rear->next = temp;
		rear = temp;
	}
}
template<typename T>
T PriorityQueue<T>::dequeue()
{

	Node *current = front;
	Node *temp1 = front;
	Node *temp2;
	while(temp1 != NULL)
	{
		if(temp1->priority > current->priority)
			current = temp1;
		temp1=temp1->next;
	}
	temp1=front;
	if(current != front)
	{
		while(temp1 != NULL)
		{
			if(temp1==current)
				break;
			temp2=temp1;
			temp1=temp1->next;
		}
		temp2->next=current->next;
	}
	else
		front=front->next;
	T data= current->data;
	delete(current);		
	return data;
}

template<typename T>
bool PriorityQueue<T>::isEmpty()
{
	if(front == NULL)
		return true;
	return false;
}
template <typename T>
void PriorityQueue<T>::sendAll(T *store,int count)
{
	int c=0;
	Node *current=front;
	while(c!=count && current!=NULL)
	{
		store[c]=current->data;
		current=current->next;
		c++;
	}	
}

