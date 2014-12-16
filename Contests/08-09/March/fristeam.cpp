/*
 ID: arpon.r1
 PROG: fristeam
 LANG: C++
*/

#include <cstdio>
using namespace std;

FILE *fin = fopen ("fristeam.in", "r"), *fout = fopen ("fristeam.out", "w");

const int MAXN = 2005, MAXF = 1005, MOD = 100000000;

int N, F, cow [MAXN], dp [MAXN][MAXF];

int main ()
{
   fscanf (fin, "%d %d", &N, &F);

   for (int i = 0; i < N; i++)
      fscanf (fin, "%d", cow + i);

   dp [0][0] = 1;

   for (int i = 0; i < N; i++)
      for (int j = 0; j < F; j++)
      {
	 dp [i + 1][j] = (dp [i + 1][j] + dp [i][j]) % MOD; 
	 dp [i + 1][(j + cow [i]) % F] = (dp [i + 1][(j + cow [i]) % F] + dp [i][j]) % MOD;
      }

   fprintf (fout, "%d\n", dp [N][0] - 1);
}
