/*
ID: arpon.r1
PROG: mtime
LANG: C++
*/

#include <cstdio>
#include <algorithm>
using namespace std;

struct job 
{
   int t, s;
   
   inline bool operator < (const job &o) const
   {
      return s > o.s;
   }
};

FILE *fin = fopen ("mtime.in", "r"), *fout = fopen ("mtime.out", "w");
const int MAXN = 1005;
int N;
job list [MAXN];


int solve ()
{
   int time = list [0].s;
   for (int i = 0; i < N; i++)
      time = min (time, list [i].s) - list [i].t;
   return (time < 0) ? -1 : time;
}

int main ()
{
   fscanf (fin, "%d", &N);

   for (int i = 0; i < N; i++)
      fscanf (fin, "%d %d", &list [i].t, &list [i].s);

   sort (list, list + N);

   fprintf (fout, "%d\n", solve ());
}
   
