/*
ID: arpon.r1
PROG: rescue
LANG: C++
*/

#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

FILE *fin = fopen ("rescue.in", "r"), *fout = fopen ("rescue.out", "w");

const int INF = 1000000005;

int N, M;
pair <int, int> start;
pair <int, pair <int, int> > best = make_pair (INF, make_pair (INF, INF));

int dist (int r1, int c1, int r2, int c2)
{
   c1 += N - r1; c2 += N - r2;
   int dr = r2 - r1, dc1 = abs (c2 - c1), dc2 = (r2 > r1) * (dr - 1 + (r1 % 2 == c1 % 2));
   return dr + (dc1 > dc2) * (dc1 - dc2) + dc2;
}

int main ()
{
   fscanf (fin, "%d %d %d %d", &N, &M, &start.first, &start.second);

   for (int i = 0; i < M; i++)
   {
      pair <int, int> end;
      fscanf (fin, "%d %d", &end.first, &end.second);

      pair <int, int> high = min (start, end), low = max (start, end);
      best = min (best, make_pair (dist (high.first, high.second, low.first, low.second), end));
   }

   fprintf (fout, "%d %d\n%d\n", best.second.first, best.second.second, best.first + 1);
   return 0;
}
	 
