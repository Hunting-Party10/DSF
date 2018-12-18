/*
 * Stack.cpp
 *
 *  Created on: 02-Jul-2009
 *      Author: e11
 */

#include "Stack.h"
template <typename T>
Stack<T>::Stack(int n) {
	// TODO Auto-generated constructor stub
	data = new T[n];
	top = -1;
	stackSize = n;
}
template <typename T>
Stack<T>::~Stack() {
	// TODO Auto-generated destructor stub
	delete data;
}
template <typename T>
bool Stack<T>::isEmpty()
{
	if(top == -1)
		return true;
	return false;
}
template <typename T>
bool Stack<T>::isFull()
{
	if(top == stackSize-1)
		return true;
	return false;
}
template <typename T>
T Stack<T>::pop()
{
	if(!isEmpty())
		return data[top--];
	return 0;
}
template <typename T>
void Stack<T>::push(T n)
{
	if(!isFull())
		data[++top] = n;
}

