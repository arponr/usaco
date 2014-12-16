/*
ID: arpon.r1
PROG: buyhay
LANG: C++
*/

#include <cstdio>
#include <cstring>
using namespace std;

FILE *fin = fopen ("buyhay.in", "r"), *fout = fopen ("buyhay.out", "w");
const int MAXH = 55005, INF = 1000000005;
int N, H, P, C,
    best [MAXH], ans = INF;

int main ()
{
   memset (best, INF, sizeof (best));
   best [0] = 0;

   fscanf (fin, "%d %d", &N, &H);

   for (int i = 0; i < N; i++)
   {
      fscanf (fin, "%d %d", &P, &C);

      for (int j = 0; j < H; j++)
	 if (best [j] + C < best [j + P])
	    best [j + P] = best [j] + C;
   }

   for (int i = H; i < MAXH; i++)
      if (best [i] < ans)
	 ans = best [i];

   fprintf (fout, "%d\n", ans);
}
