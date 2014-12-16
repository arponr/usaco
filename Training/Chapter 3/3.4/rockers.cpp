/*
 ID: arpon.r1
 PROG: rockers
 LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ofstream fout("rockers.out");
	ifstream fin("rockers.in");
	int nsongs, ndisks, cdlen, i, j, k, p, optimal = 0;
	fin >> nsongs >> cdlen >> ndisks;
	int dp[ndisks + 1][cdlen + 1][nsongs + 1], songlen[nsongs + 1];
	memset(dp, 0, sizeof(dp));
	songlen[0] = 0;
	for (i = 1; i <= nsongs; i++)
		fin >> songlen[i];
	for (i = 0; i < ndisks; i++)
		for (j = 0; j <= cdlen; j++)
			for (k = 0; k <= nsongs; k++)
			{
				for (p = k + 1; p <= nsongs; p++)
					if (j + songlen[p] <= cdlen)
					{
						if (dp[i][j][k] + 1 > dp[i][j + songlen[p]][p])
							dp[i][j + songlen[p]][p] = dp[i][j][k] + 1;
					}
					else if (songlen[p] <= cdlen && dp[i][j][k] + 1 > dp[i+1][songlen[p]][p])
						dp[i+1][songlen[p]][p] = dp[i][j][k] + 1;
				if (dp[i][j][k] > optimal)
					optimal = dp[i][j][k];
			}
	fout << optimal << endl;
}
						

