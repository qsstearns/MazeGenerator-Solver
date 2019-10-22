#include <iostream>
#include "DisjointSet.h"
#include "sampler.h"
#include "stack.h"
#include "pathfinder.h"

using namespace std;

void GenerateMaze(int, int);
void FindPath(uint8_t[][50], int, int);
int encode(int, int, int);

//uint8_t (*maze)[50];

int nr,
	nc;

int encode(int r, int c, int d) {
	int e;
	e = d * nr * nc + r * nc + c;
	return e;
}

void FindPath(uint8_t maze[][50], int nr, int nc) {
	Stack<int> S;
	int r, r3, c, c3, dir;

	S.push(encode(0, 0, 0));
	maze[0][0] |= VISITED;

	while (true) {
		int peek, wall_dir;
		peek = S.peek();
		c = peek % nc;
		peek /= nc;
		r = peek % nr;
		dir = peek / nr;

		switch (dir) {
			case 0: wall_dir = WALL_UP;
				break;
			case 1: wall_dir = WALL_RIGHT;
				break;
			case 2: wall_dir = WALL_DOWN;
				break;
			case 3: wall_dir = WALL_LEFT;
				break;
		}

		if ((r == (nr - 1)) && (c == (nc - 1))) {
			break;
		}

		if (dir == 4) {
			maze[r][c] |= DEAD_END;
			S.pop();
		}
		else {
			//let (rprime, cprime) be the next cell in direction d
			switch (dir) {
					//North
				case 0: r3 = r - 1;
					c3 = c;
					break;
					//East
				case 1: c3 = c + 1;
					r3 = r;
					break;
					//South
				case 2: r3 = r + 1;
					c3 = c;
					break;
					//West
				case 3: c3 = c - 1;
					r3 = r;
					break;

			}

			//replace encode(r,c,d) with encode(r,c,d+1) on top of stack
			S.pop();
			S.push(encode(r, c, dir+1));

			if ((maze[r][c] & wall_dir) == 0 && (maze[r3][c3] & VISITED) == 0) {
				S.push(encode(r3, c3, 0));
				maze[r3][c3] |= VISITED;
			}
		}
	}

}


void GenerateMaze(uint8_t maze[][50],int nr, int nc){
	int e, r, r2, c, c2, dir, i = 0;
	bool check;

    for(int r = 0; r < nr; r++){
        for(int c = 0; c < nc; c++){
            maze[r][c] = 15;
        }
    }

    DisjointSet ds(nr * nc);
    Sampler sampler(4*nr*nc);

    i = 0;
    while(i < ((nr * nc) - 1)){
        do{
            do{
							check = true;
							e = sampler.getSample();
							c = e % nc;
							e /= nc;
							r = e % nr;
							dir = e / nr;

							cout << "e: " << e << " c: " << c << " r: " << r << " dir: " << dir << endl;

							//column check 0
							if (c == 0 && dir == 3) {
								check = false;
							}
							//column check nc - 1
							if (c == nc-1  && dir == 1) {
								check = false;
							}
							//row check 0
							if (r == 0 && dir == 0) {
								cout << "foo" << endl;
								check = false;
							}
							//row check nr - 1
							if (r == nr -1 && dir == 2) {
								check = false;
							}
							//check nonexistent wall
							if ((maze[r][c] & (1 << dir)) == 0) {
								check = false;
							}
						}while (check == false);

						//set(r2, c2) to cell adjacent to (r1, c1) in given direction
						switch (dir) {
							//North
							case 0: r2 = r - 1;
							c2 = c;
							break;
							//East
							case 1: c2 = c+ 1;
							r2 = r;
							break;
							//South
							case 2: r2 = r + 1;
							c2 = c;
							break;
							//West
							case 3: c2 = c - 1;
							r2 = r;
							break;
						}

						cout <<"row: "<< r << " col: "<< c << " dir: " << dir << endl;
						cout << "row: " << r2 << " col: " << c2 << endl;

					}while(ds.find(r*nc+c) == ds.find(r2*nc+c2));

					ds.join(r*nc+c, r2*nc+c2);
        	i = i + 1;

					//remove wall between(r1, c1) and (r2, c2)
					switch (dir) {
						//North
						case 0: maze[r][c] &= ~WALL_UP;
						maze[r2][c2] &= ~WALL_DOWN;
						break;
						//East
						case 1: maze[r][c] &= ~WALL_RIGHT;
						maze[r2][c2] &= ~WALL_LEFT;
						break;
						//South
						case 2: maze[r][c] &= ~WALL_DOWN;
						maze[r2][c2] &= ~WALL_UP;
						break;
						//West
						case 3: maze[r][c] &= ~WALL_LEFT;
						maze[r2][c2] &= ~WALL_RIGHT;
						break;
					}
    	}
}

int main(){
    int n;

	uint8_t maze[50][50];

    cout<<"How many rows do you want?: ";
    cin>>nr;

    cout<<endl<<"How many cols do you want?: ";
    cin>>nc;
    cout<<endl;

    n = nr * nc;

//    maze = new uint8_t[nr][50];

    GenerateMaze(maze,nr, nc);
    FindPath(maze, nr, nc);
    printMaze(maze, nr, nc);

//	for (int i = 0; i < nc; i++)
	//	delete[] maze[i];
//	delete[] maze;

    return 0;
}
