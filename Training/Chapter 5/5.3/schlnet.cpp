/*
ID: arpon.r1
PROG: schlnet
LANG: C++
*/
#include <cstdio>
#include <algorithm>
using namespace std;

FILE *fin = fopen ("schlnet.in", "r"), *fout = fopen ("schlnet.out", "w");

const int MAXN = 105;

int N, front, back, q [MAXN * MAXN];
bool A [MAXN], B [MAXN], vis [MAXN], adj [MAXN][MAXN];

int max (int a, int b)
{
	return (a > b) ? a : b;
}

void ff (int s)
{
	memset (vis, false, sizeof (vis));
	front = back = 0;
	
	q [back++] = s;
	
	while (front < back)
	{
		int top = q [front++];
		
		if (vis [top]) continue;
		
		vis [top] = true;
		A [top] = false;
		B [top] = true;
		
		for (int i = 0; i < N; i++)
			if (adj [top][i])
				q [back++] = i;
	}
	
	A [s] = true;
}

int tops ()
{	
	memset (A, false, sizeof (A));
	memset (B, false, sizeof (B));
	
	while (true)
	{
		int i;
		for (i = 0; i < N && B [i]; i++);
		
		if (i == N)
			break;
		
		ff (i);
	}
	
	int total = 0;
	
	for (int i = 0; i < N; i++)
		if (A [i]) total++;
	
	return total;
}

bool done ()
{
	for (int i = 0; i < N; i++)
	{
		ff (i);
		
		for (int j = 0; j < N; j++)
			if (!vis [j]) return false;
	}
	
	return true;
}

void revgraph ()
{
	for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
		{
            bool temp = adj [i][j];
            adj [i][j] = adj [j][i];
            adj [j][i] = temp;
        }
}

int main ()
{
	fscanf (fin, "%d", &N);
	
	for (int i = 0, j; i < N; i++)
		for (fscanf (fin, "%d", &j); j != 0; fscanf (fin, "%d", &j))
			adj [i][--j] = true;
		
	int a, b;
	
	if (done ())
	{
		a = 1;
		b = 0;
	}
	else
	{
		a = tops ();
		revgraph();
		b = max (tops (), a);
	}
	
	fprintf (fout, "%d\n%d\n", a, b);
	return 0;
}



