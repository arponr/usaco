/*
ID: arpon.r1
PROG: stroll
LANG: C++
*/

#include <cstdio>
using namespace std;

FILE *fin = fopen ("stroll.in", "r"), *fout = fopen ("stroll.out", "w");

const int MAXP = 1005;

int P, left [MAXP], right [MAXP], ans = 0;

void traverse (int loc, int dist)
{
   if (loc == 0)
   {
      if (dist > ans) ans = dist;
      return;
   }

   traverse (left [loc], dist + 1);
   traverse (right [loc], dist + 1);
}

int main ()
{
   fscanf (fin, "%d", &P);

   for (int i = 0, p, l, r; i < P - 1; i++)
   {
      fscanf (fin, "%d %d %d", &p, &l, &r);
      left [p] = l; right [p] = r;
   }

   traverse (1, 0);

   fprintf (fout, "%d\n", ans);
}
