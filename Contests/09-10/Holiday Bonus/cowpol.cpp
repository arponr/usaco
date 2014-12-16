/*
ID: arpon.r1
PROG: cowpol
LANG: C++
*/

#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

FILE *in = fopen ("cowpol.in", "r"), *out = fopen ("cowpol.out", "w");

const int MAXN = 200005, MAXK = 100005;

int N, K, party [MAXN], parent [MAXN], depth [MAXN], range [MAXK];

inline int dist (int a, int b)
{
   if (depth [a] > depth [b]) 
      swap (a, b);
   
   int t = b;
   while (depth [t] > depth [a])
      t = parent [t];
   
   return depth [b] - depth [a] + 2 * (a != t);   
}

inline int height (int i)
{
   int h = 0;
   while (parent [i] != 0)
      h++, i = parent [i];
   return h;
}

int main ()
{
   fscanf (in, "%d %d", &N, &K);

   for (int i = 1; i <= N; i++)
      fscanf (in, "%d %d", party + i, parent + i);

   for (int i = 1; i <= N; i++)
      depth [i] = height (i);

   for (int i = 1; i <= N; i++)
      for (int j = i + 1; j <= N; j++)
	 if (party [i] == party [j])
	    range [party [i]] = max (range [party [i]], dist (i, j));

   for (int i = 1; i <= K; i++)
      fprintf (out, "%d\n", range [i]);

   return 0;
}
			 


   
