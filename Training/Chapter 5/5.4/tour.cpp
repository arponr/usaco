/*
ID: arpon.r1
PROG: tour
LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

FILE *fin = fopen ("tour.in", "r"), *fout = fopen ("tour.out", "w");

const int MAXN = 105, MAXLEN = 20;

int N, V, dp [MAXN][MAXN];
bool adj [MAXN][MAXN];
char city [MAXN][MAXLEN];

int find (char c [])
{
   for (int i = 0; i < N; i++)
      if (strcmp (c, city [i]) == 0)
	 return i;
   
   return -1;
}

int main ()
{
   fscanf (fin, "%d %d", &N, &V);
   
   for (int i = 0; i < N; i++)
      fscanf (fin, "%s", city [i]);
   
   for (int i = 0; i < V; i++)
   {
      char s [MAXLEN], e [MAXLEN];
      fscanf (fin, "%s %s", s, e);
      int a = find (s), b = find (e);
      adj [a][b] = adj [b][a] = true;
   }
   
   dp [0][0] = 1;
   
   for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
	 if (dp [i][j] > 0)
	    for (int k = min (max (i, j) + 1, N - 1); k < N; k++)
	    {
	       if (adj [i][k] && dp [i][j] + 1 > dp [k][j])
		  dp [k][j] = dp [j][k] = dp [i][j] + 1;
	       if (adj [j][k] && dp [i][j] + 1 > dp [i][k])
		  dp [i][k] = dp [k][i] = dp [i][j] + 1;
	    }

   fprintf (fout, "%d\n", (dp [N - 1][N - 1] - 1) > 1 ? dp [N - 1][N - 1] - 1 : 1);

   return 0;
}


