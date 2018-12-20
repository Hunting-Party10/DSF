/*
 * LinkedList.h
 *
 *  Created on: 02-Jul-2009
 *      Author: e11
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

template <typename T,int size>
class LinkedList {
	private:
	typedef struct Node
	{
		T data;
		struct Node *next;
		struct Node *prev;
	}Node;
	Node *head;
	Node *tail;
public:
	LinkedList();
	virtual ~LinkedList();
	void addtoStart(T);
	void append(T);
	int insertAt(T,int);
	T removeFromFront();
	T removeFromBack();
	T removeFrom(int);
};
#include "LinkedList.tpp";
#endif /* LINKEDLIST_H_ */
