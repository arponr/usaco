/*
  ID: arpon.r1
  PROG: dizzy 
  LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

FILE *fin = fopen ("dizzy.in", "r"), *fout = fopen ("dizzy.out", "w");

const int MAXN = 100005, MAXM = 100005;

int N, M1, M2, eadj [MAXM], eprev [MAXM], elast [MAXN], deg [MAXN], order [MAXN], q [MAXN], front = 0, back = 0;

int main ()
{
   memset (elast, -1, sizeof (elast));
   fscanf (fin, "%d %d %d", &N, &M1, &M2);

   for (int e = 0, a, b; e < M1; e++)
   {
      fscanf (fin, "%d %d", &a, &b); a--; b--;
      eadj [e] = b; eprev [e] = elast [a]; elast [a] = e;
      deg [b]++;
   }

   for (int i = 0; i < N; i++)
      if (deg [i] == 0)
	 q [back++] = i;

   while (front < back)
   {
      int top = q [front];
      order [top] = front++;

      for (int i = elast [top]; i != -1; i = eprev [i])
	 if (--deg [eadj [i]] == 0)
	    q [back++] = eadj [i];
   }

   if (front != N)
      fprintf (fout, "-1\n");
   else
      for (int i = 0, a, b; i < M2; i++)
      {
	 fscanf (fin, "%d %d", &a, &b); a--; b--;
	 if (order [a] > order [b]) swap (a, b);
	 fprintf (fout, "%d %d\n", a + 1, b + 1);
      }

   return 0;
}
	    
   
