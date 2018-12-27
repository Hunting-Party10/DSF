/*
 * Stack.h
 *
 *  Created on: 02-Jul-2009
 *      Author: e11
 */

#ifndef STACK_H_
#define STACK_H_


template <typename T,int size>
class Stack {
private:
	typedef struct Node
	{
		T data;
		struct Node *next;
	}Node;
	Node *top;
public:
	Stack();
	virtual ~Stack();
	void push(T);
	bool isEmpty();
	T pop();
	T peep();
};

#include "Stack.tpp"

#endif /* STACK_H_ */
