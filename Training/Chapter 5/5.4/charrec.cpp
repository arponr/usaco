/*
  ID: arpon.r1
  PROG: charrec
  LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

FILE *in = fopen ("charrec.in", "r"), *out = fopen ("charrec.out", "w"), *font = fopen ("font.in", "r");

const int MAXM = 1205, LEN = 20, LET = 30, INF = 1000000005;
const char alpha [LET] = " abcdefghijklmnopqrstuvwxyz";

int N, M, ideal [LET][LEN], input [MAXM], mem [LET][LEN][MAXM], dp [MAXM], last [MAXM], ans [MAXM];

void init ()
{
   fscanf (font, "%d", &N);
   N /= LEN; 

   for (int i = 0; i < N; i++)
      for (int j = 0; j < LEN; j++)
      {
	 char line [LEN + 5];
	 fscanf (font, "%s", line);
	 for (int k = 0; k < LEN; k++)
	    if (line [k] == '1')
	       ideal [i][j] |= 1 << LEN - k - 1;
      }

   fscanf (in, "%d", &M); 

   for (int i = 0; i < M; i++)
   {
      char line [LEN + 5];
      fscanf (in, "%s", line);
      for (int j = 0; j < LEN; j++)
	 if (line [j] == '1')
	    input [i] |= 1 << LEN - j - 1;
   }
}

inline int corrupt (int i, int j, int k)
{
   if (mem [i][j][k] == -1)
      mem [i][j][k] = __builtin_popcount (ideal [i][j] ^ input [k]);
   return mem [i][j][k];
}

void solve ()
{
   memset (mem, -1, sizeof (mem));
   memset (last, -1, sizeof (last));
   memset (ans, -1, sizeof (ans));
   memset (dp, INF, sizeof (dp)); 
   dp [0] = 0;

   for (int i = 0; i <= M; i++)
      if (dp [i] < INF)
	 for (int j = 0; j < N; j++)
	 {
	    if (i <= M - LEN + 1)
	    {
	       int cur = 0;

	       for (int k = 0; k < 19; k++)
		  cur += corrupt (j, k + 1, i + k);

	       if (dp [i] + cur < dp [i + LEN - 1])
	       {
		  dp [i + LEN - 1] = dp [i] + cur;
		  last [i + LEN - 1] = i;
		  ans [i + LEN - 1] = j;
	       }

	       for (int k = 1; k < 20; k++)
	       {
		  cur += corrupt (j, k - 1, i + k - 1) - corrupt (j, k, i + k - 1);
		  if (dp [i] + cur < dp [i + LEN - 1])
		  {
		     dp [i + LEN - 1] = dp [i] + cur;
		     last [i + LEN - 1] = i;
		     ans [i + LEN - 1] = j;
		  }
	       }
	    }
	    
	    if (i <= M - LEN)
	    {
	       int cur = 0;
	       
	       for (int k = 0; k < 19; k++)
		  cur += corrupt (j, k, i + k);
	       
	       if (dp [i] + cur < dp [i + LEN])
	       {
		  dp [i + LEN] = dp [i] + cur;
		  last [i + LEN] = i;
		  ans [i + LEN] = j;
	       }
	    }

	    if (i <= M - LEN - 1)
	    {
	       int cur = 0;

	       for (int k = 0; k < 20; k++)
		  cur += corrupt (j, k, i + k + 1);

	       if (dp [i] + cur < dp [i + LEN + 1])
	       {
		  dp [i + LEN + 1] = dp [i] + cur;
		  last [i + LEN + 1] = i;
		  ans [i + LEN + 1] = j;
	       }

	       for (int k = 1; k < 21; k++)
	       {
		  cur += corrupt (j, k - 1, i + k - 1) - corrupt (j, k - 1, i + k);
		  if (dp [i] + cur < dp [i + LEN + 1])
		  {
		     dp [i + LEN + 1] = dp [i] + cur;
		     last [i + LEN + 1] = i;
		     ans [i + LEN + 1] = j;
		  }
	       }
	    }
	 }
}

void write (int i)
{
   if (last [i] != -1)
   {
      write (last [i]);
      fprintf (out, "%c", alpha [ans [i]]);
   }
}
int main ()
{
   init ();
   solve ();
   write (M);
   fprintf (out, "\n");
   return 0;
}
   
   
