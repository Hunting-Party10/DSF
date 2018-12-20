/*
 * Stack.cpp
 *
 *  Created on: 02-Jul-2009
 *      Author: e11
 */

#include "Stack.h"

template <typename T,int size>

Stack<T,size>::Stack() {
	top = NULL;
}
template <typename T,int size>
Stack<T,size>::~Stack() {
	while(top != NULL)
	{
		Node *temp=top;
		top=top->next;
		delete temp;
	}
}
template <typename T,int size>
void Stack<T,size>::push(T n)
{
	Node *temp=new Node;
	temp->data=n;
	temp->next=top;
	top = temp;
}
template <typename T,int size>
T Stack<T,size>::pop()
{
	T data= top->data;
	Node *temp=top;
	top=top->next;
	delete temp;
	return data;
}
template <typename T,int size>
T Stack<T,size>::peep()
{
	if(top != NULL)
		return top->data;
	return 0;
}
