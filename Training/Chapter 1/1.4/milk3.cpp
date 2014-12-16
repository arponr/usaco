/*
 ID: arpon.r1
 PROG: milk3
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int state[3], cap[3];
bool visited[21][21] = {false};
vector<int> sols;

void pour(int from, int to)
{
	if (cap[to] - state[to] < state[from])
	{
		state[from] -= cap[to] - state[to];
		state[to] = cap[to];
	}
	else
	{
		state[to] += state[from];
		state[from] = 0;
	}
}

void search()
{
	for (int x = 0; x < 3; x++)
		cout << state[x] << " ";
	cout << endl;
	if (visited[state[1]][state[2]])
		return;
	if (state[0] == 0)
		sols.push_back(state[2]);
	int a = state[0], b = state[1], c = state[2];
	visited[b][c] = true;
	pour(0, 1); search();
	state[0] = a; state[1] = b; state[2] = c;
	pour(0, 2); search();
	state[0] = a; state[1] = b; state[2] = c;
	pour(1, 0); search();
	state[0] = a; state[1] = b; state[2] = c;
	pour(1, 2); search();
	state[0] = a; state[1] = b; state[2] = c;
	pour(2, 0); search();
	state[0] = a; state[1] = b; state[2] = c;
	pour(2, 1); search();
	state[0] = a; state[1] = b; state[2] = c;
}

int main()
{
	ofstream fout("milk3.out");
	ifstream fin("milk3.in");
	for (int x = 0; x < 3; x++)
	{
		fin >> cap[x];
		if (x < 2)
			state[x] = 0;
		else
			state[x] = cap[x];
	}
	search();
	sort(sols.begin(), sols.end());
	for (int i = 0; i < sols.size() - 1; i++)
		fout << sols[i] << " ";
	fout << sols[sols.size() - 1] << endl;
	return 0;
}
