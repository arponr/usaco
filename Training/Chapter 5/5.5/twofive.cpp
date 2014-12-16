/*
ID: arpon.r1
PROG: twofive
LANG: C++
*/

#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

FILE *in = fopen ("twofive.in", "r"), *out = fopen ("twofive.out", "w");

const int N = 5;

char type, match [N * N + 1]; 
int ind;

int row [N], col [N], num [N], mem [N + 1][N + 1][N + 1][N + 1][N + 1];
bool used [N * N];
     
int dfs (int letter)
{
   if (mem [num [0]][num [1]][num [2]][num [3]][num [4]] == -1)
   {
      int total = 0;

      if (used [letter])
	 total += dfs (letter + 1);
      else
	 for (int i = 0; i < N; i++)
	    if (((i == 0) ? (num [i] < N) : (num [i] < num [i - 1])) && letter > row [num [i]] && letter > col [i])
	    {
	       num [i]++;
	       total += dfs (letter + 1);
	       num [i]--;
	    }
      
      mem [num [0]][num [1]][num [2]][num [3]][num [4]] = total;
   }

   return mem [num [0]][num [1]][num [2]][num [3]][num [4]];
}

inline void put (int letter, int r, int c)
{
   memset (mem, -1, sizeof (mem));
   mem [5][5][5][5][5] = 1;

   row [r] = col [c] = letter;
   used [letter] = true;
}

void givenN ()
{
   memset (row, -1, sizeof (row));
   memset (col, -1, sizeof (col));

   fscanf (in, "%d", &ind);
   
   for (int i = 0; i < N * N; i++)
   {
      int r = i / 5, c = i % 5, j;
      num [c]++;

      for (j = max (row [r], col [c]) + 1; j < N * N; j++)
	 if (!used [j])
	 {
	    put (j, r, c);
	    int now = dfs (0);
	    if (now >= ind)
	       break;
	    else
	       ind -= now;
	    used [j] = false;
	 }

      match [i] = 'A' + j;
   }

   match [N * N] = '\n';

   fputs (match, out);
}

void givenW ()
{
   memset (row, -1, sizeof (row));
   memset (col, -1, sizeof (col));

   fgets (match, N * N + 1, in);

   for (int i = 0; i < N * N; i++)
   {
      int r = i / 5, c = i % 5, j;
      num [c]++;

      for (j = max (row [r], col [c]) + 1; j < match [i] - 'A'; j++)
	 if (!used [j])
	 {
	    put (j, r, c);
	    ind += dfs (0);
	    used [j] = false;
	 }

      used [j] = true;
      row [r] = col [c] = j;
   }

   fprintf (out, "%d\n", ind + 1);
}

int main ()
{
   fscanf (in, "%c\n", &type);

   if (type == 'N')
      givenN ();
   else if (type == 'W')
      givenW ();

   return 0;
}
