/*
 ID: arpon.r1
 PROG: bones
 LANG: C++
 */
#include <cstdio>
using namespace std;

FILE *fin = fopen ("bones.in", "r"), *fout = fopen ("bones.out", "w");

const int MAXN = 40;

int S1, S2, S3, count [3 * MAXN];

int main ()
{
	fscanf (fin, "%d %d %d", &S1, &S2, &S3);
	
	for (int i = 1; i <= S1; i++)
		for (int j = 1; j <= S2; j++)
			for (int k = 1; k <= S3; k++)
				count [i + j + k]++;

	int best = 0;
	
	for (int i = 3; i <= S1 + S2 + S3; i++)
		if (count [i] > count [best])
			best = i;
	
	fprintf (fout, "%d\n", best);
	return 0;
}
