/*
 ID: arpon.r1
 PROG: money
 LANG: C++
 */

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ofstream fout("money.out");
	ifstream fin("money.in");
	int v, n;
	fin >> v >> n;
	long long dyn[10001];
	dyn[0] = 1;
	for (int a = 1; a <= n; a++)
		dyn[a] = 0;
	for (int i = 0; i < v; i++)
	{
		int val;
		fin >> val;
		for (int j = val; j <= n; j++)
			dyn[j] += dyn[j-val];
	}
	fout << dyn[n] << endl;
}