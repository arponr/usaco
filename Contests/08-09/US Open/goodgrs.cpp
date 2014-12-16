/*
 ID: arpon.r1
 PROB: goodgrs
 LANG: C++
*/

using namespace std;
#include <cstdio>
#include <cstring>
#include <algorithm>

FILE *fin = fopen ("goodgrs.in", "r"), *fout = fopen ("goodgrs.out", "w");

const int MAXRC = 105;

int R, C, P [MAXRC][MAXRC];

int sq_sum (int r, int c)
{
	int sum = 0;
	
	for (int i = r; i < r + 3; i++)
		for (int j = c; j < c + 3; j++)
			sum += P [i][j];
	
	return sum;
}

int main ()
{
	fscanf (fin, "%d %d", &R, &C);
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			fscanf (fin, "%d", &P [i][j]);
	
	int br, bc, best = 0, temp;
	
	for (int i = 0; i < R - 2; i++)
		for (int j = 0; j < C - 2; j++)
			if ((temp = sq_sum (i, j)) > best)
			{
				best = temp;
				br = i; bc = j;
			}
	
	fprintf (fout, "%d\n%d %d\n", best, br + 1, bc + 1);
	return 0;
}
