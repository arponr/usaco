/*
 ID: arpon.r1
 PROG: fracdec
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
bool rep = false;
int k = 0;
vector<int> out;
void divide(int x, int y)
{
	int seen_rems[y];
	for (int i = 0; i < y; i++)
		seen_rems[i] = -1;
	int count = 0;
	while (1)
	{
		x %= y;
		if (x == 0)
			break;
		if (seen_rems[x] > -1)
		{
			rep = true;
			break;
		}
		seen_rems[x] = count;
		x *= 10;
		out.push_back(x / y);
		count++;
	}
	k = seen_rems[x];
}

int main()
{
	ofstream fout("fracdec.out");
	ifstream fin("fracdec.in");
	int n, d;
	fin >> n >> d;
	int whole = n / d;
	n -= d * whole;
	fout << whole << ".";
	int test = whole;
	int digits = 0;
	while (test > 0)
	{
		digits++;
		test /= 10;
	}
	if (digits == 0)
		digits++;
	digits++;
	cout << digits;
	if (n > 0)
	{
		divide(n, d);
		if (rep)
		{
			//cout << k;
			int charcount = 0, linecount = 0;
			for (int i = 0; i < out.size(); i++)
			{
				if ((linecount == 0 && charcount > 0 && charcount % (76 - digits) == 0))
				{
					charcount = 0;
					linecount++;
					fout << endl;
				}
				else if (linecount > 0 && charcount % 76 == 0)
				{
					charcount = 0;
					linecount++;
					fout << endl;
				}
				if (i == k)
				{
					fout << "(";
					charcount++;
				}
				fout << out[i];
				charcount++;
			}
			fout << ")";
		}
		else
		{
			for (int i = 0; i < out.size(); i++)
			{
				if (i > 0 && i % 76 == 0)
					fout << endl;
				fout << out[i];
			}
		}
		fout << endl;
	}
	else 
		fout << 0 << endl;
}
