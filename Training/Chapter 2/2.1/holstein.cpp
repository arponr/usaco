/*
 ID: arpon.r1
 PROG: holstein
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
int v, g, sol[15], vitReq[25], feeds[15][25], minCount, moveset[25], vals[25];

void search(int moveCount, int type)
{
	if (moveCount == minCount)
		return;
	int k;
	for (k = 0; k < v; k++)
		if (vals[k] < vitReq[k])
			break;
	if (k == v)
	{
		minCount = moveCount;
		for (int x = 0; x < minCount; x++)
			sol[x] = moveset[x];
		return; 
	}
	for (int i = type; i < g; i++)
	{
		for (int j = 0; j < v; j++)
			vals[j] += feeds[i][j];
		moveset[moveCount] = i + 1;
		search(moveCount + 1, i + 1);
		for (int j = 0; j < v; j++)
			vals[j] -= feeds[i][j];
	}
}

int main()
{
	ofstream fout("holstein.out");
	ifstream fin("holstein.in");
	fin >> v;
	for (int i = 0; i < v; i++)
		fin >> vitReq[i];
	fin >> g;
	minCount = g + 1;
	for (int a = 0; a < g; a++)
		for (int b = 0; b < v; b++)
			fin >> feeds[a][b];
	for (int s = 0; s < v; s++)
		vals[s] = 0;
	search(0, 0);
	fout << minCount;
	for (int x = 0; x < minCount; x++)
		fout << " " << sol[x];
	fout << endl;
	return 0;
}
