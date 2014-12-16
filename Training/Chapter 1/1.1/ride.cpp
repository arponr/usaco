/*
ID: arpon.r1
PROG: ride
LANG: C++
*/
#include <cstdio>
#include <cstring>
using namespace std;

FILE *fin = fopen ("ride.in", "r"), *fout = fopen ("ride.out", "w");

const int MAXLEN = 10;

char comet [MAXLEN], group [MAXLEN];

int hash (char *s)
{
	int val = 1;
	char *p;
	
	for (p = s; *p; p++)
		val = (val * (*p - 'A' + 1)) % 47;
	
	return val;
}

int main ()
{
	fscanf (fin, "%s\n%s", comet, group);
	
	fprintf (fout, (hash (comet) == hash (group)) ? "GO\n" : "STAY\n");
	
	return 0;
}

