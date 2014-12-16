/*
 ID: arpon.r1
 PROG: crypt1
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;
bool checkDigits[10];

bool check(int d, int n)
{
	if (n / pow(10, d - 1) < 1 || n / pow(10, d - 1) >= 10)
		return false;
	else
	{
		while (n > 0)
		{
			if (!checkDigits[n % 10])
				return false;
			n /= 10;
		}
	}
	return true;
}
			
int main()
{
	ofstream fout("crypt1.out");
	ifstream fin("crypt1.in");
	int n, line1, line2, solutions = 0;
	int digits[n];
	checkDigits[0] = false;
	checkDigits[1] = false;
	checkDigits[2] = false;
	checkDigits[3] = false;
	checkDigits[4] = false;
	checkDigits[5] = false;
	checkDigits[6] = false;
	checkDigits[7] = false;
	checkDigits[8] = false;
	checkDigits[9] = false;
	fin >> n;
	for (int x = 0; x < n; x++)
	{
		int temp;
		fin >> temp;
		checkDigits[temp] = true;
		digits[x] = temp;
	}
	for (int a = 0; a < n; a++)
	{
		for (int b = 0; b < n; b++)
		{
			for (int c = 0; c < n; c++)
			{
				for (int d = 0; d < n; d++)
				{
					for (int e = 0; e < n; e++)
					{
						line1 = 100 * digits[a] + 10 * digits[b] + digits[c];
						line2 = 10 * digits[d] + digits[e];
						if (check(3, line1 * digits[d]) && check(3, line1 * digits[e]) && check(4, line1 * line2))
							solutions++;
					}
				}
			}
		}
	}
	fout << solutions << endl;
	return 0;
}
	