/*
 ID: arpon.r1
 PROB: fads
 LANG: C++
*/

using namespace std;
#include <cstdio>
#include <cstring>
#include <algorithm>

FILE *fin = fopen ("fads.in", "r"), *fout = fopen ("fads.out", "w");

const int MAXN = 100005;

int N, L, K, res [MAXN];

int main ()
{
	fscanf (fin, "%d %d %d", &N, &L, &K);
	
	for (int i = 0; i < N; i++)
		fscanf (fin, "%d", res + i);
	sort (res, res + N);
	
	int p;
	for (p = 0; p < N && L >= res [p]; p++)
		L += K;
	
	fprintf (fout, "%d\n", p);
	return 0;
}
