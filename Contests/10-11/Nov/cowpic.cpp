/*
ID: arpon.r1
PROG: cowpic
LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

FILE *in = fopen ("cowpic.in", "r"), *out = fopen ("cowpic.out", "w");

const int MAXN = 100005, INF = 1000000005;

int N, list [MAXN];

int main ()
{
   fscanf (in, "%d", &N);

   for (int i = 0; i < N; i++)
   {
      fscanf (in, "%d", list + i);
      list [i]--;
   }

   int moves = 0;

   while (true)
   {
      bool flag = true;
      for (int i = 1; flag && i < N; i++)
	 if (list [i] != (list [i - 1] + 1) % N)
	    flag = false;
      if (flag) break;

      int diff = INF;

      for (int i = 1; i < N; i++)
	 if (list [i] < list [i - 1])
	    diff = min (diff, list [i - 1] - list [i]);

      for (int i = 1; i < N; i++)
	 if (list [i - 1] - list [i] == diff)
	 {
	    swap (list [i], list [i - 1]);
	    moves++;
	 }
   }

   fprintf (out, "%d\n", moves);

   return 0;
}
