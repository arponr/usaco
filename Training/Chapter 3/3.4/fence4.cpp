/*
 ID: arpon.r1
 PROG: fence4
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

#define EPSILON 1e-8
#define MAXV 200

int nv;
double v[MAXV + 1][2], obsx, obsy;
bool visible[MAXV];

int side_of_line(double ax, double ay, double bx, double by, double cx, double cy)
{
	double ux, uy, vx, vy, cross;
	ux = bx - ax;
	uy = by - ay;
	vx = cx - ax;
	vy = cy - ay;
	cross = ux * vy - uy * vx;
	if (cross < -EPSILON) return -1;
	else if (cross > EPSILON) return 1;
	return 0;
}

bool intersect(double ax, double ay, double bx, double by, double cx, double cy, double dx, double dy)
{
	if (side_of_line(ax, ay, bx, by, cx, cy) * side_of_line(ax, ay, bx, by, dx, dy) > 0)
		return false;
	if (side_of_line(cx, cy, dx, dy, ax, ay) * side_of_line(cx, cy, dx, dy, bx, by) > 0)
		return false;
	return true;
}

double calc_coeff(int i, int j, double deltax, double deltay)
{
	double ax, ay, bx, by, cx, cy, dx, dy;
	ax = obsx;
	ay = obsy;
	bx = v[i][0] + deltax;
	by = v[i][1] + deltay;
	cx = v[j][0];
	cy = v[j][1];
	dx = v[j+1][0];
	dy = v[j+1][1];
	return (ax * (dy - cy) + cx * (ay - dy) + dx * (cy - ay)) / (ax * (dy - cy) + bx * (cy - dy) + dx * (by - ay) + cx * (ay - by));
}

void check_visible()
{
	for (int i = 0; i < nv; i++)
	{
		int j;
		double deltax, deltay;
		int obs_side;
		obs_side = (side_of_line(v[i][0], v[i][1], v[i+1][0], v[i+1][1], obsx, obsy));
		deltax = (v[i+1][0] - v[i][0]) / 1000;
		deltay = (v[i+1][1] - v[i][1]) / 1000;
		double coeff, sectx, secty;
		for (j = 0; j < nv; j++)
		{
			if (j != i && intersect(obsx, obsy, v[i][0] + deltax, v[i][1] + deltay, v[j][0], v[j][1], v[j+1][0], v[j+1][1]))
			{
				coeff = calc_coeff(i, j, deltax, deltay);
				sectx = obsx + (v[i][0] + deltax - obsx) * coeff;
				secty = obsy + (v[i][1] + deltay - obsy) * coeff;
				if (side_of_line(v[i][0] + deltax , v[i][1] + deltay, v[i+1][0] - deltax, v[i+1][1] - deltay, sectx, secty) == obs_side)
					 break;
			}
		}
		if (j == nv)
		{
			visible[i] = 1;
			continue;
		}
		for (j = 0; j < nv; j++)
		{
			if (j != i && intersect(obsx, obsy, v[i+1][0] - deltax, v[i+1][1] - deltay, v[j][0], v[j][1], v[j+1][0], v[j+1][1]))
			{
				coeff = calc_coeff(i+1, j, -1 * deltax, -1 * deltay);
				sectx = obsx + (v[i+1][0] - deltax - obsx) * coeff;
				secty = obsy + (v[i+1][1] - deltay - obsy) * coeff;
				if (side_of_line(v[i][0] + deltax, v[i][1] + deltay, v[i+1][0] - deltax, v[i+1][1] - deltay, sectx, secty) == obs_side)
					break;
			}
		}
		if (j == nv)
			visible[i] = 1;
	}
}
				
				
int main()
{
	ofstream fout("fence4.out");
	ifstream fin("fence4.in");
	int i, j;
	fin >> nv >> obsx >> obsy;
	for (i = 0; i < nv; i++)
		fin >> v[i][0] >> v[i][1];
	v[nv][0] = v[0][0];
	v[nv][1] = v[0][1];
	for (i = 0; i < nv; i++)
		for (j = i + 2; j < nv; j++)
			if (intersect(v[i][0], v[i][1], v[i+1][0], v[i+1][1], v[j][0], v[j][1], v[j+1][0], v[j+1][1]) && !(i == 0 && j == nv - 1))
				break;
	if (i < nv)
		fout << "NOFENCE" << endl;
	else
	{
		check_visible();
		int count = 0;
		for (i = 0; i < nv; i++)
			if (visible[i])
				count++;
		fout << count << endl;
		for (i = 0; i < nv - 2; i++)
			if (visible[i])
				fout << v[i][0] << " " << v[i][1] << " " << v[i+1][0] << " " << v[i+1][1] << endl;
		if (visible[nv-1])
			fout << v[0][0] << " " << v[0][1] << " " << v[nv-1][0] << " " << v[nv-1][1] << endl;
		if (visible[nv-2])
			fout << v[nv-2][0] << " " << v[nv-2][1] << " " << v[nv-1][0] << " " << v[nv-1][1] << endl;
	}
}
