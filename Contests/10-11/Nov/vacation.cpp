/*
ID: arpon.r1
PROG: vacation
LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

FILE *in = fopen ("vacation.in", "r"), *out = fopen ("vacation.out", "w");

const int MAXN = 50005, INF = 1000000005;

int N, eadj [2 * MAXN], eprev [2 * MAXN], elast [MAXN], depth [MAXN], D_max, num [MAXN], q [MAXN], front, back, S_max;
bool used [MAXN];

inline void add_edge (int e, int a, int b)
{
   eadj [e] = b; eprev [e] = elast [a]; elast [a] = e;
}

void dfs (int S, int D)
{
   if (D > D_max)
   {
      S_max = max (S_max, S);
      return;
   }

   if (used [D - 1])
      dfs (S, D + 1);
   else
   {
      used [D] = true;
      dfs (S + num [D], D + 1);

      used [D] = false;
      dfs (S, D + 1);
   }
}

int main ()
{
   memset (elast, -1, sizeof (elast));
   
   fscanf (in, "%d", &N);

   for (int i = 0, e = 0, a, b; i < N - 1; i++)
   {
      fscanf (in, "%d %d", &a, &b); a--; b--;
      add_edge (e++, a, b);
      add_edge (e++, b, a);
   }

   memset (depth, INF, sizeof (depth));

   front = back = depth [0] = 0;
   q [back++] = 0;

   while (front < back)
   {
      int top = q [front++];

      for (int i = elast [top]; i != -1; i = eprev [i])
	 if (depth [top] + 1 < depth [eadj [i]])
	 {
	    depth [eadj [i]] = depth [top] + 1;
	    q [back++] = eadj [i];
	 }
   }

   for (int i = 0; i < N; i++)
   {
      num [depth [i]]++;
      D_max = max (D_max, depth [i]); 
   }

   dfs (0, 0);

   fprintf (out, "%d\n", S_max);

   return 0;
}
