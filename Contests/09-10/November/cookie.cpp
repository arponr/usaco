/*
ID: arpon.r1
PROG: cookie
LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

FILE *fin = fopen ("cookie.in", "r"), *fout = fopen ("cookie.out", "w");

const int MAXN = 1005, MAXM = 105, INF = 1000000005;
const double EPS = 1e-10;

int N, M, source, sink, cap [MAXN + MAXM][MAXN + MAXM], flow [MAXN + MAXM], prev [MAXN + MAXM], vis [MAXN + MAXM];
double cow [MAXN];

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
   fscanf (fin, "%d %d", &N, &M);
   source = 0; sink = N + M + 1;

   for (int i = N + 1, size, c; i <= N + M; i++)
   {
      cap [i][sink] = 1;

      fscanf (fin, "%d", &size);
      for (int j = 0; j < size; j++)
      {
	 fscanf (fin, "%d", &c);
	 cap [c][i] = 1;
	 cow [c] += 1.0 / size;
      }
   }

   for (int i = 1; i <= N; i++)
      cap [source][i] = (int) ceil (cow [i]);
   
   int total = 0, aug;
   while (total < M && (aug = augment ()) > 0)
      total += aug;
   
   if (total < M)
      fprintf (fout, "-1\n");
   else
      for (int i = N + 1; i <= N + M; i++)
	 for (int j = 1; j <= N; j++)
	    if (cap [i][j] > 0)
	    {
	       fprintf (fout, "%d\n", j);
	       break;
	    }

   return 0;
}
	       

	       
