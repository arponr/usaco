/*
 ID: arpon.r1
 PROB: tcave
 LANG: C++
*/

using namespace std;
#include <cstdio>
#include <cstring>
#include <algorithm>

FILE *fin = fopen ("tcave.in", "r"), *fout = fopen ("tcave.out", "w");

const int MAXP = 5005;

int P, S, T, path [MAXP], l [MAXP], r [MAXP];

void leave (int dist)
{
	fprintf (fout, "%d\n", dist);
	
	for (int i = 0; i < dist; i++)
		fprintf (fout, "%d\n", path [i] + 1);
	
	exit (0);
}

void dfs (int p, int dist)
{
	if (p == -1) return;
	
	path [dist] = p;
	
	if (p == T) 
		leave (dist + 1);
	
	dfs (l [p], dist + 1);
	dfs (r [p], dist + 1);
}

int main ()
{
	memset (path, -1, sizeof (path));
	memset (l, -1, sizeof (l));
	memset (r, -1, sizeof (r));
	
	fscanf (fin, "%d %d %d", &P, &S, &T);
	T--;
	
	for (int i = 0; i < S; i++)
	{
		int a, b, c; fscanf (fin, "%d %d %d", &a, &b, &c);
		a--; b--; c--;
		l [a] = b; r [a] = c;
	}
	
	path [0] = 0;
	dfs (0, 0);
}