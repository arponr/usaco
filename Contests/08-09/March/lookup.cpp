/*
ID: arpon.r1
PROG: lookup
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

#define MAXN 100000

int n, h[MAXN], l[MAXN];

int main()
{
	FILE *fin = fopen("lookup.in", "r"), *fout = fopen("lookup.out", "w");
	int i, j;
	fscanf(fin, "%d", &n);
	for (i = 0; i < n; i++)
		fscanf(fin, "%d", &h[i]);
	for (i = 0; i < n; i++)
	{
		if (i > 0 && h[i] >= h[i-1])
			j = l[i-1];
		else
			j = i + 1;
		for (; j < n; j++)
			if (h[j] > h[i])
			{
				l[i] = j;
				fprintf(fout, "%d\n", j + 1);
				break;
			}
		if (j == n)
		{
			l[i] = n;
			fprintf(fout, "%d\n", 0);
		}
	}
}
