/*
 * Stack.cpp
 *
 *  Created on: 02-Jul-2009
 *      Author: e11
 */

#include "Stack.h"

template <typename T>

Stack<T>::Stack() {
	top = NULL;
}
template <typename T>
Stack<T>::~Stack() {
	while(top != NULL)
	{
		Node *temp=top;
		top=top->next;
		delete temp;
	}
}
template <typename T>
void Stack<T>::push(T n)
{
	Node *temp=new Node;
	temp->data=n;
	temp->next=top;
	top = temp;
}
template <typename T>
T Stack<T>::pop()
{
	T data= top->data;
	Node *temp=top;
	top=top->next;
	delete temp;
	return data;
}
template <typename T>
T Stack<T>::peep()
{
	if(top != NULL)
		return top->data;
	return 0;
}

template <typename T>
bool Stack<T>::isEmpty()
{
	if(top==NULL)
		return true;
	return false;
}
