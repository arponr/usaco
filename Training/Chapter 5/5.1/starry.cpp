/*
 ID: arpon.r1
 PROG: starry
 LANG: C++
 */

#include <cstdio>
#include <algorithm>
using namespace std;

FILE *fin = fopen ("starry.in", "r"), *fout = fopen ("starry.out", "w");

const int MAXHW = 105, MAXCL = 505, MAXST = 165, NLTRS = 26, NDIR = 8, INF = 1000000005,
	      dx [8] = {0, 1, 1, 1, 0, -1, -1, -1}, dy [8] = {-1, -1, 0, 1, 1, 1, 0, -1};

struct cluster
{
	int r [MAXST], c [MAXST], nstars,
		minr, minc, maxr, maxc, h, w;
	char label;
	
	void init ()
	{
		memset (r, -1, sizeof (r));
		memset (c, -1, sizeof (c));
		minr = minc = INF;
		maxr = maxc = -1;
		nstars = 0;
		label = '?';
	}
	
	void reinit ()
	{
		for (int i = 0; i < nstars; i++)
		{
			r [i] -= minr;
			c [i] -= minc;
		}
		
		h = maxr - minr + 1;
		w = maxc - minc + 1;
	}
	
	void rot ()
	{
		for (int i = 0; i < nstars; i++)
		{	
			int tmp = r [i];
			r [i] = c [i];
			c [i] = h - tmp - 1;
		}
		
		int tmp = h;
		h = w;
		w = tmp;
	}
	
	void ref ()
	{
		for (int i = 0; i < nstars; i++)
			c [i] = w - c [i] - 1;
	}
	
	bool sim (cluster o)
	{
		if (nstars != o.nstars || h != o.h || w != o.w)
			return false;
		
		bool a [h][w], b [h][w];
		memset (a, false, sizeof (a));
		memset (b, false, sizeof (b));
		for (int i = 0; i < nstars; i++)
		{
			a [r [i]][c [i]] = true;
			b [o.r [i]][o.c [i]] = true;
		}
		
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				if (a [i][j] != b [i][j])
					return false;
		return true;
	}
};

int R, C, nclust, lbl;
bool vis [MAXHW][MAXHW];
char map [MAXHW][MAXHW];
cluster clusts [MAXCL];

void add_star (int r, int c)
{
	clusts [nclust].r [clusts [nclust].nstars] = r;
	clusts [nclust].c [clusts [nclust].nstars] = c;
	clusts [nclust].nstars++;
	
	if (r < clusts [nclust].minr) clusts [nclust].minr = r;
	if (c < clusts [nclust].minc) clusts [nclust].minc = c;
	if (r > clusts [nclust].maxr) clusts [nclust].maxr = r;
	if (c > clusts [nclust].maxc) clusts [nclust].maxc = c;
}

void ff (int r, int c)
{
	if (r < 0 || r >= R || c < 0 || c >= C || map [r][c] == '0' || vis [r][c]) return;
	
	vis [r][c] = true;
	add_star (r, c);
	
	for (int i = 0; i < NDIR; i++)
		ff (r + dy [i], c + dx [i]);
}

bool check (cluster a, cluster b)
{
	int i;
	
	for (i = 0; i < 4; i++)
	{
		if (a.sim (b))
			break;
		b.rot ();
	}
	
	if (i < 4) return true;
	b.ref ();
	
	for (i = 0; i < 4; i++)
	{
		if (a.sim (b))
			break;
		b.rot ();
	}
	
	return i < 4;
}

int main ()
{
    fscanf (fin, "%d %d", &C, &R);
    for (int i = 0; i < R; i++)
        fscanf (fin, "%s", map [i]);
    
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            if (map [i][j] == '1' && !vis [i][j])
            {
				clusts [nclust].init ();
				ff (i, j);
				clusts [nclust++].reinit ();
            }
	
	for (int i = 0; i < nclust; i++)
	{
		if (clusts [i].label == '?')
		{
			clusts [i].label = lbl + 'a';
			lbl++;
		}
		
		for (int j = i + 1; j < nclust; j++)
			if (clusts [j].label == '?' && check (clusts [i], clusts [j]))
				clusts [j].label = clusts [i].label;
	}
	
	for (int i = 0; i < nclust; i++)
		for (int j = 0; j < clusts [i].nstars; j++)
			map [clusts [i].r [j] + clusts [i].minr][clusts [i].c [j] + clusts [i].minc] = clusts [i].label;
			
	for (int i = 0; i < R; i++)
		fprintf (fout, "%s\n", map [i]);
		
	return 0;
}


