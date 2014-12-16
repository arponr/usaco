/*
 ID: arpon.r1
 PROG: kimbits
 LANG: C++
 */

#include <iostream>
#include <fstream>

using namespace std;

int N, L, f[32][32];
double I;

int main()
{
	FILE *fin = fopen("kimbits.in", "r"), *fout = fopen("kimbits.out", "w");
	int i, j, list_pos;
	fscanf(fin, "%d %d %lf", &N, &L, &I);
	for (i = 0; i <= 31; i++)
	{
		f[0][i] = 1;
		f[i][0] = 1;
	}
	for (i = 1; i <= 31; i++)
		for (j = 1; j <= 31; j++)
			f[i][j] = f[i-1][j-1] + f[i-1][j];
	i = L; list_pos = (long long)(I - 1);
	for (j = N; j > 0; j--)
	{
		if (list_pos >= f[j-1][i])
		{
			list_pos -= f[j-1][i];
			i--;
			fprintf(fout, "1");
		}
		else
			fprintf(fout, "0");
	}
	fprintf(fout, "\n");
}