/*
 ID: arpon.r1
 PROG: patheads
 LANG: C++
 */

#include <cstdio>

using namespace std;

FILE *fin = fopen ("patheads.in", "r"), *fout = fopen ("patheads.out", "w");

const int MAXN = 100005, MAXA = 1000005;

int N, A [MAXN], occur [MAXA], pats [MAXA], i, j;

int main()
{
	fscanf (fin, "%d", &N);
	for (i = 0; i < N; i++)
	{
		fscanf (fin, "%d", &A[i]);
		occur[A[i]]++;
	} 
	for (i = 1; i < MAXA; i++)
		if (occur[i] > 0)
			for (j = i; j < MAXA; j += i)
				pats[j] += occur[i];
	for (i = 0; i < N; i++)
		fprintf (fout, "%d\n", pats[A[i]] - 1);

}


