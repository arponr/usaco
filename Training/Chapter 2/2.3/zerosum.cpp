/*
 ID: arpon.r1
 PROG: zerosum
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int n;
vector<int> digits;
char operations[3] = {' ', '+', '-'};
ofstream fout("zerosum.out");

void print(char* seq)
{
	for (int x = 0; x < n - 1; x++)
		fout << x + 1 << seq[x];
	fout << n << endl;
}

int check(char* in, vector<int> nums)
{
	for (int i = 0; i < n - 1; i++)
	{
		if (in[i] == ' ')
		{
			int back = i;
			while (nums[back] == -1)
				back--;
			nums[back] = nums[back] * 10 + nums[i+1];
			nums[i + 1] = -1;
		}
	}
	int sum = nums[0];
	for (int j = 1; j < n; j++)
	{
		if (nums[j] != -1)
		{
			if (in[j - 1] == '+')
				sum += nums[j];
			else if (in[j - 1] == '-')
				sum -= nums[j];
		}
	}
	if (!sum)
		cout << nums[0] << endl;
	return !sum;
}

void search(int cycle, char current[])
{
	if (cycle == n - 1)
	{
		if (check(current, digits))
			print(current);
		return;
	}
	for (int y = 0; y < 3; y++)
	{
		current[cycle] = operations[y];
		search(cycle + 1, current);
	}
}

int main()
{
	ifstream fin("zerosum.in");
	fin >> n;
	for (int a = 1; a <= n; a++)
		digits.push_back(a);
	char temp[n - 1];
	search (0, temp);
	return 0;
}