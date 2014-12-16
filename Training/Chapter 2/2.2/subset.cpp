/*
 ID: arpon.r1
 PROG: subset
 LANG: C++
 */

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ofstream fout("subset.out");
	ifstream fin("subset.in");
	int n;
	fin >> n;
	if (n * (n + 1)  % 4 > 0)
	{
		fout << 0 << endl;
		return 0;
	}
	int sum = (n * (n + 1) / 4);
	long long dynamic[1000];
	dynamic[0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = sum; j >= i; j--)
			dynamic[j] += dynamic[j-i];
	fout << dynamic[sum] / 2 << endl;
}