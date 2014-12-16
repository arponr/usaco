/*
 ID: arpon.r1
 PROG: fact4
 LANG: C++
 */

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	FILE *fin = fopen("fact4.in", "r"), *fout = fopen("fact4.out", "w");
	int n;
	fscanf(fin, "%d", &n);
	for (int i = n - 1; i > 1; i--)
	{
		n *= i;
		while (n % 10 == 0) n /= 10;
		n %= 100000;
	}
	while (n % 10 == 0) n /= 10;
	fprintf(fout, "%d\n", n % 10);
}