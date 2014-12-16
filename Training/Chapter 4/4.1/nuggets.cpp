/*
 ID: arpon.r1
 PROG: nuggets
 LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

#define MAXSIZE 65024

int nopts, sizes[10], dyn[MAXSIZE + 1];

int gcd(int a, int b)
{
	int t;
	while (b != 0)
	{
		t = b;
		b = a % b;
		a = t;
	}
	return a;
}

int main()
{
	ofstream fout("nuggets.out");
	ifstream fin("nuggets.in");
	int i, j, factor = 0;
	fin >> nopts;
	for (i = 0; i < nopts; i++)
	{
		fin >> sizes[i];
		factor = gcd(sizes[i], factor);
	}
	if (factor != 1)
		fout << 0 << endl;
	else
	{
		dyn[0] = 1;
		for (i = 0; i < nopts; i++)
			for (j = 0; j <= MAXSIZE - sizes[i]; j++)
				if (dyn[j])
					dyn[j + sizes[i]] = 1;
		int impossible = 0;
		for (i = MAXSIZE; i >= 0; i--)
			if (!dyn[i])
			{
				impossible = i;
				break;
			}
		fout << impossible << endl;
	}
}