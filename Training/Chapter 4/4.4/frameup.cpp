/*
 ID: arpon.r1
 PROG: frameup
 LANG: C++
*/

#include <iostream>
#include <fstream>
#define MAXLEN 30
#define NUMLTRS 26

using namespace std;

char pic[MAXLEN][MAXLEN + 1], cur[NUMLTRS + 1];
int H, W, nframes, frame[NUMLTRS][4];  //miny, minx, maxy, maxx
bool in [NUMLTRS], above[NUMLTRS][NUMLTRS];
FILE *fout = fopen("frameup.out", "w");

void define(int r, int c, char l)
{
	int i = l - 'A';
	if (!in [i])
	{
		in [i] = true;
		nframes++;
	}
	if (r < frame[i][0] || frame[i][0] == -1) frame[i][0] = r;
	if (r > frame[i][2] || frame[i][2] == -1) frame[i][2] = r;
	if (c < frame[i][1] || frame[i][1] == -1) frame[i][1] = c;
	if (c > frame[i][3] || frame[i][3] == -1) frame[i][3] = c;
}

void order(int l)
{
	for (int i = frame[l][0]; i <= frame[l][2]; i++)
	{
		if (pic[i][frame[l][1]] - 'A' != l)
			above[pic[i][frame[l][1]] - 'A'][l] = 1;
		if (pic[i][frame[l][3]] - 'A' != l)
			above[pic[i][frame[l][3]] - 'A'][l] = 1;
	}
	for (int i = frame[l][1]; i <= frame[l][3]; i++)
	{
		if (pic[frame[l][0]][i] - 'A' != l)
			above[pic[frame[l][0]][i] - 'A'][l] = 1;
		if (pic[frame[l][2]][i] - 'A' != l)
			above[pic[frame[l][2]][i] - 'A'][l] = 1;
	}
}

void build (int depth)
{
	if (depth == nframes)
	{
		cur[nframes] = '\0';
		fprintf (fout, "%s\n", cur);
		return;
	}
	for (int i = 0; i < NUMLTRS; i++)
		if (in [i])
		{
			int j;
			for (j = 0; j < NUMLTRS; j++)
				if (in [j] && above[i][j])
					break;
			if (j == NUMLTRS)
			{
				cur[depth] = (char)('A' + i);
				in [i] = 0;
				build(depth + 1);
				in [i] = 1;
			}
		}
}

int main()
{
	ifstream fin("frameup.in");
	int i, j;
	fin >> H >> W;
	fin.get();
	for (i = 0; i < H; i++)
		fin.getline(pic[i], W + 1);
	memset(frame, -1, sizeof(frame));
	for (i = 0; i < H; i++)
		for (j = 0; j < W; j++)
			if (pic [i][j] != '.')
				define(i, j, pic[i][j]);
	for (i = 0; i < NUMLTRS; i++)
		if (in [i])
			order (i);
	build (0);
}
	
