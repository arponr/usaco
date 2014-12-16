/*
 ID: arpon.r1
 PROG: maze1
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

#define INF 100000000
#define MAXW 38
#define MAXH 100

typedef struct pt pt;
struct pt
{
	int x, y;
};

typedef struct state state;
struct state
{
	pt p;
	int dist;
};

char maze[MAXH * 2 + 1][MAXW * 2 + 1];
int w, h, dists[MAXH * 2 + 1][MAXW * 2 + 1], nexits = 0;
pt exits[2];
int moves[4][2] = {{-1,0}, {1,0}, {0, -1}, {0, 1}};
int moves2[4][2] = {{-2,0}, {2,0}, {0, -2}, {0, 2}};

pt construct(int x, int y)
{
	pt p;
	p.x = x;
	p.y = y;
	return p;
}

void BFS(pt p)
{
	int read = 0, write = 1;
	state q[MAXH * MAXW], top;
	q[0].p = p;
	q[0].dist = dists[p.x][p.y] = 1;
	while (read < write)
	{
		top = q[read++];
		for (int i = 0; i < 4; i++)
		{
			int newx = top.p.x + moves[i][0], newy = top.p.y + moves[i][1];
			int newx2 = top.p.x + moves2[i][0], newy2 = top.p.y + moves2[i][1];
			if (maze[newx][newy] ==  ' ' && newx2 < 2 * h + 1 && newx2 >= 0 && newy2 < 2 * w + 1 && newy2 >= 0 && top.dist + 1 < dists[newx2][newy2])
			{
				q[write].p.x = newx2;
				q[write].p.y = newy2;
				q[write++].dist = dists[newx2][newy2] = top.dist + 1;
			}
		}
		
	}
}

int main()
{
	ofstream fout("maze1.out");
	ifstream fin("maze1.in");
	int i, j;
	fin >> w >> h; fin.get();
	for (i = 0; i <= 2 * h; i++)
		fin.getline(maze[i], 2 * w + 2);
	for (j = 1; j < 2 * w; j += 2)
	{
		if (maze[0][j] == ' ')
		{
			exits[nexits].x = 0;
			exits[nexits].y = j;
			nexits++;
		}
		if (nexits == 2) break;
		if (maze[2 * h][j] == ' ')
		{
			exits[nexits].x = 2 * h;
			exits[nexits].y = j;
			nexits++;
		}
		if (nexits == 2) break;
	}
	for (j = 1; j < 2 * h; j += 2)
	{
		if (nexits == 2) break;
		if (maze[j][0] == ' ')
		{
			exits[nexits].x = j;
			exits[nexits].y = 0;
			nexits++;
		}
		if (nexits == 2) break;
		if (maze[j][2 * w] == ' ')
		{
			exits[nexits].x = j;
			exits[nexits].y = 2 * w;
			nexits++;
		}
		if (nexits == 2) break;
	}
	for (i = 0; i <= 2 * h; i++)
		for (j = 0; j <= 2 * w; j++)
			 dists[i][j] = INF;
	for (i = 0; i < 2; i++)
	{
		if (exits[i].x == 0)
			BFS(construct(exits[i].x + 1, exits[i].y));
		if (exits[i].x == 2 * h)
			BFS(construct(exits[i].x - 1, exits[i].y));
		if (exits[i].y == 0)
			BFS(construct(exits[i].x, exits[i].y + 1));
		if (exits[i].y == 2 * w)
			BFS(construct(exits[i].x, exits[i].y - 1));
	}
	int m = 0;
	for (i = 1; i < 2 * h; i += 2)
		for (j = 1; j < 2 * w; j += 2)
			if (dists[i][j] > m)
				m = dists[i][j];
	fout << m << endl;
}
			