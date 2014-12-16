/*
ID: arpon.r1
PROG: gather
LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

struct state
{
   int num, dist;
   
   inline bool operator < (const state &o) const
   {
      return dist > o.dist;
   }
};

FILE *in = fopen ("gather.in", "r"), *out = fopen ("gather.out", "w");

const int MAXN = 100005, INF = 1000000005;

int N, cows [MAXN], dist [MAXN], best = INF;
int eadj [2 * MAXN], elen [2 * MAXN], enext [2 * MAXN], elast [MAXN];
priority_queue <state> pq;

void addedge (int e, int a, int b, int len)
{
   eadj [e] = b; elen [e] = len; enext [e] = elast [a]; elast [a] = e;
}

int dijkstra (int start)
{
   memset (dist, INF, sizeof (dist));
   dist [start] = 0; pq.push ((state) {start, 0});
   
   while (!pq.empty ())
   {
      state top = pq.top (); pq.pop (); 
      
      if (top.dist > dist [top.num])
	 continue;
      
      for (int i = elast [top.num]; i != -1; i = enext [i])
	 if (top.dist + elen [i] < dist [eadj [i]])
	    pq.push ((state) {eadj [i], dist [eadj [i]] = top.dist + elen [i]});
   }
}

int main ()
{
   memset (elast, -1, sizeof (elast));
   
   fscanf (in, "%d", &N);

   for (int i = 0; i < N; i++)
      fscanf (in, "%d", cows + i);

   for (int i = 0, a, b, len; i < N - 1; i++)
   {
      fscanf (in, "%d %d %d", &a, &b, &len); a--; b--;
      addedge (2 * i, a, b, len);
      addedge (2 * i + 1, b, a, len);
   }

   for (int i = 0; i < N; i++)
   {
      dijkstra (i);

      int now = 0;
      for (int j = 0; j < N; j++)
	 now += dist [j] * cows [j];

      if (now < best)
	 best = now;
   }

   fprintf (out, "%d\n", best);

   return 0;
}
