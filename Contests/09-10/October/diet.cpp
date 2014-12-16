/*
ID: arpon.r1
PROG: diet
LANG: C++
*/

#include <cstdio>
using namespace std;

FILE *fin = fopen ("diet.in", "r"), *fout = fopen ("diet.out", "w");

const int MAXN = 505, MAXH = 45005;

int N, H;
bool eat [MAXH];

int main ()
{
   fscanf (fin, "%d %d", &H, &N);

   eat [0] = true;

   for (int i = 0; i < N; i++)
   {
      int W;
      fscanf (fin, "%d", &W);

      for (int j = H; j >= W; j--)
	 eat [j] |= eat [j - W];
   }

   int ans;
   for (ans = H; !eat [ans]; ans--)
      ;

   fprintf (fout, "%d\n", ans);
}
