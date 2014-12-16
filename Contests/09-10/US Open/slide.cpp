/*
ID: arpon.r1
LANG: C++
PROG: slide
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

FILE *in = fopen ("slide.in", "r"), *out = fopen ("slide.out", "w");

const int MAXV = 50005, MAXE = 150005;
const long long INF = 2000000005;

int V, E, K, eadj [MAXE], enext [MAXE], elast [MAXV];
long long efun [MAXE];

inline void addedge (int e, int a, int b, int fun)
{
   eadj [e] = b; efun [e] = fun; enext [e] = elast [a]; elast [a] = e;
}

long long dfs (int v, int k)
{
   if (v == V - 1)
      return 0;

   if (v == 0 || k >= K)
   {
      long long best = efun [elast [v]] + dfs (eadj [elast [v]], k);
      
      for (int i = enext [elast [v]]; i != -1; i = enext [i])
	 best = max (best, efun [i] + dfs (eadj [i], k));

      return best;
   }
   else
   {
      long long worst = min (efun [elast [v]] + dfs (eadj [elast [v]], k), efun [elast [v]] + dfs (eadj [elast [v]], k + 1));
      
      for (int i = enext [elast [v]]; i != -1; i = enext [i])
	 worst = min (worst, min (efun [i] + dfs (eadj [i], k), efun [i] + dfs (eadj [i], k + 1)));
    
      return worst;
   }
}

int main ()
{
   memset (elast, -1, sizeof (elast));

   fscanf (in, "%d %d %d", &V, &E, &K);

   for (int i = 0, p, q, f; i < E; i++)
   {
      fscanf (in, "%d %d %d", &p, &q, &f); p--; q--;
      addedge (i, p, q, f);
   }

   fprintf (out, "%lld\n", dfs (0, 0));

   return 0;
}
