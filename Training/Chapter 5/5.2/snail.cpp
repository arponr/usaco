/*
ID: arpon.r1
PROG: snail
LANG: C++
*/

#include <cstdio>
#include <cstring>
using namespace std;

FILE *fin = fopen ("snail.in", "r"), *fout = fopen ("snail.out", "w");

const int MAXN = 125;

int N, B, best, len;
bool grid [MAXN][MAXN], vis [MAXN][MAXN];

bool valid (int x, int y)
{
	return (x >= 0 && x < N && y >= 0 && y < N);
}

void dfs (int x, int y, int dx, int dy)
{	
	if (vis [x][y])
	{
		if (len > best) best = len;
		return;
	}
	
	vis [x][y] = true;
	len++;
	
	if (!valid (x + dx, y + dy) || !grid [x + dx][y + dy])
	{
		if (len > best) best = len;
		
		dx = !dx; dy = !dy;
		if (valid (x + dx, y + dy) && grid [x + dx][y + dy])
			dfs (x + dx, y + dy, dx, dy);
		if (valid (x - dx, y - dy) && grid [x - dx][y - dy])
			dfs (x - dx, y - dy, -dx, -dy);
	}
	else 
		dfs (x + dx, y + dy, dx, dy);
		
	vis [x][y] = false;
	len--;
}

int main ()
{
	fscanf (fin, "%d %d", &N, &B);
	memset (grid, true, sizeof (grid));
	
	for (int i = 0; i < B; i++)
	{
		char a; int b;
		fscanf (fin, "\n%c%d", &a, &b);
		grid [a - 'A'][b - 1] = false;
	}
	
	dfs (0, 0, 1, 0);
	dfs (0, 0, 0, 1);
	
	fprintf (fout, "%d\n", best);
	return 0;
}


