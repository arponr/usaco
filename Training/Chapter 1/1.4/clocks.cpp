/*
 ID: arpon.r1
 PROG: clocks
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
int turns[9][5] = {{0,1,3,4,-1}, 
				   {0,1,2,-1,-1},
				   {1,2,4,5,-1},
				   {0,3,6,-1,-1},
				   {1,3,4,5,7},
				   {2,5,8,-1,-1},
				   {3,4,6,7,-1},
				   {6,7,8,-1,-1},
				   {4,5,7,8,-1}};
int sol[9], solNum = 10000000, state[9];

void search(int m, int moves[])
{
	if (m == 9)
	{	
		for (int x = 0; x < 9; x++)
			if (state[x] != 12)
				return;
		int tempSum = 0;
		for (int x = 0; x < 9; x++)
			tempSum += moves[x];
		if (tempSum < solNum)
		{
			for (int x = 0; x < 9; x++)
				sol[x] = moves[x];
			solNum = tempSum;
		}
		return;
	}
	for (int i = 3; i >= 0; i--)
	{
		for (int g = 0; g < 5; g++)
		{
			if (turns[m][g] == -1)
				break;
			state[turns[m][g]] += i * 3;
			while (state[turns[m][g]] > 12)
				state[turns[m][g]] -= 12;
		}
		moves[m] = i;
		search (m + 1, moves);
		for (int g = 0; g < 5; g++)
		{
			if (turns[m][g] == -1)
				break;
			state[turns[m][g]] -= i * 3;
			while (state[turns[m][g]] <= 0)
				state[turns[m][g]] += 12;
		}
		moves[m] = 0;
	}
}
int main()
{
	ofstream fout("clocks.out");
	ifstream fin("clocks.in");
	int moves[9];
	for (int i = 0; i < 9; i++)
	{
		fin >> state[i];
		moves[i] = 0;
		sol[i] = 0;
	}
	search (0, moves);
	vector<int> out;
	for (int a = 0; a < 9; a++)
	{
		for (int b = 0; b < sol[a]; b++)
			out.push_back(a + 1);
	}
	for (int i = 0; i < out.size() - 1; i++)
		fout << out[i] << " ";
	fout << out[out.size() - 1] << endl;
	return 0;
}
