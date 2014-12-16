/*
  ID: arpon.r1
  PROG: pwrfail
  LANG: C++
*/
#include <cstdio>
#include <cmath>
#include <queue>
using namespace std;

FILE *fin = fopen ("pwrfail.in", "r"), *fout = fopen ("pwrfail.out", "w");

const int MAXN = 1005, MAXW = 10005;
const double INF = 1000000005.0, EPS = .00000001;

struct state
{
   int num; double dist;
   
   inline bool operator < (const state &o) const
   {
      return dist > o.dist;
   }
};

int N, W;
double M, x [MAXN], y [MAXN], ptdist [MAXN][MAXN], dist [MAXN];
bool vis [MAXN];
priority_queue <state> pq;

void dijkstra ()
{
   for (int i = 1; i < N; i++)
      dist [i] = INF;
   
   pq.push ((state) {0, 0});
   
   while (!pq.empty ())
   {
      state top = pq.top (); pq.pop ();
      
      if (vis [top.num])
	 continue;
      
      vis [top.num] = true;
      
      for (int i = 0; i < N; i++)
	 if (!vis [i] && ptdist [top.num][i] <= M && top.dist + ptdist [top.num][i] < dist [i])
	    pq.push ((state) {i, dist [i] = top.dist + ptdist [top.num][i]});
   }
}

int main ()
{
   fscanf (fin, "%d %d %lf", &N, &W, &M);
   
   for (int i = 0; i < N; i++)
      fscanf (fin, "%lf %lf", x + i, y + i);
   
   for (int i = 0; i < N; i++)
      for (int j = i + 1; j < N; j++)
	 ptdist [i][j] = ptdist [j][i] = hypot (x [i] - x [j], y [i] - y [j]);
   
   for (int i = 0, a, b; i < W; i++)
   {
      fscanf (fin, "%d %d", &a, &b); a--; b--;
      ptdist [a][b] = ptdist [b][a] = 0;
   }
   
   dijkstra ();
   
   fprintf (fout, "%d\n", (vis [N - 1]) ? (int) (dist [N - 1] * 1000) : -1);
   return 0;
}
