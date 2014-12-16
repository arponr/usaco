/*
ID: arpon.r1
PROG: lights
LANG: C++
*/

#include <cstdio>
#include <algorithm>
using namespace std;

FILE *fin = fopen ("lights.in", "r"), *fout = fopen ("lights.out", "w");

const int MAXN = 35;

int N, M, P, Q, best = MAXN;
long long toggle [MAXN];
pair <long long, int> first [1 << MAXN / 2];

int main ()
{
   fscanf (fin, "%d %d", &N, &M);
   P = N / 2; Q = N - P;

   for (int i = 0; i < N; i++)
      toggle [i] = 1LL << i;

   for (int i = 0, a, b; i < M; i++)
   {
      fscanf (fin, "%d %d", &a, &b); a--; b--;
      toggle [a] |= 1LL << b; toggle [b] |= 1LL << a;
   }

   for (int i = 0; i < 1 << P; i++)
   {
      first [i] = make_pair (0LL, 0);
      
      for (int j = 0; j < P; j++)
	 if (i & 1 << j)
	 {
	    first [i].first ^= toggle [j];
	    first [i].second++;
	 }
   }

   sort (first, first + (1 << P));

   for (int i = 0; i < 1 << Q; i++)
   {
      long long mask = 0LL;
      int switches = 0;
      
      for (int j = 0; j < Q; j++)
	 if (i & 1 << j)
	 {
	    mask ^= toggle [j + P];
	    switches++;
	 }

      int loc = lower_bound (first, first + (1 << P), make_pair (mask ^ ((1LL << N) - 1), 0)) - first;
      if ((first [loc].first ^ mask) == (1LL << N) - 1)
	 best = min (best, first [loc].second + switches);
   }

   fprintf (fout, "%d\n", best);
   return 0;
}
