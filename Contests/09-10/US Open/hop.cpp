/*
ID: arpon.r1
LANG: C++
PROG: hop
*/

#include <cstdio>
#include <algorithm>
using namespace std;

FILE *in = fopen ("hop.in", "r"), *out = fopen ("hop.out", "w");

const int MAXN = 250005;

int N, K;
long long value [MAXN], cash;
bool vis [MAXN];

void dfs2 (int sq, long long total)
{
   if (sq == 0)
   {
      cash = max (cash, total);
      return;
   }

   for (int i = 1; i <= K && sq - i >= 0; i++)
      if (sq - i == 0 || !vis [sq - i] && vis [sq - i + 1])
	 dfs2 (sq - i, total + value [sq - i]);
}

void dfs1 (int sq, long long total)
{
   vis [sq] = true;

   if (sq == N)
   {
      dfs2 (N, total);
      return;
   }

   for (int i = 1; i <= K && sq + i <= N; i++)
      dfs1 (sq + i, total + value [sq + i]);
   
   vis [sq] = false;
}

int main ()
{
   fscanf (in, "%d %d", &N, &K);

   for (int i = 1; i <= N; i++)
      fscanf (in, "%lld", value + i);

   dfs1 (0, 0);

   fprintf (out, "%lld\n", cash);

   return 0;
}
