/*
ID: arpon.r1
PROG: bigbrn
LANG: C++
*/
#include <cstdio>
#include <algorithm>
using namespace std;

FILE *fin = fopen ("bigbrn.in", "r"), *fout = fopen ("bigbrn.out", "w");

const int MAXN = 1005;

bool grid [MAXN][MAXN];
int N, T, r [MAXN][MAXN], d [MAXN][MAXN], dp [MAXN][MAXN];

int min_3 (int a, int b, int c)
{
   return (a > b) ? ((b > c) ? c : b) : ((a > c) ? c : a);
}

int main ()
{
   fscanf (fin, "%d %d", &N, &T);
   
   for (int i = 0, row, col; i < T; i++)
   {
      fscanf (fin, "%d %d", &row, &col); row--; col--;
      grid [row][col] = true;
   }
   
   int best = 0;
   
   for (int i = N - 1; i >= 0; i--)
      for (int j = N - 1; j >= 0; j--)
	 if (!grid [i][j])
	 {
	    r [i][j] = r [i][j + 1] + 1;
	    d [i][j] = d [i + 1][j] + 1;
	    dp [i][j] = min_3 (r [i][j], d [i][j], dp [i + 1][j + 1] + 1);
	    
	    if (dp [i][j] > best)
	       best = dp [i][j];
	 }
   
   fprintf (fout, "%d\n", best);
   return 0;
}
