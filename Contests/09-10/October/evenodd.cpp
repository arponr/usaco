/*
ID: arpon.r1
PROG: evenodd
LANG: C++
*/

#include <cstdio>
#include <cstring>
using namespace std;

FILE *fin = fopen ("evenodd.in", "r"), *fout = fopen ("evenodd.out", "w");

const int MAXN = 105, MAXLEN = 100;

int N;
char a [MAXLEN];

int main ()
{
   fscanf (fin, "%d\n", &N);

   for (int i = 0; i < N; i++)
   {
      fgets (a, MAXLEN, fin);
      fprintf (fout, "%s\n", ((a [strlen (a) - 2] - '0') % 2 == 0) ? "even" : "odd");
   }
}
