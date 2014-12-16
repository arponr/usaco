/*
 ID: arpon.r1
 PROG: fence9
 LANG: C++
*/

#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

#define EPSILON 1e-8

int up (double x)
{
	int y = (int) floor(x); 
	if (x - y > EPSILON)
		y++;
	return y;
}

int down (double x)
{
	int y = (int) ceil(x); 
	if (y - x > EPSILON)
		y--;
	return y;
}

int main()
{
	ofstream fout("fence9.out");
	ifstream fin("fence9.in");
	int n, m, p, i, ncows = 0;
	double f[2];
	fin >> n >> m >> p;
	f[0] = (double) n / m;
	f[1] = (double) (n - p) / m;
	for (i = 1; i < m; i++)
		ncows += up(f[1] * i + p) - down(f[0] * i) - 1;
	fout << ncows << endl;
}