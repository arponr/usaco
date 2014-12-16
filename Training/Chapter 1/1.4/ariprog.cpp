/*
ID: arpon.r1
PROG: ariprog
LANG: C++
*/

#include <cstdio>
#include <algorithm>
using namespace std;

FILE *fin = fopen ("ariprog.in", "r"), *fout = fopen ("ariprog.out", "w");

const int MAXM = 255;

bool bisquare [2 * MAXM * MAXM];
int N, M, list [MAXM * MAXM], size = 0, ans = 0;

void init ()
{
   for (int i = 0; i <= M; i++)
      for (int j = i; j <= M; j++)
	 if (!bisquare [i * i + j * j])
	 {
	    list [size++] = i * i + j * j;
	    bisquare [i * i + j * j] = true;
	 }

   sort (list, list + size);
}

bool prog (int a, int b)
{
   for (int i = 1; i < N; i++)
      if (!bisquare [a + i * b])
	 return false;
   return true;
}

int main ()
{
   fscanf (fin, "%d %d", &N, &M);
   init ();

   bool hay = false;
   for (int b = 1; b < 2 * M * M; b++)
      for (int i = 0; i < size && list [i] + (N - 1) * b <= 2 * M * M; i++)
	 if (prog (list [i], b))
	 {
	    hay = true;
	    fprintf (fout, "%d %d\n", list [i], b);
	 }
   if (!hay)
      fprintf (fout, "NONE\n");

   return 0;
}
   
