/*
 ID: !cowlovers
 PROG: cattleb
 LANG: C++
 */

#include <cstdio>
#include <math.h>

using namespace std;

#define INF 1000000000

typedef struct plyr plyr;
struct plyr
{
	double x, y, deltax, deltay;
};

int nbruisers, approaching = 0, distancing = 0;
double prox, bx, by, bvx, bvy, x, y, vx, vy, t, intersections[50000][2];
plyr bess, bruisers[50000];

inline plyr construct(double x, double y, double vx, double vy)
{
	plyr p;
	p.x = x;
	p.y = y;
	p.deltax = vx;
	p.deltay = vy;
	return p;
}

inline bool termin()
{
	if (bess.x < -1000 || bess.x > 1000 || bess.y < -1000 || bess.y > 1000 || distancing > approaching)
		return true;
	for (int i = 0; i < nbruisers; i++)
		if (bruisers[i].x >= -1000 && bruisers[i].x <= 1000 && bruisers[i].x >= -1000 && bruisers[i].y <= 1000 && (bruisers[i].deltax != 0 || bruisers[i].deltay != 0))
			return false;
	return true;
}

inline double get_dist(double a, double b, double c, double d)
{
	return sqrt((a - c) * (a - c) + (b - d) * (b - d));
}

inline void app_dist()
{
	approaching = 0;
	distancing = 0;
	for (int i = 0; i < nbruisers; i++)
	{
		if (intersections[i][0] == INF)
			continue;
		if (get_dist(bruisers[i].x + bruisers[i].deltax, bruisers[i].y + bruisers[i].deltay, intersections[i][0], intersections[i][1]
			<= get_dist(bruisers[i].x, bruisers[i].y, intersections[i][0], intersections[i][1])))
				approaching++;
		else
			distancing++;
	}
}

int main()
{
	FILE *fin = fopen("cattleb.in", "r"), *fout = fopen("cattleb.out", "w");
	int i, j;
	double bess_m, bess_b;
	fscanf(fin, "%d %lf %lf %lf %lf %lf", &nbruisers, &prox, &bx, &by, &bvx, &bvy);
	bess = construct(bx, by, bvx, bvy);
	if (bvx == 0)
	{
		bess_m = bvy;
		bess_b = by;
	}
	else
	{
		bess_m = bvy / bvx;
		bess_b = by - bvy/bvx * bx;
	}
	for (i = 0; i < nbruisers; i++)
	{
		double x, y, vx, vy, m, b;
		fscanf(fin, "%lf %lf %lf %lf", &x, &y, &vx, &vy);
		bruisers[i] = construct(x, y, vx, vy);
		if (vx == 0)
		{
			m = vy;
			b = y;
		}
		else
		{
			m = vy / vx;
			b = y - vy/vx * x;
		}
		if (m == bess_m)
			intersections[i][0] = INF;
		else
		{
			intersections[i][0] = (b - bess_b) / (bess_m - m);
			intersections[i][1] = intersections[i][0] * bess_m + bess_b;
		}
	}
	int max_attacks = 0, GET_TO_A_ONE = 0;
	app_dist();
	for (t = 0; !termin() && t <= 2000 && max_attacks < nbruisers; t += .0005)
	{
		int cur_attacks = 0;
		bess.x += bess.deltax * t;
		bess.y += bess.deltay * t;
		for (j = 0; j < nbruisers; j++)
		{
			bruisers[j].x += bruisers[j].deltax * t;
			bruisers[j].y += bruisers[j].deltay * t;
			if (get_dist(bess.x, bess.y, bruisers[j].x, bruisers[j].y) <= prox)
				cur_attacks++;
		}
		if (cur_attacks > max_attacks)
		{
			max_attacks = cur_attacks;
		}
		if (GET_TO_A_ONE == 1000)
		{
			GET_TO_A_ONE = 0;
			app_dist();
		}
		else
			GET_TO_A_ONE++;
	}
	fprintf(fout, "%d\n", max_attacks);
}

