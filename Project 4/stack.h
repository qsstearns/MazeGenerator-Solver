#ifndef _STACK_H
#define _STACK_H

#include "exceptions.h"

const int STACK_SIZE = 16;

template <class StackType>
class Stack {
public:
	Stack(double m = 2.0, double b = 0.0) {

		top = 0;

		this->m = m;
		this->b = b;

		capacity = STACK_SIZE;

		data = new StackType[capacity];
	}
	~Stack() {

		delete[] data;
	}

	bool isEmpty() { return top == 0; }
	int size() { return top; }

	void clear() { top = 0; }

	void push(const StackType& d) {

		if (top == capacity) {
			uint32_t
				tmpCap = m * capacity + b;

			if (tmpCap <= capacity)
				throw ContainerFullException();

			StackType
				* tmpData = new StackType[tmpCap];

			if (tmpData == nullptr)
				throw ContainerFullException();

			for (uint32_t i = 0; i < capacity; i++)
				tmpData[i] = data[i];

			delete[] data;

			data = tmpData;

			capacity = tmpCap;
		}

		data[top++] = d;
	}

	StackType pop() {

		if (top == 0)
			throw ContainerEmptyException();

		return data[--top];
	}

	StackType peek() {

		if (top == 0)
			throw ContainerEmptyException();

		return data[top - 1];
	}


private:
	StackType
		* data;
	uint32_t
		top,
		capacity;
	double
		m, b;
};

#endif

