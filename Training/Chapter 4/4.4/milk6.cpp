/*
 ID: arpon.r1
 PROG: milk6
 LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

FILE *fin = fopen ("milk6.in", "r"), *fout = fopen ("milk6.out", "w");

const int mxN = 32, mxM = 1000, INF = 1000000005;

int N, M, rt [mxM][3], src [mxN];
double cap [mxN][mxN], flow [mxN];
bool vis [mxN];

double augment ()
{
	double mx;
	int mloc, t;
	
	memset(flow, 0, sizeof (flow));
	memset(vis, 0, sizeof (vis));
	
	flow[0] = 2000000000 * 1000.0 + 1.0;
	while (1)
	{
		mloc = -1;
		mx = 0.9; 
		for (int i = 0; i < N; i++)
			if (!vis [i] && flow [i] > mx)
			{
				mx = flow [i];
				mloc = i;
			}
		
		if (mloc == -1) return -1;
		
		if (mloc == N - 1) break; 
		
		vis [mloc] = 1; 
		
		for (int i = 0; i < N; i++)
			if (cap [mloc][i] > flow [i] && mx > flow [i])
			{ 
				src [i] = mloc;
				
				flow [i] = cap [mloc][i];
				if (flow [i] > mx) flow [i] = mx;
			}
	}
	
	for (mloc = N - 1; mloc > 0; mloc = src [mloc])
	{
		t = src [mloc];
		
		cap [t][mloc] -= mx; 
		cap [mloc][t] += mx; 
	}
	
	return mx;
}


void flood (int loc)
{
	vis [loc] = true;
	
	for (int i = 0; i < N; i++)
		if (cap [loc][i] > 0 && !vis [i])
			flood (i);
}

int main ()
{
	fscanf (fin, "%d %d", &N, &M);
	
	for (int i = 0; i < M; i++) 
	{
		fscanf (fin, "%d %d %d", rt [i], rt [i] + 1, rt [i] + 2); 
		rt [i][0]--; rt [i][1]--;
		cap [rt [i][0]][rt [i][1]] += (1.0 + 1001.0 * rt [i][2]) * 500000.0 + i;
	}
	
	double flow = 0.0, aug;
	int real, shut = 0, dead [mxM];
	
	while ((aug = augment ()) > 0.0)
	{
		flow += aug;
		memset (vis, false, sizeof (vis));
	}
	real = (int) (flow / 500500000.0);
	
	memset (vis, false, sizeof (vis));
	flood (0);
	
	for (int i = 0; i < M; i++)
		if (vis [rt [i][0]] && !vis [rt [i][1]])
			dead [shut++] = i + 1;
	 
	fprintf (fout, "%d %d\n", real, shut);
	for (int i = 0; i < shut; i++)
		fprintf (fout, "%d\n", dead [i]);
	return 0;
}


