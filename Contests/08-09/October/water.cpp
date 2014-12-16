/*
 ID: arpon.r1
 PROG: water
 LANG: C++
 */
#include <cstdio>
#include <queue>
using namespace std;

FILE *fin = fopen ("water.in", "r"), *fout = fopen ("water.out", "w");

const int MAXN = 305, MAXE = 2 * MAXN * MAXN, INF = 1000000005;

struct state
{
	int num, dist;
	
	inline bool operator < (const state &o) const
	{
		return dist > o.dist;
	}
};

int N, E, dist [MAXN];
int eadj [MAXE], elen [MAXE], enext [MAXE], elast [MAXN];
bool done [MAXN];
priority_queue <state> pq; 

void addedge (int e, int a, int b, int len)
{
	eadj [e] = b; elen [e] = len; enext [e] = elast [a]; elast [a] = e;
}

int mst ()
{
	memset (dist, INF, sizeof (dist));
	int total = 0;
	
	pq.push ((state) {0, 0});
	
	while (!pq.empty ())
	{
		state top = pq.top (); pq.pop ();
		
		if (done [top.num]) 
			continue;
		
		done [top.num] = true;
		total += top.dist;
		
		for (int i = elast [top.num]; i != -1; i = enext [i])
			if (!done [eadj [i]] && elen [i] < dist [eadj [i]])
				pq.push ((state) {eadj [i], dist [eadj [i]] = elen [i]});
	}
	
	return total;
}

int main ()
{
	memset (elast, -1, sizeof (elast));
	fscanf (fin, "%d", &N);
	
	for (int i = 1, d; i <= N; i++)
	{
		fscanf (fin, "%d", &d);
		addedge (E++, 0, i, d);
	}
	
	for (int i = 1, d; i <= N; i++) 
		for (int j = 1; j <= N; j++) 
		{
			fscanf (fin, "%d", &d); 
			addedge (E++, i, j, d);
			addedge (E++, j, i, d);
		}
	
	fprintf (fout, "%d\n", mst ());
	return 0;
}
	