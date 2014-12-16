/*
ID: arpon.r1
PROG: hidden
LANG: C++
*/

#include <cstdio>
#include <cstring>
using namespace std;

FILE *in = fopen ("hidden.in", "r"), *out = fopen ("hidden.out", "w");

const int MAXL = 2 * 100005, LINE = 72;

char pass [MAXL];
int L, ind = 0;
      
int main ()
{
   fscanf (in, "%d\n", &L);

   for (int i = 0; i < L; i += LINE)
      fscanf (in, "%s", pass + i);
   memcpy (pass + L, pass, L);

   for (int i = 1; i < L; i++)
   {
      char *p = pass + i, *q = pass + ind;

      int j;
      for (j = 0; j < L && *p == *q; j++, p++, q++)
	 ;
      
      if (*p < *q)
	 ind = i;

      if (j > 1) 
	 i += j - 1;
   }
   
   fprintf (out, "%d\n", ind);

   return 0;
}
