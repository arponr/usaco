/*
ID: arpon.r1
PROG: telecow
LANG: C++
*/

#include <cstdio>
#include <algorithm>
using namespace std;

FILE *fin = fopen ("telecow.in", "r"), *fout = fopen ("telecow.out", "w");

const int MAXN = 105, MAXM = 605, MAXV = 2 * MAXN, INF = 1000000005;

int N, M, V, c1, c2;
bool adj [MAXN][MAXN], cut [MAXN];
int src, sink, cap [MAXV][MAXV], prev [MAXV], flow [MAXV]; 
bool vis [MAXV];

inline int min (int a, int b)
{
   return (a < b) ? a : b;
}

int augment ()
{
   memset (flow, 0, sizeof (flow));
   memset (vis, false, sizeof (vis));
   memset (prev, -1, sizeof (prev));
   
   flow [src] = INF;
   
   int best, loc;
   
   while (true)
   {
      best = 0; 
      loc = -1;
      
      for (int i = 0; i < V; i++)
	 if (flow [i] > best && !vis [i])
	 {
	    best = flow [i];
	    loc = i;
	 }
      
      if (loc == -1 || loc == sink) break;
      
      vis [loc] = true;
      
      for (int i = 0; i < V; i++)
	 if (flow [i] < min (cap [loc][i], best))
	 {
	    flow [i] = min (cap [loc][i], best);
	    prev [i] = loc;
	 }
   }
   
   if (loc == -1 || best == 0) return -1;
   
   for (int i = sink; i != src; i = prev [i])
   {
      cap [prev [i]][i] -= best;
      cap [i][prev [i]] += best;
   }
   
   return best;
}

int maxflow ()
{
   int total = 0, aug;
   
   memset (cap, 0, sizeof (cap));
   
   for (int i = 0; i < N; i++)
   {
      if (!cut [i])
	 cap [2 * i][2 * i + 1] = 1;
      
      for (int j = 0; j < N; j++)
	 if (adj [i][j])
	    cap [2 * i + 1][2 * j] = INF;
   }
   
   while ((aug = augment ()) > 0)
      total += aug;
   
   return total;
}

int main ()
{
   fscanf (fin, "%d %d %d %d", &N, &M, &c1, &c2); c1--; c2--;
   V = 2 * N; src = 2 * c1 + 1; sink = 2 * c2;
   
   for (int i = 0, a, b; i < M; i++)
   {
      fscanf (fin, "%d %d", &a, &b); a--; b--;
      adj [a][b] = adj [b][a] = true;
   }
   
   int ans = maxflow ();
   int copy = ans;
   
   for (int i = 0, temp; i < N && copy > 0; i++)
      if (i != c1 && i != c2)
      {
	 cut [i] = true;
	 
	 if ((temp = maxflow ()) < copy)
	    copy = temp;
	 else
	    cut [i] = false;
      }
   
   fprintf (fout, "%d\n", ans);
   
   bool first = true;
   for (int i = 0; i < N; i++)
      if (cut [i])
      {
	 if (first)
	 {
	    fprintf (fout, "%d", i + 1);
	    first = false;
	 }
	 else
	    fprintf (fout, " %d", i + 1);
      }
   fprintf (fout, "\n");
   
   return 0;
}
