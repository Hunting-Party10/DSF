/*
 * PriorityQueue.h
 *
 *  Created on: 15-Jan-2019
 *      Author: e11
 */

#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

template <typename T>
class PriorityQueue {
private:
	typedef	struct	Node
	{
		int priority;
		T data;
		struct Node *next;
	}Node;
	Node *front;
	Node *rear;
public:
	PriorityQueue();
	virtual ~PriorityQueue();
	void enqueue(T,int);
	T dequeue();
	bool isEmpty();
	void sendAll(T*,int);
};
#include"PriorityQueue.tpp"
#endif /* PRIORITYQUEUE_H_ */
