/*
ID: arpon.r1
PROG: fc
LANG: C++
*/

#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

FILE *fin = fopen ("fc.in", "r"), *fout = fopen ("fc.out", "w");

const int MAXN = 10005;

struct angle
{
    double val;
    int point;
    
    inline bool operator < (const angle &o) const
    {
        return val < o.val;
    }	
};

int N, hull [MAXN];
double x [MAXN], y [MAXN];
angle angles [MAXN];

inline double cross (double ux, double uy, double vx, double vy)
{
    return ux * vy - uy * vx;
}

inline double dist (double x1, double y1, double x2, double y2)
{
    return sqrt ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int main ()
{
    fscanf (fin, "%d", &N);
    
    double midx = 0, midy = 0;
    
    for (int i = 0; i < N; i++)
    {
	fscanf (fin, "%lf %lf", x + i, y + i);
	midx += (double) x [i] / N; midy += (double) y [i] / N;
    }
    
    for (int i = 0; i < N; i++)
    {
	angles [i].point = i;
	angles [i].val = atan2 (y [i] - midy, x [i] - midx);
    }
    
    sort (angles, angles + N);
    
    hull [0] = angles [0].point;
    hull [1] = angles [1].point;
    int hpos = 2;
    
    for (int i = 0; i < N; i++)
    {
	int p = angles [i].point;
	while (hpos > 1 && cross (x [hull [hpos - 2]] - x [hull [hpos - 1]], y [hull [hpos - 2]] - y [hull [hpos - 1]],
				  x [p] - x [hull [hpos - 1]], y [p] - y [hull [hpos - 1]]) >= 0)
	    hpos--;
	hull [hpos] = p;
	if (i < N - 1)
	    hpos++;
    }
    
    int hstart = 0;
    
    while (true)
    {
	if (hpos - hstart >= 2 && cross (x [hull [hpos - 1]] - x [hull [hpos]], y [hull [hpos - 1]] - y [hull [hpos]],
					 x [hull [hstart]] - x [hull [hpos]], y [hull [hstart]] - y [hull [hpos]]) >= 0)
	{
	    hpos--;
	    continue;
	}
	
	if (hpos - hstart >= 2 && cross (x [hull [hpos]] - x [hull [hstart]], y [hull [hpos]] - y [hull [hstart]],
					 x [hull [hstart + 1]] - x [hull [hstart]], y [hull [hstart + 1]] - y [hull [hstart]]) >= 0)
	{
	    hstart++;
	    continue;
	}
	break;
    }
    
    double len = 0;
    
    for (int i = hstart; i <= hpos; i++)
    {
	int next = (i == hpos) ? hstart : i + 1;
	len += dist (x [hull [i]], y [hull [i]], x [hull [next]], y [hull [next]]);
    }
    
    fprintf (fout, "%.2lf\n", len);
    return 0;
}
