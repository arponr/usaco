/*
ID: arpon.r1
PROG: corral
LANG: C++
*/

#include <cstdio>
#include <algorithm>
using namespace std;

FILE *in = fopen ("corral.in", "r"), *out = fopen ("corral.out", "w");

const int MAXM = 100005, INF = 1000000005;

int C, M, start [MAXM], len [MAXM], ans = INF;

void dfs (int covers, int beg, int end, int last)
{
   if (end - beg + 1 >= C)
   {
      ans = min (ans, covers);
      return;
   }

   for (int i = last + 1; i < M; i++)
      dfs (covers + 1, min (beg, start [i]), max (end, start [i] + len [i]), i);
}

int main ()
{
   fscanf (in, "%d %d", &C, &M);

   for (int i = 0; i < M; i++)
      fscanf (in, "%d %d", start + i, len + i);

   dfs (0, INF, -INF, -1);

   fprintf (out, "%d\n", ans);

   return 0;
}
