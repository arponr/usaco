/*
ID: arpon.r1
PROG: heatwv
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

FILE *fin = fopen ("heatwv.in", "r"), *fout = fopen ("heatwv.out", "w");

const int MAXT = 2505, MAXC = 6205, INF = 1000000005;

int T, C, start, end, dist [MAXT];
int eadj [2 * MAXC], elen [2 * MAXC], enext [2 * MAXC], elast [MAXT];
priority_queue <state> pq;

void addedge (int e, int a, int b, int len)
{
   eadj [e] = b; elen [e] = len; enext [e] = elast [a]; elast [a] = e;
}

int dijkstra ()
{
   memset (dist, 63, sizeof (dist));
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
   
   return dist [end];
}

int main ()
{
   memset (elast, -1, sizeof (elast));
   
   fscanf (fin, "%d %d %d %d", &T, &C, &start, &end);
   start--; end--;

   for (int i = 0, e = 0, a, b, len; i < C; i++)
   {
      fscanf (fin, "%d %d %d", &a, &b, &len); a--; b--;
      addedge (e++, a, b, len);
      addedge (e++, b, a, len);
   }

   fprintf (fout, "%d\n", dijkstra ());
}
