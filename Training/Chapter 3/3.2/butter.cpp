/*
  ID: arpon.r1
  PROG: butter
  LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

FILE *fin = fopen ("butter.in", "r"), *fout = fopen ("butter.out", "w");

const int MAXP = 805, MAXC = 2 * 1455, INF = 1000000005;

struct state
{
   int num, dist;
   
   inline bool operator < (const state &o) const
   {
      return dist > o.dist;
   }
};

int N, P, C, cows [MAXP], dist [MAXP];
int eadj [MAXC], elen [MAXC], enext [MAXC], elast [MAXP];
priority_queue <state> pq;

void addedge (int e, int a, int b, int len)
{
   eadj [e] = b; elen [e] = len; enext [e] = elast [a]; elast [a] = e;
}

int dijkstra (int start)
{
   memset (dist, INF, sizeof(dist));
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
   
   int total = 0;
   
   for (int i = 0; i < P; i++)
      total += dist [i] * cows [i];
   
   return total;
}

int main ()
{
   memset (elast, -1, sizeof (elast));
   fscanf (fin, "%d %d %d", &N, &P, &C);
   
   for (int i = 0, p; i < N; i++)
   {
      fscanf (fin, "%d", &p); p--;
      cows [p]++;
   }
   
   for (int i = 0, e = 0, a, b, len; i < C; i++)
   {
      fscanf (fin, "%d %d %d", &a, &b, &len); a--; b--;
      addedge (e++, a, b, len);
      addedge (e++, b, a, len);
   }
   
   int best = INF;
   
   for (int i = 0, cur; i < P; i++)
      if ((cur = dijkstra (i)) < best)
	 best = cur;
   
   fprintf (fout, "%d\n", best);
}

