#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <iostream>

using namespace std;

class DisjointSet {
	public:
		DisjointSet(int n) {
			elements = new int[n];
			rank = new int[n];

			for (int i = 0; i < n; i++) {
				elements[i] = i;
				rank[i] = 0;
			}
		}

		~DisjointSet() {
			delete[] elements;
			delete[] rank;
		}

		int find(int a) {
			if (elements[a] != a) {
				elements[a] = find(elements[a]);
			}

			return elements[a];
		}

		void join(int a, int b) {
			a = find(a);
			b = find(b);

			if (a != b) {
				if (rank[a] < rank[b]) {
					elements[a] = b;
				}
				else {
					if (rank[a] == rank[b]) {
						rank[a] = rank[a] + 1;
					}
					elements[b] = a;
				}
			}
		}


	private:
		int* elements;
		int* rank;
};

#endif
