/*
ID: arpon.r1
PROG: latin
LANG: C++
*/
#include <cstdio>
using namespace std;

FILE *fin = fopen ("latin.in", "r"), *fout = fopen ("latin.out", "w");

const int MAXN = 7;

int N, row [MAXN], col [MAXN], factorial [MAXN + 1];

int solve (int r, int c)
{
   int sol = 0;
   
   if (r == N - 1) 
      sol++;
   else
   {
      for (int i = 0, mem; i < N; i++)
	 if (!(row [r] & (1 << i)) && !(col [c] & (1 << i)))
	 {
	    if (r == 1 && i > c + 1)
	       sol += mem;
	    else
	    {
	       row [r] ^= (1 << i); col [c] ^= (1 << i);
	       sol += (mem = (c == N - 1) ? solve (r + 1, 1) : solve (r, c + 1));
	       row [r] ^= (1 << i); col [c] ^= (1 << i);
	    }
	 }
   }

   return sol;
}

int main ()
{
   fscanf (fin, "%d", &N);
   for (int i = 0; i < N; i++)
   {
      factorial [i] = (i == 0) ? 1 : factorial [i - 1] * i;
      row [i] |= (1 << i);
      col [i] |= (1 << i);
   }
   fprintf (fout, "%.0f\n", (double) solve (1, 1) * (double) factorial [N - 1]);
   return 0;
}
