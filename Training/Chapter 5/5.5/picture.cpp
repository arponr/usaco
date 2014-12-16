/*
ID: arpon.r1
PROG: picture
LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

FILE *in = fopen ("picture.in", "r"), *out = fopen ("picture.out", "w");

const int MAXN = 5005, BOUND = 20001;

struct border 
{
   int sign, a, b, c;

   inline void init (int sign_, int a_, int b_, int c_)
   {
      sign = sign_; a = a_; b = b_; c = c_;
   }

   inline bool operator < (const border &other) const
   {
      return c < other.c;
   }
} len [2 * MAXN], wid [2 * MAXN];

int N, now [BOUND], last [BOUND], perim = 0;

void solve (border *list)
{
   sort (list, list + 2 * N);

   memset (now, 0, sizeof (now));
   int ind = 0;

   while (ind < 2 * N)
   {
      memcpy (last, now, sizeof (now));
      int C = list [ind].c;

      for (; ind < 2 * N && list [ind].c == C; ind++)
	 for (int i = list [ind].a; i < list [ind].b; i++)
	    now [i] += list [ind].sign;

      for (int i = 0; i < BOUND; i++)
	 if (last [i] == 0 && now [i] > 0 || now [i] == 0 && last [i] > 0)
	    perim++;
   }
}

int main ()
{
   fscanf (in, "%d", &N);

   for (int i = 0, x, X, y, Y; i < N; i++)
   {
      fscanf (in, "%d %d %d %d", &x, &y, &X, &Y);
      x += 10000; X += 10000; y += 10000; Y += 10000;

      len [2 * i].init (1,y, Y, x);
      len [2 * i + 1].init (-1, y, Y, X);

      wid [2 * i].init (1, x, X, y);
      wid [2 * i + 1].init (-1, x, X, Y);
   }

   solve (len);
   solve (wid);

   fprintf (out, "%d\n", perim);

   return 0;
}
      
