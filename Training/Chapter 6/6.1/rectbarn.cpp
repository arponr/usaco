/*
ID: arpon.r1
PROG: rectbarn
LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

FILE *in = fopen ("rectbarn.in", "r"), *out = fopen ("rectbarn.out", "w");

const int MAXR = 3005, MAXC = 3005, INF = 1000000005;

int R, C, P, area = 0, down [MAXC], right [MAXC], tmp_right [MAXC], left [MAXC], tmp_left [MAXC];
bool bad [MAXR][MAXC];

int main ()
{
   fscanf (in, "%d %d %d", &R, &C, &P);
   
   if (P == 0)
   {
      fprintf (out, "%d\n", R * C);
      return 0;
   }

   for (int i = 0, r, c; i < P; i++)
   {
      fscanf (in, "%d %d", &r, &c); r--; c--;
      bad [r][c] = true;
   }

   memset (right, INF, sizeof (right));
   memset (left,  INF, sizeof (left));
   for (int r = 0; r < R; r++)
   {
      tmp_left [0] = bad [r][0] ? -1 : 0;
      for (int c = 1; c < C; c++)
	 tmp_left [c] = bad [r][c] ? -1 : (tmp_left [c - 1] + 1);

      tmp_right [C - 1] = bad [r][C - 1] ? -1 : 0;
      for (int c = C - 2; c >= 0; c--)
	 tmp_right [c] = bad [r][c] ? -1 : (tmp_right [c + 1] + 1);

      for (int c = 0; c < C; c++)
      {
	 if (bad [r][c])
	 {
	    down  [c] = 0;
	    right [c] = INF;
	    left  [c] = INF;
	 }
	 else
	 {
	    down  [c]++;
	    right [c] = min (right [c], tmp_right [c]);
	    left  [c] = min (left  [c], tmp_left  [c]);
	 }
	 
	 area = max (area, down [c] * (right [c] + left [c] + 1));
	 //printf ("(%d,%d):%d,%d,%d\n", r+1, c+1, down [c], right [c], left [c]);
      }
   }
   //printf ("%d %\n", down [2]);
/*
  1 2 3 4
 +-+-+-+-+
1| | |X| |
 +-+-+-+-+
2|X|#|#|#|
 +-+-+-+-+
3| |#|#|#|
 +-+-+-+-+
*/
   fprintf (out, "%d\n", area);
	    
   return 0;
}
