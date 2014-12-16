/*
 ID: arpon.r1
 PROG: camelot
 LANG: C++
*/

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

#define INFINITY 32767
#define MAXK 780
#define MAXR 30
#define MAXC 26

typedef struct state state;
struct state
{
	short r, c, moves;
};

short knight_moves[8][2] = {{-2,1}, {-1,2}, {1,2}, {2,1}, {2,-1}, {1,-2}, {-1,-2}, {-2, -1}},
      king_moves[8][2] = {{-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}},
      king[2], knights[MAXK][2],
      king_dist[MAXR][MAXC], knight_dist[MAXR][MAXC][MAXR][MAXC],
      R, C, kcount;

void king_bfs()
{
	int read = 0, write = 1;
	state q[R * C], f;
	q[0].r = king[0]; 
	q[0].c = king[1];
	q[0].moves = 0;
	king_dist[king[0]][king[1]] = 0;
	while (read < write)
	{
		f = q[read++];
		for (int i = 0; i < 8; i++)
		{
			int newr = f.r + king_moves[i][0], newc = f.c + king_moves[i][1];
			if (newr >= 0 && newr < R && newc >= 0 && newc < C && king_dist[newr][newc] == INFINITY)
			{
				q[write].r = newr;
				q[write].c = newc;
				q[write++].moves = f.moves + 1;
				king_dist[newr][newc] = f.moves + 1;
			}
		}
	}
}

void knight_bfs(int r, int c)
{
	int read = 0, write = 1;
	state q[R * C], f;
	q[0].r = r; 
	q[0].c = c;
	q[0].moves = 0;
	knight_dist[r][c][r][c] = 0;
	while (read < write)
	{
		f = q[read++];
		for (int i = 0; i < 8; i++)
		{
			int newr = f.r + knight_moves[i][0], newc = f.c + knight_moves[i][1];
			if (newr >= 0 && newr < R && newc >= 0 && newc < C && knight_dist[r][c][newr][newc] == INFINITY)
			{
				q[write].r = newr;
				q[write].c = newc;
				q[write++].moves = f.moves + 1;
				knight_dist[r][c][newr][newc] = knight_dist[newr][newc][r][c] = f.moves + 1;
			}
		}
	}
}

int solve()
{
	int r, c, i, j, k, best = INFINITY;
	for (r = 0; r < R; r++)
	{
		for (c = 0; c < C; c++)
		{
			int cost = 0;
			for (i = 0; i < kcount; i++)
				cost += knight_dist[knights[i][0]][knights[i][1]][r][c];
			if (cost + king_dist[r][c] < best) 
				best = cost + king_dist[r][c];
			for (i = 0; i < kcount; i++)
			{
				int pickup = INFINITY;
				for (j = king[0] - 1; j <= king[0] + 1; j++)
					for (k = king[1] - 1; k <= king[1] + 1; k++)
						if (j >= 0 && j < R && k >= 0 && k < C && knight_dist[knights[i][0]][knights[i][1]][j][k] + knight_dist[j][k][r][c] + king_dist[j][k] < pickup)
							pickup = knight_dist[knights[i][0]][knights[i][1]][j][k] + knight_dist[j][k][r][c] + king_dist[j][k];
				cost += pickup - knight_dist[knights[i][0]][knights[i][1]][r][c];
				if (cost < best) 
					best = cost;
				cost -= pickup - knight_dist[knights[i][0]][knights[i][1]][r][c];
			}
		}
	}
	return best;
}

int main()
{
	ofstream fout("camelot.out");
	ifstream fin("camelot.in");
	int tmp2;
	char tmp1;
	fin >> R >> C >> tmp1 >> tmp2;
	king[0] = tmp2 - 1; king[1] = tmp1 - 'A';
	while (fin >> tmp1)
	{
		fin >> tmp2;
		knights[kcount][0] = tmp2 - 1;
		knights[kcount++][1] = tmp1 - 'A';
	}
	if (kcount > 0)
	{
		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
			{
				king_dist[i][j] = INFINITY;
				for (int k = 0; k < R; k++)
					for (int l = 0; l < C; l++)
						knight_dist[i][j][k][l] = INFINITY;
			}
		king_bfs();
		for (int i = 0; i < R; i++)
			for (int j = 0; j < C; j++)
				knight_bfs(i, j);
		fout << solve() << endl;
	}
	else
		fout << 0 << endl;
}
	