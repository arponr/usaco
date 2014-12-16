/*
ID: arpon.r1
PROG: guardian
LANG: C++
*/

#include <cstdio>
#include <cstring>
using namespace std;

FILE *fin = fopen ("guardian.in", "r"), *fout = fopen ("guardian.out", "w");
const int MAX = 705;
int R, C, map [MAX][MAX];
bool visit [MAX][MAX];

inline bool valid (int r, int c)
{
   return (r >= 0 && r < R && c >= 0 && c < C);
}

bool flood (int r, int c)
{
   visit [r][c] = true;

   bool flag = true;

   for (int nr = r - 1; nr <= r + 1; nr++)
      for (int nc = c - 1; nc <= c + 1; nc++)
	 if (valid (nr, nc))
	    if (map [nr][nc] > map [r][c])
	       flag = false;
	    else if (!visit [nr][nc] && map [nr][nc] == map [r][c])
	       flag &= flood (nr, nc);

   return flag;
}

int main ()
{
   fscanf (fin, "%d %d", &R, &C);
   for (int i = 0; i < R; i++)
      for (int j = 0; j < C; j++)
	 fscanf (fin, "%d", map [i] + j);

   int ans = 0;

   for (int r = 0; r < R; r++)
      for (int c = 0; c < C; c++)
	 if (!visit [r][c] && flood (r, c))
	    ans++;

   fprintf (fout, "%d\n", ans);
}
	   
