/*
ID: arpon.r1
PROG: papaya
LANG: C++
*/

#include <cstdio>
#include <algorithm>
using namespace std;

FILE *fin = fopen ("papaya.in", "r"), *fout = fopen ("papaya.out", "w");

const int MAXRC = 45, dir = 4, dr [] = {-1, 0, 0, 1}, dc [] = {0, -1, 1, 0};

int R, C, map [MAXRC][MAXRC];

int main ()
{
   fscanf (fin, "%d %d", &R, &C);

   for (int i = 0; i < R; i++)
      for (int j = 0; j < C; j++)
	 fscanf (fin, "%d", &map [i][j]);

   int r = 0, c = 0, ans = map [0][0];
   map [0][0] = 0;

   while (r != R - 1 || c != C - 1)
   {
      int nr, nc, best = 0;

      for (int i = 0; i < dir; i++)
	 if (r + dr [i] >= 0 && r + dr [i] < R && c + dc [i] >= 0 && c + dc [i] < C && map [r + dr [i]][c + dc [i]] > best)
	 {
	    nr = r + dr [i];
	    nc = c + dc [i];
	    best = map [r + dr [i]][c + dc [i]];
	 }

      ans += best;
      map [nr][nc] = 0;
      r = nr; c = nc;
   }

   fprintf (fout, "%d\n", ans);
}
	       
