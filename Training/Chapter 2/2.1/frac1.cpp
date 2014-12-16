/*
 ID: arpon.r1
 PROG: frac1
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;



int gcd(int a, int b)
{
	if (b == 0)
		return a;
	else
		return gcd(b, a % b);
}

int main()
{
	ofstream fout("frac1.out");
	ifstream fin("frac1.in");
	int n;
	vector<pair<double, pair<int, int> > > frax;
	fin >> n;
	for (int i = 1; i < n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			int g = gcd(i, j);
			double x = i;
			double y = j;
			frax.push_back(make_pair(x/y, make_pair(i/g, j/g)));
		}
	}
	sort(frax.begin(), frax.end());
	frax.erase(unique(frax.begin(), frax.end()), frax.end());
	fout << "0/1" << endl;
	for (int x = 0; x < frax.size(); x++)
		fout << frax[x].second.first << "/" << frax[x].second.second << endl;
	fout << "1/1" << endl;
	return 0;
}

