/*
 ID: arpon.r1
 PROG: shopping
 LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

typedef struct offer offer;
struct offer
{
	int involved[1000], price;
};

int main()
{
	ofstream fout("shopping.out");
	ifstream fin("shopping.in");
	int s, b, n, c, k, p, i, j;
	int map[5], prices[5], dp[6][6][6][6][6], nwant[5];
	memset(dp, 0, sizeof(dp));
	memset(prices, 0, sizeof(prices));
	memset(nwant, 0, sizeof(nwant));
	memset(map, 0, sizeof(map));
	fin >> s;
	offer A[s];
	for (i = 0; i < s; i++)
	{
		fin >> n;
		offer in;
		memset(in.involved, 0, sizeof(in.involved));
		for (j = 0; j < n; j++)
		{
			fin >> c >> k;
			in.involved[c] = k;
		}
		fin >> in.price;
		A[i] = in;
	}
	fin >> b;
	for (i = 0; i < b; i++)
	{
		fin >> c >> k >> p;
		map[i] = c;
		nwant[i] = k;
		prices[i] = p;
	}
	for (int a = 0; a < 6; a++)
		for (int b = 0; b < 6; b++)
			for (int c = 0; c < 6; c++)
				for (int d = 0; d < 6; d++)
					for (int e = 0; e < 6; e++)
					{
						dp[a][b][c][d][e] = a * prices[0] + b * prices[1] + c * prices[2] + d * prices[3] + e * prices[4];
						for (i = 0; i < s; i++)
						{
							if (A[i].involved[map[0]] <= a && A[i].involved[map[1]] <= b && A[i].involved[map[2]] <= c && A[i].involved[map[3]] <= d && A[i].involved[map[4]] <= e)
							{
								int div = 100000, amts[5] = {a, b, c, d, e};
								for (j = 0; j < 5; j++)
								{
									if (A[i].involved[map[j]] > 0)
										if (amts[j] / A[i].involved[map[j]] < div)
											div = amts[j] / A[i].involved[map[j]];
								}
								int temp[5];
								for (j = 0; j < 5; j++)
									temp[j] = (amts[j] - A[i].involved[map[j]] * div);
								int new_price = div * A[i].price + dp[temp[0]][temp[1]][temp[2]][temp[3]][temp[4]];
								if (new_price < dp[a][b][c][d][e])
									dp[a][b][c][d][e] = new_price;
							}
						}
					}
	fout << dp[nwant[0]][nwant[1]][nwant[2]][nwant[3]][nwant[4]] << endl;
}
		