/*
ID: arpon.r1
LANG: C++
PROG: tricount
*/

#include <cstdio>
using namespace std;

FILE *in = fopen ("tricount.in", "r"), *out = fopen ("tricount.out", "w");

const int MAXN = 100005, EPS = 1e-8;

int N, X [MAXN], Y [MAXN], ans;

inline bool check (int i, int j, int x, int y)
{
   return (((X [j] - X [i]) * (y - Y [i]) - (Y [j] - Y [i]) * (x - X [i])) * ((X [j] - X [i]) * (-Y [i]) - (Y [j] - Y [i]) * (-X [i])) > 0);
}

inline bool golden (int i, int j, int k)
{
   int xbar = (X [i] + X [j] + X [k]) / 3, ybar = (Y [i] + Y [j] + Y [k]) / 3;
   return (check (i, j, xbar, ybar) && check (i, k, xbar, ybar) && check (j, k, xbar, ybar));
}

int main ()
{
   fscanf (in, "%d", &N);

   for (int i = 0; i < N; i++)
      fscanf (in, "%d %d", X + i, Y + i);

   for (int i = 0; i < N; i++)
      for (int j = i + 1; j < N; j++)
	 for (int k = j + 1; k < N; k++)
	    if (golden (i, j, k))
	       ans++;

   fprintf (out, "%d\n", ans);

   return 0;
}
      
	
