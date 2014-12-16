/*
 ID: arpon.r1
 PROG: chkr
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int n, opps = 0;
char board[30][30];
vector<pair<int, int> > kings, sol;

void search(int x, int y, int count, vector<pair<int, int> > moves)
{
	if (x < 0 || y < 0 || x >= n || y >= n)
		return;
	moves.push_back(make_pair(x, y));
	if (count == 0)
	{
		sol.clear();
		for (int i = 0; i < moves.size(); i++)
			sol.push_back(make_pair(moves[i].first, moves[i].second));
		return;
	}
	if (board[x-1][y-1] == 'o' && board[x-2][y-2] == '+')
	{
		board[x-1][y-1] = '-';
		search(x-2, y-2, count - 1, moves);
		board[x-1][y-1] = 'o';
	}
	if (board[x-1][y+1] == 'o' && board[x-2][y+2] == '+')
	{
		board[x-1][y+1] = '-';
		search(x-2, y+2, count - 1, moves);
		board[x-1][y+1] = 'o';
	}
	if (board[x+1][y-1] == 'o' && board[x+2][y-2] == '+')
	{
		board[x+1][y-1] = '-';
		search(x+2, y-2, count - 1, moves);
		board[x+1][y-1] = 'o';
	}
	if (board[x+1][y+1] == 'o' && board[x+2][y+2] == '+')
	{
		board[x+1][y+1] = '-';
		search(x+2, y+2, count - 1, moves);
		board[x+1][y+1] = 'o';
	}
}
		
int main()
{
	ofstream fout("chkr.out");
	ifstream fin("chkr.in");
	fin >> n;
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < n; y++)
		{
			fin >> board[x][y];
			if (board[x][y] == 'K')
				kings.push_back(make_pair(x, y));
			else if (board[x][y] == 'o')
				opps++;
		}
	}
	vector<pair<int, int> > temp;
	for (int i = 0; i < kings.size(); i++)
		search(kings[i].first, kings[i].second, opps, temp);
	for (int a = 0; a < sol.size(); a++)
		fout << sol[a].first + 1 << " " << sol[a].second + 1 << endl;
	return 0;
}
	

