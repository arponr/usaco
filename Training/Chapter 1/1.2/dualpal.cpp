/*
 ID: arpon.r1
 PROG: dualpal
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int digits;

int* conv(int b, int n)
{
	digits = 0;
	int num[15];
	while (n > 0)
	{
		num[digits] = n%b;
		digits++;
		n /= b;
	}
	return num;
}

bool pal(int* in)
{
	for (int x = 0; x <= digits/2; x++)
	{
		if (in[x] != in[digits - x - 1])
			return false;
	}
	return true;
}

bool dual(int n)
{
	int count = 0;
	for (int b = 2; b <= 10; b++)
	{
		if (pal(conv(b, n)))
		{
			count++;
			if (count == 2)
				return true;
		}
	}
	return false;
}

int main()
{
	ofstream fout("dualpal.out");
	ifstream fin("dualpal.in");
	int n, s;
	fin >> n >> s;
	for (s++; n > 0; s++)
	{
		if (dual(s))
		{
			fout << s << endl;
			n--;
		}
	}
	return 0;
}