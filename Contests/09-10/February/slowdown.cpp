/*
ID: arpon.r1
PROG: slowdown
LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

FILE *in = fopen ("slowdown.in", "r"), *out = fopen ("slowdown.out", "w");

const int MAXN = 100005;

int N, cow [MAXN], parent [MAXN], q [MAXN], front, back;
vector <int> adj [MAXN];
bool done [MAXN];

inline int deg (int ind)
{
   return (int) adj [ind].size ();
}

void bfs ()
{
   done [0] = true;

   front = back = 0;

   for (int i = 1; i < N; i++)
      if (deg (i) == 1)
      {
	 parent [i] = adj [i][0];
	 if (!done [parent [i]])
	 {
	    q [back++] = parent [i];
	    done [parent [i]] = true;
	 }
      }

   while (front < back)
   {
      int top = q [front++];

      for (int i = 0; i < deg (top); i++)
	 if (parent [adj [top][i]] == -1)
	 {
	    parent [top] = adj [top][i];
	    if (!done [parent [top]])
	    {
	       q [back++] = parent [top];
	       done [parent [top]] = true;
	    }
	    break;
	 }
   }
}

inline int slows (int ind)
{
   int s = 0;
   
   for (int i = parent [ind]; i != -1; i = parent [i])
      if (cow [i] != -1)
	 s++;

   return s;
}

int main ()
{
   memset (parent, -1, sizeof (parent));
   memset (cow, -1, sizeof (cow));

   fscanf (in, "%d", &N);

   for (int i = 0, a, b; i < N - 1; i++)
   {
      fscanf (in, "%d %d", &a, &b); a--; b--;
      adj [a].push_back (b);
      adj [b].push_back (a);
   }

   bfs ();

   for (int i = 0, p; i < N; i++)
   {
      fscanf (in, "%d", &p); p--;
      cow [p] = i;
      fprintf (out, "%d\n", slows (p));
   }

   return 0;
}


