/*
ID: arpon.r1
PROG: cowxor
LANG: C++
*/

#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

FILE *in = fopen ("cowxor.in", "r"), *out = fopen ("cowxor.out", "w");

const int MAXN = 100005, B = 21;

struct node
{
    int cow, val;
    node *ch [2];

    inline node ()
    { 
	ch [0] = ch [1] = NULL;
    }
} *trie;

inline void insert (int c, int n)
{
    node *t = trie;

    for (int i = B - 1; i >= 0; i--)
    {
	int x = (n >> i) & 1;
	if (t->ch [x] == NULL)
	    t->ch [x] = new node;
	t = t->ch [x];
    }

    t->cow = c;
    t->val = n;
}	

int N, M = -1, S, E;

inline void lookup (int e, int u, int v)
{
    node *t = trie;

    for (int i = B - 1; i >= 0; i--)
    {
	int x = (u >> i) & 1;
	t = (t->ch [!x] == NULL) ? t->ch [x] : t->ch [!x];
    }

    int s = t->cow;
    int m = (s == e) ? v : u ^ (t->val);
    if (m > M)
    {
	M = m;
	S = s + (s != e);
	E = e;
    }
}

int main ()
{
    trie = new node;
    fscanf (in, "%d", &N);

    for (int i = 1, u = 0, v; i <= N; i++)
    {
	fscanf (in, "%d", &v);
	u ^= v;
	insert (i, u);
	lookup (i, u, v);
    }

   fprintf (out, "%d %d %d\n", M, S, E);

   return 0;
}
