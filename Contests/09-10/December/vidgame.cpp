/*
  ID: arpon.r1
  PROG: vidgame
  LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

FILE *fin = fopen ("vidgame.in", "r"), *fout = fopen ("vidgame.out", "w");

const int MAXV = 100005, INF = 1000000005;

int N, V, P, G, dp1 [MAXV], dp2 [MAXV];

int main ()
{
   fscanf (fin, "%d %d", &N, &V);
   
   for (int i = 0; i < N; i++)
   {
      fscanf (fin, "%d %d", &P, &G);

      for (int j = 0; j + P <= V; j++)
	 dp1 [j + P] = dp2 [j];

      for (int j = 0; j < P; j++)
	 dp1 [j] = -INF;

      for (int j = 0, cost, value; j < G; j++)
      {
	 fscanf (fin, "%d %d", &cost, &value);

	 for (int k = V; k >= cost; k--)
	    dp1 [k] = max (dp1 [k], dp1 [k - cost] + value);
      }

      for (int j = 0; j <= V; j++)
      {
	 dp2 [j] = max (dp2 [j], dp1 [j]);
	 if (j > 0) dp2 [j] = max (dp2 [j], dp2 [j - 1]);
      }
   } 

   fprintf (fout, "%d\n", dp2 [V]);
   return 0;
}
 
