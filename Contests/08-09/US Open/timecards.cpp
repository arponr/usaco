/*
ID: arpon.r1
PROB: timecards
LANG: C++
*/

using namespace std;
#include <cstdio>
#include <cstring>
#include <algorithm>

FILE *fin = fopen ("timecards.in", "r"), *fout = fopen ("timecards.out", "w");

const int MAXN = 145, MAXL = 1458, HRMIN = 60;

int N, L, total [MAXN],  start [MAXN];

int main ()
{
	fscanf (fin, "%d %d", &N, &L);
	
	for (int i = 0; i < L; i++)
	{
		int c, h, m, temp;
		char key [6];
		fscanf (fin, "%d %s %d %d", &c, key, &h, &m); c--;
		temp = h * HRMIN + m;
		if (key [2] == 'A')
			start [c] = temp;
		else
			total [c] += temp - start [c];
	}
	
	for (int i = 0; i < N; i++)
		fprintf (fout, "%d %d\n", total [i] / HRMIN, total [i] % HRMIN);
	
	return 0;
}