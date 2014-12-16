/*
 ID: arpon.r1
 PROG: game1
 LANG: C++
 */

#include <iostream>
#include <fstream>

using namespace std;

int N, board[101], dp[101][101], subtotals[101][101];

int main()
{
    ofstream fout("game1.out");
    ifstream fin("game1.in");
    int i, j;
    fin >> N;
    for (i = 0; i < N; i++)
	{
        fin >> board[i];
		subtotals[i][0] = 0;
	}
	for (j = 1; j <= N; j++)
		for (i = 0; i + j <= N; i++)
			subtotals[i][j]  = board[i] + subtotals[i+1][j-1];
    for (j = 2; j <= N; j++)
        for (i = 0; i + j <= N; i++)
            if (j == 2)
				dp[i][j] = max(board[i], board[i+1]);
            else
                dp[i][j] = max(subtotals[i+1][j-1] - dp[i+1][j-1] + board[i], subtotals[i][j-1] - dp[i][j-1] + board[i+j-1]);
	fout << dp[0][N] << " " << subtotals[0][N] - dp[0][N] << endl;
}

