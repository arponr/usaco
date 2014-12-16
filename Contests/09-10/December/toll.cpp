/*
  ID: arpon.r1
  PROG: toll
  LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

FILE *fin = fopen ("toll.in", "r"), *fout = fopen ("toll.out", "w");

const int MAXV = 255, MAXE = 10005, INF = 100000005;

int N, M, K, cost [MAXV], dist [MAXV][MAXV], toll [MAXV][MAXV], order [MAXV];

int cmp (
int main ()
{
   memset (dist, INF, sizeof (dist));
   memset (toll, INF, sizeof (toll));

   fscanf (fin, "%d %d %d", &N, &M, &K);

   for (int i = 0; i < N; i++)
   {
      fscanf (fin, "%d", cost + i);
      toll [i][i] = cost [i];
      dist [i][i] = 0;
   }

   for (int i = 0, a, b, len; i < M; i++)
   {
      fscanf (fin, "%d %d %d", &a, &b, &len); a--; b--;
      toll [a][b] = toll [b][a] = max (cost [a], cost [b]);
      dist [a][b] = dist [b][a] = min (dist [a][b], len); 
   }

   for (int k = 0; k < N; k++)
      for (int i = 0; i < N; i++)
	 for (int j = 0; j < N; j++)
	    if (dist [i][k] + dist [k][j] + max (toll [i][k], toll [k][j]) < dist [i][j] + toll [i][j])
	    {
	       toll [i][j] = toll [j][i] = max (toll [i][k], toll [k][j]);
	       dist [i][j] = dist [j][i] = dist [i][k] + dist [k][j];
	    }
 
   for (int i = 0, s, t; i < K; i++)
   {
      fscanf (fin, "%d %d", &s, &t); s--; t--;
      fprintf (fout, "%d\n", dist [s][t] + toll [s][t]);
   }

   return 0;
}
