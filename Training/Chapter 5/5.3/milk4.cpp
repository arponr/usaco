/*
 ID: arpon.r1
 PROG: milk4
 LANG: C++
 */

#include <cstdio>
#include <algorithm>
using namespace std;

FILE *fin = fopen ("milk4.in", "r"), *fout = fopen ("milk4.out", "w");

const int MAXP = 105, MAXQ = 20005;

int Q, P, pail [MAXP];
bool used [MAXP], dp [MAXQ];

bool knap ()
{
	memset (dp, false, sizeof (dp));
	dp [0] = true;
	
	for (int i = 0; i < P && !dp [Q]; i++)
		if (used [i])
			for (int j = pail [i]; j <= Q; j++)
				dp [j] |= dp [j - pail [i]];
	
	return dp [Q];
}

bool dfs (int k, int s)
{
	if (k == 0)
		return knap ();
	
	for (int i = s; i < P; i++)
	{
		used [i] = true;
		
		if (dfs (k - 1, i + 1))
			return true;
				
		used [i] = false;
	}
			
	return false;
}

int main ()
{
    fscanf (fin, "%d %d", &Q, &P);
    
    for (int i = 0; i < P; i++)
        fscanf (fin, "%d", pail + i);
		
    sort (pail, pail + P);
	
	int st;
	
	for (st = 1; !dfs (st, 0); st++);
    
	fprintf (fout, "%d", st);
	for (int i = 0; i < P; i++)
		if (used [i])
			fprintf (fout, " %d", pail [i]);
	fprintf (fout, "\n");
	
    return 0;
}


