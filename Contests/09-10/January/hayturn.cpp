/*
  ID: arpon.r1
  LANG: C++
  PROG: hayturn
*/

#include <cstdio>
using namespace std;

FILE *in = fopen ("hayturn.in", "r"), *out = fopen ("hayturn.out", "w");

const int MAXN = 700005;

int N, weight [MAXN];

int main ()
{
   fscanf (in, "%d", &N);

   for (int i = 0; i < N; i++)
      fscanf (in, "%d", weight + i);

   long long first = 0, second = 0;
   
   for (int i = N - 1; i >= 0; i--)
   {
      long long nfirst = weight [i] + second, nsecond = first;
      
      if (nfirst >= first)
      {
	 first = nfirst;
	 second = nsecond;
      }
   }
   
   fprintf (out, "%lld %lld\n", first, second);

   return 0;
}
