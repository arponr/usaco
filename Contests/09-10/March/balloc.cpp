/*
ID: arpon.r1
PROG: balloc
LANG: C++
*/

#include <cstdio>
#include <vector>
using namespace std;

FILE *in = fopen ("balloc.in", "r"), *out = fopen ("balloc.out", "w");

const int MAXN = 100005;

int N, M, cap [MAXN], req [MAXN], bad [MAXN], now;
vector <pair <int, int> > cows;

inline bool check ()
{
   now = 0;

   for (int i = 0; i < N; i++)
      if (req [i] > cap [i])
	 bad [now++] = i;

   return (now == 0);
}

inline int count (int c)
{
   int fix = 0;

   for (int i = 0; i < now; i++)
      if (bad [i] >= cows [c].first && bad [i] <= cows [c].second)
	 fix++;

   return fix;
}

int main ()
{
   fscanf (in, "%d %d", &N, &M);

   for (int i = 0; i < N; i++)
      fscanf (in, "%d", cap + i);

   for (int i = 0, a, b; i < M; i++)
   {
      fscanf (in, "%d %d", &a, &b); a--; b--;
      cows.push_back (make_pair (a, b));

      for (int j = a; j <= b; j++)
	 req [j]++;
   }

   while (!check ())
   {
      int ind, most = 0;

      for (int i = 0, temp; i < (int) cows.size (); i++)
	 if ((temp = count (i)) > most)
	 {
	    ind = i;
	    most = temp;
	 }

      for (int i = cows [ind].first; i <= cows [ind].second; i++)
	 req [i]--;

      cows.erase (cows.begin () + ind);
   }

   fprintf (out, "%d\n", (int) cows.size ());

   return 0;
}

      
