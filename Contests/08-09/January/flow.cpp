/*
ID: arpon.r1
PROG: flow
LANG: C++
*/

using namespace std;
#include <iostream>
#include <fstream>
#define INF 100000000

int n, c[52][52], p[52];

int hash(char ch)
{ 
	return (ch >= 'a' && ch <= 'z') ? ch - 'a' + 26 : ch - 'A'; 
}

int augment()
{
	int q[700], r = 0, w = 1, i, cur, prev, pcap = INF;
	q[0] = 0 ;
	while (r < w)
	{
		cur = q[r++];
		if (cur == 25)
			break;
		for (i = 0; i < 52; i++)
			if (c[cur][i] && p[i] == -1)
			{
				q[w++] = i;
				p[i] = cur;
			}
	}
	cur = 25;
	while ((prev = p[cur]) != -1)	
	{
		pcap = min(pcap, c[prev][cur]);
		cur = prev;
	}
	cur = 25;
	while ((prev = p[cur]) != -1)	
	{
		c[prev][cur] -= pcap;
		c[cur][prev] += pcap;
		cur = prev;
	}
	return (pcap == INF) ? 0 : pcap;
}

int main()
{
	ofstream fout("flow.out");
	ifstream fin("flow.in");
	int i, cap, flow, final;
	char a, b;
	fin >> n;
	for (i = 0; i < n; i++)
	{
		fin >> a >> b >> cap;
		c[hash(a)][hash(b)] += cap;
		c[hash(b)][hash(a)] += cap;
	}
	while (flow = augment())
	{
		for (i = 0; i < 52; i++) 
			p[i] = -1;
		final += flow;
	}
	fout << flow << endl;
}


