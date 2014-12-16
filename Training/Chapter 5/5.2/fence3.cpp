/*
ID: arpon.r1
PROG: fence3
LANG: C++
*/

#include <cstdio>
#include <cmath>
using namespace std;

FILE *fin = fopen ("fence3.in", "r"), *fout = fopen ("fence3.out", "w");

const int MAXF = 155;
const double radius [] = {20, 1, .5, .1, .05, .01}, pi = acos (-1);

int F;
double fences [MAXF][4], dx [8], dy [8];

void set_delta ()
{
	for (int i = 0; i < 8; i++)
	{
		dx [i] = cos (i * pi / 4);
		dy [i] = sin (i * pi / 4);
	}
}

double total (double x1, double y1)
{
	double sum = 0;
	
	for (int i = 0; i < F; i++)
	{
		double x2, y2;
		
		if (x1 < fences [i][0]) 
			x2 = fences [i][0];
		else if (x1 > fences [i][2])
			x2 = fences [i][2];
		else 
			x2 = x1;
		
		if (y1 < fences [i][1]) 
			y2 = fences [i][1];
		else if (y1 > fences [i][3])
			y2 = fences [i][3];
		else 
			y2 = y1;
		
		sum += sqrt ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	}
	
	return sum;
}

int main ()
{
	double x = 10, y = 10, d;
	
	fscanf (fin, "%d", &F);
	
	for (int i = 0; i < F; i++)
	{
		fscanf (fin, "%lf %lf %lf %lf", fences [i], fences [i] + 1, fences [i] + 2, fences [i] + 3);
		if (fences [i][2] < fences [i][0])
		{
			double tmp = fences [i][0];
			fences [i][0] = fences [i][2];
			fences [i][2] = tmp;
		}
		if (fences [i][3] < fences [i][1])
		{
			double tmp = fences [i][1];
			fences [i][1] = fences [i][3];
			fences [i][3] = tmp;
		}
	}
	
	d = total (x, y);
	set_delta ();
	
	for (int r = 0; r < 6; r++)
		for (int j = 0; j < 25; j++)
		{
			int best = -1;
			double tmp;
			
			for (int i = 0; i < 8; i++)
			{
				x += radius [r] * dx [i];
				y += radius [r] * dy [i];
				
				if ((tmp = total (x, y)) < d)
				{
					d = tmp;
					best = i;
				}
				
				x -= radius [r] * dx [i];
				y -= radius [r] * dy [i];
			}
			
			if (best != -1)
			{
				x += radius [r] * dx [best];
				y += radius [r] * dy [best];
			}
		}
	
	fprintf (fout, "%.1lf %.1lf %.1lf\n", x, y, d);
	return 0;
}


