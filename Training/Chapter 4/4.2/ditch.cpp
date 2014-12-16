/*
  ID: arpon.r1
  PROG: ditch
  LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

FILE *in = fopen ("ditch.in", "r"), *out = fopen ("ditch.out", "w");

const int MAXV = 205, MAXE = MAXV * MAXV, INF = 1000000005;

int N, M, source, sink, cap [MAXV][MAXV], flow [MAXV], vis [MAXV], prev [MAXV];

int augment ()
{
   memset (flow, 0, sizeof (flow));
   memset (vis, false, sizeof (vis));
   memset (prev, -1, sizeof (prev));
   
   flow [source] = INF;

   while (true)
   {
      int at = -1;
      
      for (int i = source; i <= sink; i++)
	 if (!vis [i] && ((at == -1) ? (flow [i] > 0) : (flow [i] > flow [at])))
	    at = i;

      if (at == -1)   return -1;
      if (at == sink) break;
      
      vis [at] = true;

      for (int i = source; i <= sink; i++)
	 if (flow [i] < min (cap [at][i], flow [at]))
	 {
	    flow [i] = min (cap [at][i], flow [at]);
	    prev [i] = at;
	 }
   }
   
   for (int i = sink; i != source; i = prev [i])
   {
      cap [prev [i]][i] -= flow [sink];
      cap [i][prev [i]] += flow [sink];
   }

   return flow [sink];
}

int main ()
{
   fscanf (in, "%d %d", &N, &M);
   source = 0; sink = M - 1;

   for (int i = 0, a, b, c; i < N; i++)
   {
      fscanf (in, "%d %d %d", &a, &b, &c); a--; b--;
      cap [a][b] += c;
   }

   int total = 0, aug;
   while ((aug = augment ()) > 0)
      total += aug;

   fprintf (out, "%d\n", total);
   return 0;
}
