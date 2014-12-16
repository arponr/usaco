/*
ID: arpon.r1
PROG: feed
LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

FILE *in = fopen ("feed.in", "r"), *out = fopen ("feed.out", "w");

const int MAXN = 505, MAXE = 505;

int K, E, N;

struct store
{
   int X, F, C, take;
} stores [MAXN];

bool cmp1 (store a, store b)
{
   return (E - a.X) * a.F * a.F + a.F * a.C < (E - b.X) * b.F * b.F + b.F * b.C;
}

bool cmp2 (store a, store b)
{
   return a.X < b.X;
}

int main ()
{
   fscanf (in, "%d %d %d", &K, &E, &N);

   for (int i = 0; i < N; i++)
   {
      fscanf (in, "%d %d %d", &stores [i].X, &stores [i].F, &stores [i].C);
      stores [i].take = 0;
   }

   sort (stores, stores + N, cmp1);

   for (int i = 0, k = 0; k < K; i++)
   {
      stores [i].take = k + stores [i].F > K ? K - k : stores [i].F;
      k += stores [i].take;
   }
   
   sort (stores, stores + N, cmp2);

   int feed = 0, cost = 0;
   for (int i = 0; i < N; i++)
   {
      feed += stores [i].take;
      cost += stores [i].take * stores [i].C + feed * feed;
   }

   fprintf (out, "%d\n", cost);

   return 0;
}
