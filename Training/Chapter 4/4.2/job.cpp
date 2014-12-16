/*
 ID : arpon.r1
 PROG: job
 LANG: C++
 */

#include <iostream>
#include <fstream>

using namespace std;

#define MAXN 1000
#define MAXM 30
#define INF 100000000

int N, M1, M2,
	A_end[MAXM], B_end[MAXM],
	A_time[MAXM], B_time[MAXM],
	A_done[MAXN], B_done[MAXN];

void solve()
{
	int i, j, opt, opt_loc;
	for (i = 0; i < N; i++)
	{
		opt = INF;
		opt_loc = -1;
		for (j = 0; j < M1; j++)
			if (A_end[j] + A_time[j] < opt)
			{
				opt = A_end[j] + A_time[j];
				opt_loc = j;
			}
		A_end[opt_loc] = A_done[i] = opt;
		
		opt = INF;
		opt_loc = -1;
		for (j = 0; j < M2; j++)
			if (B_end[j] + B_time[j] < opt)
			{
				opt = B_end[j] + B_time[j];
				opt_loc = j;
			}
		B_end[opt_loc] = B_done[i] = opt;
	}
}

int main()
{
	ofstream fout("job.out");
	ifstream fin("job.in");
	int i, out1 = 0, out2 = 0;
	fin >> N >> M1 >> M2;
	for (i = 0; i < M1; i++)
		fin >> A_time[i];
	for (i = 0; i < M2; i++)
		fin >> B_time[i];
	solve();
	for (i = 0; i < N; i++)
		if (A_done[i] > out1)
			out1 = A_done[i];
	for (i = 0; i < N; i++)
		if (A_done[i] + B_done[N - i - 1] > out2)
			out2 = A_done[i] + B_done[N - i - 1];
	fout << out1 << ' ' << out2 << endl;
}