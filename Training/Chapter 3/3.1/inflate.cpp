/*
 ID: arpon.r1
 PROG: inflate
 LANG: C++
 */

#include <iostream>
#include <fstream>

using namespace std;

#define MAXM 10000

int main()
{
	ofstream fout("inflate.out");
	ifstream fin("inflate.in");
	int m, n, i, j, s, t;
	fin >> m >> n;
	int dyn[m + 1];
	dyn[0] = 1;
	for (i = 1; i <= m; i++)
		dyn[i] = 0;
	for (i = 0; i < n; i++)
	{
		fin >> s >> t;
		for (j = 0; j + t <= m; j++)
			if (dyn[j] && s + dyn[j] > dyn[j + t])
				dyn[j + t] = s + dyn[j];
	}
	int best = 0;
	for (i = 0; i <= m; i++)
		if (dyn[i] > best)
			best = dyn[i];
	fout << best - 1 << endl;
}