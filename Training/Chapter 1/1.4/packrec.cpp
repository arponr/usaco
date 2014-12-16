/*
 ID: arpon.r1
 PROG: packrec
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int rots[4][16], heights[4][2], widths[4][2];
vector< pair<int, pair<int, int> > > sols;

void fillRots()
{
	int count = 0;
	for (int a = 0; a < 2; a++)
	{
		for (int b = 0; b < 2; b++)
		{
			for (int c = 0; c < 2; c++)
			{
				for (int d = 0; d < 2; d++)
				{
					rots[0][count] = a;
					rots[1][count] = b;
					rots[2][count] = c;
					rots[3][count] = d;
					count++;
				}
			}
		}
	}
}
			

int main()
{
	ofstream fout("packrec.out");
	ifstream fin("packrec.in");
	for (int x = 0; x < 4; x++)
	{
		int w, h;
		fin >> w >> h;
		widths[x][0] = w;
		widths[x][1] = h;
		heights[x][0] = h;
		heights[x][1] = w;
	}
	fillRots();
	int perms[4] = {0,1,2,3}, order = 0, x, y;
	int minimum = 1000000000;
	while (order < 16)
	{
		int w[4], h[4];
		for (int g = 0; g < 4; g++)
		{
			w[g] = widths[g][rots[g][order]];
			h[g] = heights[g][rots[g][order]];
		}
		do
		{
			x = w[perms[0]] + w[perms[1]] + w[perms[2]] + w[perms[3]];
			y = max(max(h[0], h[1]), max(h[2], h[3]));
			if (x * y <= minimum)
			{
				minimum = x * y;
				sols.push_back(make_pair(x * y, make_pair(min(x, y), max(x,y))));
			}
			
			x = max(w[perms[0]], w[perms[1]] + w[perms[2]] + w[perms[3]]);
			y = max(max(h[perms[1]], h[perms[2]]), h[perms[3]]) + h[perms[0]];
			if (x * y <= minimum)
			{
				minimum = x * y;
				sols.push_back(make_pair(x * y, make_pair(min(x, y), max(x,y))));
			}
			
			x = max(w[perms[0]], w[perms[2]] + w[perms[3]]) + w[perms[1]];
			y = max(max(h[perms[2]] + h[perms[0]], h[perms[3]] + h[perms[0]]), h[perms[1]]);
			if (x * y <= minimum)
			{
				minimum = x * y;
				sols.push_back(make_pair(x * y, make_pair(min(x, y), max(x,y))));
			}
			
			x = w[perms[0]] + max(w[perms[1]], w[perms[2]]) + w[perms[3]];
			y = max(max(h[perms[0]], h[perms[1]] + h[perms[2]]), h[perms[3]]);
			if (x * y <= minimum)
			{
				minimum = x * y;
				sols.push_back(make_pair(x * y, make_pair(min(x, y), max(x,y))));
			}
			
			x = max(w[perms[0]] + w[perms[2]], w[perms[1]] + w[perms[3]]);
			y = max(h[perms[0]] + h[perms[1]], h[perms[2]] + h[perms[3]]);
			if (x < w[perms[0]] + w[perms[3]] && y < h[perms[0]] +  h[perms[3]])
                x = w[perms[0]] + w[perms[3]];
            if (x < w[perms[1]] + w[perms[2]] && y < h[perms[1]] +  h[perms[2]])
                x = w[perms[1]] + w[perms[2]];
			if (x * y <= minimum)
			{
				minimum = x * y;
				sols.push_back(make_pair(x * y, make_pair(min(x, y), max(x,y))));
			}
		}
		while (next_permutation(perms, perms + 4));
		order++;
	}
	fout << minimum << endl;
	sort(sols.begin(), sols.end());
	sols.erase(unique(sols.begin(), sols.end()), sols.end());
	for (int x = 0; x < sols.size(); x++)
	{
		if (sols[x].first == minimum)
			fout << sols[x].second.first << " " << sols[x].second.second << endl;
	}
	return 0;
}



