/*
ID: arpon.r1
PROG: allow
LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

FILE *fin = fopen ("allow.in", "r"), *fout = fopen ("allow.out", "w");

const int MAXN = 25;

struct coin
{
   int val, count;

   inline bool operator < (const coin &o) const
   {
      return val < o.val;
   }
} coins [MAXN];

int N, C;

inline int min (int a, int b)
{
   return ((a < b) ? a : b);
}

bool pay ()
{
   int cost = C;

   for (int i = N - 1; i >= 0; i--)
   {
      int n = min (cost / coins [i].val, coins [i].count);
      cost -= n * coins [i].val;
      coins [i].count -= n;
   }

   if (cost > 0)
      for (int i = 0; i < N; i++)
	 if (coins [i].count > 0 && coins [i].val >= cost)
	 {
	    cost = 0;
	    coins [i].count--;
	    break;
	 }

   return (cost <= 0);
}

int main ()
{
   fscanf (fin, "%d %d", &N, &C);

   for (int i = 0; i < N; i++)
      fscanf (fin, "%d %d", &coins [i].val, &coins [i].count);
   sort (coins, coins + N);

   int weeks = 0, add;

   while (pay ())
      weeks++;

   fprintf (fout, "%d\n", weeks);
}
