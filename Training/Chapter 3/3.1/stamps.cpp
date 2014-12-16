/*
 ID: arpon.r1
 PROG: stamps
 LANG: C++
 */

#include <iostream>
#include <fstream>

using namespace std;

#define INF 1000000

int main()
{
	FILE *fin = fopen("stamps.in", "r"), *fout = fopen("stamps.out", "w");
	int K, N, i, j;
	fscanf(fin, "%d %d", &K, &N);
	int vals[N], maxval = 0;
	for (i = 0; i < N; i++)
	{
		fscanf(fin, "%d", &vals[i]);
		if (vals[i] > maxval)
			maxval = vals[i];
	}
	int dyn[maxval * K + 1];
	dyn[0] = 0;
	for (i = 1; i <= maxval * K; i++)
		dyn[i] = INF;
	for (i = 0; i < N; i++)
		for (j = vals[i]; j <= maxval * K; j++)
			if (dyn[j - vals[i]] < INF && dyn[j] > dyn[j - vals[i]] + 1)
				dyn[j] = dyn[j - vals[i]] + 1;
	for (i = 1; dyn[i] <= K && i <= maxval * K; i++)
		;
	fprintf(fout, "%d\n", i - 1);
}