/*
 ID: arpon.r1
 PROG: ratios
 LANG: C++
 

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

typedef struct state state;
struct state
{
	int vals[3], factor, num_each[3];
};

int goal[3], feeds[3][3];
bool visited[101][101][101];
ofstream fout("ratios.out");

int gcd(int a, int b)
{
	if (b == 0)
		return a;
	else
		return gcd(b, a % b);
}

void bfs()
{
	queue<state> q;
	state a;
	for (int i = 0; i < 3; i++)
		a.vals[i] = a.num_each[i] = 0;
	a.factor = 1;
	q.push(a);
	while(!q.empty())
	{
		state c = q.front();
		q.pop();
		if (!visited[c.num_each[0]][c.num_each[1]][c.num_each[2]])
		{
			visited[c.num_each[0]][c.num_each[1]][c.num_each[2]] = true;
			int i, j;
			for (i = 0; i < 3; i++)
				if (c.vals[i] != goal[i] * c.factor)
					break;
			if (i == 3)
			{
				for (i = 0; i < 3; i++)
					fout << c.num_each[i] << " ";
				fout << c.factor << endl;
				return;
			}
			for (i = 0; i < 3; i++)
			{
				state n;
				for (j = 0; j < 3; j++)
				{
					if (j == i)
						n.num_each[j] = c.num_each[j] + 1;
					else
						n.num_each[j] = c.num_each[j];
					n.vals[j] = c.vals[j] + feeds[i][j];
				}
				if (c.vals[0] == 0 || c.vals[1] == 0 || c.vals[2] == 0)
					n.factor = 1;
				else
					n.factor = gcd(gcd(c.vals[0], c.vals[1]), c.vals[2]);
				if (c.num_each[0] <= 100 && c.num_each[1] <= 100 && c.num_each[2] <= 100)
					q.push(n);
			}
		}
	}
}

SOLVED IN SCHOOL

int main()
{
	ifstream fin("ratios.in");
	int i, j, k;
	for (i = 0; i < 3; i++)
		fin >> goal[i];
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			fin >> feeds[i][j];
	int best[3] = {101, 101, 101}, factor = 1;
	for (i = 0; i <= 100; i++)
	{
		for (j = 0; j <= 100; j++)
		{
			for (k = 0; k <= 100; k++)
			{
				int cur[3];
				for (int e = 0; e < 3; e++)
					cur[e] = i * feeds[0][e] + j * feeds[1][e] + k * feeds[2][e];
				int divisor = gcd(gcd(cur[0], cur[1]), cur[2]);
				int g;
				for (g = 0; g < 3; g++)
					if (cur[g] != goal[g] * divisor)
						break;
				if (g == 3 && cur[0] + cur[1] + cur[2] < best[0] + best[1] + best[2])
	bfs();
}*/
	


