/*
 ID: arpon.r1
 PROG: milk
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
	ofstream fout("milk.out");
	ifstream fin("milk.in");
	int numF, price, amtMilk, finalPrice = 0, need;
	vector<int> milk(1001, 0);
	fin >> need >> numF;
	for (int x = 0; x < numF; x++)
	{
		fin >> price >> amtMilk;
		milk[price] += amtMilk;
	}
	for (int y = 0; y < 1001 && need > 0; y++)
	{
		if (milk[y] > 0)
		{
			if (milk[y] < need)
			{
				finalPrice += milk[y] * y;
				need -= milk[y];
			}
			else
			{
				finalPrice += y * need;
				need = 0;
			}
		}
	}
	fout << finalPrice << endl;
	return 0;
}