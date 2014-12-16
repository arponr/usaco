/*
ID: arpon.r1
PROG: bestspot
LANG: C++
*/

using namespace std;

#include <iostream>
#include <fstream>
#define MAXP 500
#define INF 100000000

int P, F, C, f[MAXP], d[MAXP][MAXP];

int main()
{
	ofstream fout("bestspot.out");
	ifstream fin("bestspot.in");
	int i, j, k, a, b, t;
	fin >> P >> F >> C;
	for (i = 0; i < F; i++)
	{
		fin >> f[i];
		f[i]--;
	}
	for (i = 0; i < P; i++)
		for (j = 0; j < P; j++)
			d[i][j] = (i == j) ? 0 : INF;
	for (i = 0; i < C; i++)
	{
		fin >> a >> b >> t;
		a--; b--;
		d[a][b] = d[b][a] = t;
	}
	for (i = 0; i < P; i++)
		for (j = 0; j < P; j++)
			for (k = 0; k < P; k++)
				if (d[i][j] + d[i][k] < d[j][k])
					d[j][k] = d[i][j] + d[i][k];
	int best = INF, best_i = -1;
	for (i = 0; i < P; i++)
	{
		int temp = 0;
		for (j = 0; j < F; j++)
			temp += d[i][f[j]];
		if (temp < best)
		{
			best = temp;
			best_i = i + 1;
		}
	}
	fout << best_i << endl;
}
		
