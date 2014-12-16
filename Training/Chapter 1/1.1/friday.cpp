/*
ID: arpon.r1
PROG: friday
LANG: C++
*/
#include <cstdio>
using namespace std;

FILE *fin = fopen ("friday.in", "r"), *fout = fopen ("friday.out", "w");

const int DAYS = 7, MONTHS = 12, month [] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, FEB = 1, START = 1900;

int N, count [DAYS];

bool leap (int year)
{
	return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

int len (int year, int mo)
{
	if (mo == FEB)
		return (leap (year)) ? month [mo] + 1 : month [mo];
	return month [mo];
}

int main ()
{
	fscanf (fin, "%d", &N);
	
	int day = 0;
	
	for (int i = START; i < START + N; i++)
		for (int j = 0; j < MONTHS; j++)
		{
			count [day]++;
			day = (day + len (i, j)) % 7;
		}
	
	for (int i = 0; i < DAYS - 1; i++)
		fprintf (fout, "%d ", count [i]);
	fprintf (fout, "%d\n", count [DAYS - 1]);
	
	return 0;
}


