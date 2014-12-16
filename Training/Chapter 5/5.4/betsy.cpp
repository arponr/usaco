/*
  ID: arpon.r1
  PROG: betsy
  LANG: C++
*/

#include <cstdio>
using namespace std;

FILE *fin = fopen ("betsy.in", "r"), *fout = fopen ("betsy.out", "w");

const int MAXN = 10, dir = 4, dr [dir] = {-1, 0, 1, 0}, dc [dir] = {0, 1, 0, -1};

int N, destr, destc, ntours = 0,
    around [MAXN][MAXN], row [MAXN], col [MAXN];
bool vis [MAXN][MAXN];

void search (int r, int c, int nvis)
{
   if (r == destr && c == destc)
   {
      if (nvis == N * N)
	 ntours++;
      return;
   }

   bool wall  = row [r + 1] == N || col [c - 1] == N,
        block = (r == 1 && !vis [r][c - 1]) || (r == N && !vis [r][c + 1]) || (c == 1 && !vis [r - 1][c]) || (c == N && !vis [r - 1][c]);
   if (!wall && !block)
   {
      int bad = 0;
      for (int i = 0; i < dir; i++)
	 if (++around [r + dr [i]][c + dc [i]] > 2 && !vis [r + dr [i]][c + dc [i]])
	    bad++;

      if (bad <= 1)
      {
	 vis [r][c] = true;
	 row [r]++; col [c]++;

	 if (bad == 0)
	 {
	    for (int i = 0; i < dir; i++)
	       if (!vis [r + dr [i]][c + dc [i]])
		  search (r + dr [i], c + dc [i], nvis + 1);
	 }
	 else
	 {
	    for (int i = 0; i < dir; i++)
	       if (around [r + dr [i]][c + dc [i]] > 2 && !vis [r + dr [i]][c + dc [i]])
	       {
		  search (r + dr [i], c + dc [i], nvis + 1);
		  break;
	       }
	 }

	 vis [r][c] = false;
	 row [r]--; col [c]--;
      }

      for (int i = 0; i < dir; i++)
	 around [r + dr [i]][c + dc [i]]--;
   }
}

int main ()
{
   fscanf (fin, "%d", &N);
   destc = 1; destr = N;
   for (int i = 0; i <= N + 1; i++)
   {
      vis [0][i]    = vis [N + 1][i]    = vis [i][0]    = vis [i][N + 1]    = true;
      around [0][i] = around [N + 1][i] = around [i][0] = around [i][N + 1] = -10;
      around [1][i] = around [N][i]     = around [i][1] = around [i][N]     = 1;
   }
   search (1, 1, 1);
   fprintf (fout, "%d\n", ntours);
}
