/*
ID: arpon.r1
PROG: ice
LANG: C++
*/

#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

FILE *in = fopen ("ice.in", "r"), *out = fopen ("ice.out", "w");

struct rock
{
   int ind;
   pair <int, int> loc;

   inline bool operator < (const rock &other) const
   {
      return (loc < other.loc);
   }
};

const int MAXN = 20005, DIR = 4, RIGHT = 0, LEFT = 1, UP = 2, DOWN = 3, dx [] = {1, -1, 0, 0}, dy [] = {0, 0, 1, -1};

int N, B, G, BX, BY, GX, GY;
rock xrock [MAXN], yrock [MAXN];
int q [MAXN * DIR], front, back, adj [MAXN * DIR][DIR], dist [MAXN * DIR];

void bfs ()
{
   memset (dist, 63, sizeof (dist));
   dist [B] = 0;

   front = back = 0;
   q [back++] = B;
   
   while (front < back)
   {
      int top = q [front++];

      if (top == G)
	 return;

      for (int i = 0; i < DIR; i++)
	 if (adj [top][i] != -1 && dist [top] + 1 < dist [adj [top][i]])
	 {
	    dist [adj [top][i]] = dist [top] + 1;
	    q [back++] = adj [top][i];
	 }
   }
}

int main ()
{
   fscanf (in, "%d %d %d %d %d", &N, &BX, &BY, &GX, &GY);
  
   for (int i = 0; i < N; i++)
   {
      xrock [i].ind = yrock [i].ind = i;

      fscanf (in, "%d %d", &xrock [i].loc.first, &xrock [i].loc.second);
      yrock [i].loc = make_pair (xrock [i].loc.second, xrock [i].loc.first);
   }

   sort (xrock, xrock + N);
   sort (yrock, yrock + N);

   memset (adj, -1, sizeof (adj));

   for (int i = 0, ind, x, y; i < N; i++)
      for (int j = 0; j < DIR; j++)
      {
	 ind = xrock [i].ind * DIR + j;
	 x = xrock [i].loc.first + dx [j];
	 y = xrock [i].loc.second + dy [j];

	 if (x == BX && y == BY)
	    B = ind;
	 else if (x == GX && y == GY)
	    G = ind;

	 rock search; search.loc = make_pair (x, y);
	 int up = upper_bound (xrock, xrock + N, search) - xrock, down = lower_bound (xrock, xrock + N, search) - xrock - 1;

	 if (up >= 0 && up < N && xrock [up].loc.first == x) 
	    adj [ind][UP] = xrock [up].ind * DIR + DOWN;
	 
	 if (down >= 0 && down < N && xrock [down].loc.first == x) 
	    adj [ind][DOWN] = xrock [down].ind * DIR + UP;
      }

   for (int i = 0, ind, x, y; i < N; i++)
      for (int j = 0; j < DIR; j++)
      {
	 ind = yrock [i].ind * DIR + j;
	 x = yrock [i].loc.second + dx [j];
	 y = yrock [i].loc.first + dy [j];

	 rock search; search.loc = make_pair (y, x);
	 int right = upper_bound (yrock, yrock + N, search) - yrock, left = lower_bound (yrock, yrock + N, search) - yrock - 1;

	 if (right >= 0 && right < N && xrock [right].loc.first == y) 
	    adj [ind][RIGHT] = xrock [right].ind * DIR + LEFT;
	 
	 if (left >= 0 && left < N && xrock [left].loc.first == y) 
	    adj [ind][LEFT] = xrock [left].ind * DIR + RIGHT;
      }
   
   for (int i = 0; i < N * DIR; i++)
   {
      printf ("%d:\n", i);
      for (int j = 0; j < DIR; j++)
	 printf ("\t%d\n", adj [i][j]);
   }

   bfs ();

   fprintf (out, "%d\n", dist [G]);

   return 0;
}
