/*
 * Stack.h
 *
 *  Created on: 02-Jul-2009
 *      Author: e11
 */

#ifndef STACK_H_
#define STACK_H_

template <typename T>
class Stack {
private:
	T  *data;
	int top;
	int stackSize;
public:
	//Stack();
	Stack(int);
	virtual ~Stack();
	bool isEmpty();
	bool isFull();
	void push(T);
	T pop();
};

#include "Stack.tpp"
#endif /* STACK_H_ */
