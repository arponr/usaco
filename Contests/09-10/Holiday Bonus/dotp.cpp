/*
ID: arpon.r1
PROG: dotp
LANG: C++
*/

#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

FILE *in = fopen ("dotp.in", "r"), *out = fopen ("dotp.out", "w");

const int MAXN = 305;

int N, M, P, Q, adj [MAXN][MAXN], deg [MAXN];
bool vis [MAXN];
double R, city [MAXN];

inline double infsum (double a, double r)
{
   return a * (1 / (1 - r));
}

void dfs (int at, double prob, int len)
{
   printf ("%d|%lf|%d|%lf\n", at, prob, len, infsum (prob, pow (R, len)));
   
   if (vis [at])
   {
      city [at] += infsum (prob, pow (R, len));
      len = 0;
   }
   else
   {
      city [at] += prob;
      vis [at] = true;
      for (int i = 0; i < deg [at]; i++)
	 dfs (adj [at][i], prob * R, len + 1);
      vis [at] = false;
   }
}

int main ()
{
   fscanf (in, "%d %d %d %d", &N, &M, &P, &Q); 
   R = (double) P / (double) Q;

   for (int i = 0, a, b; i < M; i++)
   {
      fscanf (in, "%d %d", &a, &b); a--; b--;
      adj [a][deg [a]++] = b;
      adj [b][deg [b]++] = a;
   }

   dfs (0, R, 0);

   for (int i = 0; i < N; i++)
      fprintf (out, "%.9lf\n", city [i]);

   return 0;
}
