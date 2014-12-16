/*
 ID: arpon.r1
 PROG: palsquare
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string reverse(string in)
{
	int n = in.size();
	for (int x = 0; x < n / 2; x++)
	{
		swap(in[x], in[n - x - 1]);
	}
	return in;
}
string conv(int b, int n)
{
	string digits = "0123456789ABCDEFGHIJKLMNOPQRZ";
	string output;
	while (n > 0)
	{
		output += digits[n%b];
		n /= b;
	}
	return reverse(output);
}

bool pal(string in)
{
	for (int x = 0; x <= in.size() / 2; x++)
	{
		if (in[x] != in[in.size() - x - 1])
			return false;
	}
	return true;
}

int main()
{
	ofstream fout("palsquare.out");
	ifstream fin("palsquare.in");
	int base;
	fin >> base;
	for (int x = 1; x <= 300; x++)
	{
		string i = conv(base, x);
		string iSqr = conv(base, x*x);
		if (pal(iSqr))
			fout << i << " " << iSqr << endl;
	}
	return 0;
}
