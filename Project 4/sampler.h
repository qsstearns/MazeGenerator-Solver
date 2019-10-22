#ifndef SAMPLER_H
#define SAMPLER_H

#include <iostream>

using namespace std;

class Sampler {
public:
	Sampler(int n) {
		num = n;
		arr = new int[num];

		for (int i = 0; i < num; i++)
			arr[i] = i;
	}

	~Sampler() { delete[] arr; }

	int getSample() {
		int i, e;

		i = rand() % num;
		e = arr[i];
		num = num - 1;
		arr[i] = arr[num];

		return e;
	}

private:
	int num, *arr;
};

#endif
