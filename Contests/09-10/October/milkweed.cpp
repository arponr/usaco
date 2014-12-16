/*
ID: arpon.r1
PROG: milkweed
LANG: C++
*/
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

FILE *fin = fopen ("milkweed.in", "r"), *fout = fopen ("milkweed.out", "w");

const int MAX = 105, INF = 1000000005;

int X, Y, MX, MY;
char map [MAX][MAX];
int taken [MAX][MAX];

int main ()
{
   fscanf (fin, "%d %d %d %d\n", &X, &Y, &MX, &MY);
   MX--; MY = Y - MY;

   for (int i = 0; i <= Y; i++)
      fgets (map [i], X + 2, fin);

   int left = 0;

   for (int i = 0; i < Y; i++)
      for (int j = 0; j < X; j++)
	 if (map [i][j] == '.')
	    left++;

   memset (taken, INF, sizeof (taken));

   int time = 0;

   taken [MY][MX] = time;
   map [MY][MX] = 'M';
   left--;

   while (left > 0)
   { 
      time++;

      for (int i = 0; i < Y; i++)
	 for (int j = 0; j < X; j++)
	    if (taken [i][j] == time - 1)
	       for (int dy = -1; dy <= 1; dy++)
		  for (int dx = -1; dx <= 1; dx++)
		     if (i + dy >= 0 && i + dy < Y && j + dx >= 0 && j + dx < X && map [i + dy][j + dx] == '.')
		     {
			map [i + dy][j + dx] = 'M';
			taken [i + dy][j + dx] = time;
			left--;
		     }
   }

   fprintf (fout, "%d\n", time);
}
			
      

