/*
ID: arpon.r1
PROG: fence6
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

#define MAXS 100
#define INF 10000000
int nsegs, npts,
	seglen[MAXS],
	edgelist[MAXS * 2][9], adjlist[MAXS * 2][9],
	deg[MAXS * 2],
	mindist, begin;
	
bool visited[MAXS];

void DFS(int last, int point, int edge, int dist)
{
	if (dist >= mindist)
		return;
	if (edge != -1)
	{
		if (visited[edge])
			return;
		if (point == begin)
		{
			mindist = dist;
			return;
		}
	}
	visited[edge] = true;
	for (int i = 0; i < deg[point]; i++)
		DFS(point, adjlist[point][i], edgelist[point][i], dist + seglen[edgelist[point][i]]);
	visited[edge] = false;
}

int main()
{
	ofstream fout("fence6.out");
	ifstream fin("fence6.in");
	int i, j, k;
	fin >> nsegs;
	npts = nsegs * 2;
	for (i = 0; i < nsegs; i++)
	{
		int s, len, conn1, conn2;
		fin >> s >> len >> conn1 >> conn2;
		seglen[--s] = len;
		deg[2 * s] = conn1 + 1;
		deg[2 * s + 1] = conn2 + 1;
		edgelist[2 * s][0] = s;
		for (j = 1; j <= conn1; j++)
		{
			fin >> edgelist[2 * s][j];
			edgelist[2 * s][j]--;
		}
		edgelist[2 * s + 1][0] = s;
		for (j = 1; j <= conn2; j++)
		{
			fin >> edgelist[2 * s + 1][j];
			edgelist[2 * s + 1][j]--;
		}
	}
	for (i = 0; i < npts; i++)
	{
		if (i % 2 == 0)
			adjlist[i][0] = i + 1;
		else
			adjlist[i][0] = i - 1;
		for (j = 1; j < deg[i]; j++)
		{
			int orig = i / 2, find = edgelist[i][j] * 2;
			for (k = 0; k < deg[find] && edgelist[find][k] != orig; k++);
			if (k < deg[find])
				find++;
			adjlist[i][j] = find;
		}
	}
	int minperim = INF;
	for (i = 0; i < npts; i++)
	{
		memset(visited, false, nsegs * sizeof(int));
		mindist = INF; begin = i;
		DFS(i, i, -1, 0);
		if (mindist < minperim)
			minperim = mindist;
	}
	fout << minperim << endl;
}
			


