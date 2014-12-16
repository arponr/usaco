/*
ID: arpon.r1
PROG: quad
LANG: C++
*/
#include <cstdio>
using namespace std;

FILE *fin = fopen ("quad.in", "r"), *fout = fopen ("quad.out", "w");

const int MAXN = 2505;

int N, dp [MAXN][5];

int main ()
{
	fscanf (fin, "%d", &N);
	
	dp [0][0] = 1;
	
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j < (N + 1) / 2; j++)
			for (int k = j; k <= N; k++)
				dp [k][i] += dp [k - j][i - 1];
	
	fprintf (fout, "%d\n", dp [N][4]);
	return 0;
}
