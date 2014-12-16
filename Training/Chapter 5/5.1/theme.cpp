/*
ID: arpon.r1
PROG: theme
LANG: C++
*/

#include <cstdio>

FILE *fin = fopen ("theme.in", "r"), *fout = fopen ("theme.out", "w");

const int MAXN = 5005, MINLEN = 5;

int N, notes [MAXN];

int main ()
{
	fscanf (fin, "%d", &N);
	
	for (int i = 0; i < N; i++)
		fscanf (fin, "%d", notes + i);
	
	int longest = 0;
	
	for (int i = 1; i < N; i++)
	{
		int len = 1;
		for (int j = N - i - 2; j >= 0; j--)
			if (notes [j + 1] - notes [j] == notes [j + i + 1] - notes [j + i])
			{
				len++;
				if (len > i) len = i;
				if (len > longest) longest = len;
			}
			else
				len = 1;
	}
	
	longest = (longest >= MINLEN) ? longest : 0;
	
	fprintf (fout, "%d\n", longest);
	return 0;
}
			
			


