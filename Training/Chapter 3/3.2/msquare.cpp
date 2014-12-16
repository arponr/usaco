/*
 ID: arpon.r1
 PROG: msquare
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>

using namespace std;

typedef struct state state;
struct state
{
	int num, move_count;
	string moves;
};

bool visited[40320];
int goal, turns[3][8] = {{4, 5, 6, 7, 0, 1, 2, 3}, {3, 0, 1, 2, 7, 4, 5, 6}, {0, 5, 1, 3, 4, 6, 2, 7}}, perms[40320];
char map[3] = {'A', 'B', 'C'};
FILE *fin = fopen("msquare.in", "r");
ofstream fout("msquare.out");

inline int f(int in[])
{
	return 10000000 * in[0] + 1000000 * in[1] + 100000 * in[2] + 10000 * in[3] + 1000 * in[4] + 100 * in[5] + 10 * in[6] + in[7];
}

void gen_perms()
{
	int in[8] = {1, 2, 3, 4, 5, 6, 7, 8}, pl = 0;
	do
		perms[pl++] = f(in);
	while (next_permutation(in, in + 8));
}

int b_search(int key)
{
	int first = 0, last = 40319;
	while(1)
	{
		int middle = (first + last) / 2;
		if (key == perms[middle])
			return middle;
		if (key > perms[middle])
			first = middle + 1;
		else
			last = middle - 1;
	}
	return -1;
}

void bfs()
{
	queue<state> q;
	state initial;
	initial.num = 12348765;
	initial.move_count = 0;
	q.push(initial);
	while (!q.empty())
	{
		state c = q.front();
		q.pop();
		int index = b_search(c.num);
		if (!visited[index])
		{
			visited[index] = true;
			if (c.num == goal)
			{
				fout << c.move_count << endl;
				fout << c.moves << endl;
				return;
			}
			for (int i = 0; i < 3; i++)
			{
				state s;
				s.num = 0;
				for (int j = 0; j < 8; j++)
					s.num += pow(10, 7 - j) * ((int)(c.num / pow(10, 7 - turns[i][j])) % 10);
				s.moves = c.moves;
				s.moves += map[i];
				s.move_count = c.move_count + 1;
				q.push(s);
			}
		}
	}
}

int main()
{
	int final[8];
	fscanf(fin, "%d %d %d %d %d %d %d %d", &final[0], &final[1], &final[2], &final[3], &final[7], &final[6], &final[5], &final[4]);
	goal = f(final);
	gen_perms();
	bfs();
}
	

