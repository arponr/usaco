/*
 ID: arpon.r1
 PROG: sprime
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>

using namespace std;
int d1[4] = {2,3,5,7}, od[4] = {1,3,7,9};
vector<int> sols;

bool is_prime(int x)
{
	if (x == 2)
		return true;
	if (x == 1 || x % 2 == 0)
		return false;
	for (int a = 3; a * a <= x; a += 2)
		if (x % a == 0)
			return false;
	return true;
}

void search(int len, int temp, int num)
{
	if (temp < len)
	{
		if (!is_prime(num))
			return;
		if (temp == 0)
		{
			sols.push_back(num);
			return;
		}
		for (int y = 0; y < 4; y++)
			search(len, temp - 1, num * 10 + od[y]);
	}
	else
		for (int x = 0; x < 4; x++)
			search(len, temp - 1, d1[x]);
}

int main()
{
	ofstream fout("sprime.out");
	ifstream fin("sprime.in");
	int len;
	fin >> len;
	search(len, len, 0);
	for (int i = 0; i < sols.size(); i++)
		fout << sols[i] << endl;
	return 0;
}
