/*
 ID: arpon.r1
 PROG: comehome
 LANG: C++
 */

#include <iostream>
#include <fstream>

using namespace std;

int conv[256];
int adj[52][52], dijkstra[52][2];
bool visited[52];

void make_indicies()
{
	conv['A'] = 0; conv['a'] = 26; 
	conv['B'] = 1; conv['b'] = 27;
	conv['C'] = 2; conv['c'] = 28;
	conv['D'] = 3; conv['d'] = 29;
	conv['E'] = 4; conv['e'] = 30;
	conv['F'] = 5; conv['f'] = 31;
	conv['G'] = 6; conv['g'] = 32;
	conv['H'] = 7; conv['h'] = 33;
	conv['I'] = 8; conv['i'] = 34;
	conv['J'] = 9; conv['j'] = 35;
	conv['K'] = 10; conv['k'] = 36;
	conv['L'] = 11; conv['l'] = 37;
	conv['M'] = 12; conv['m'] = 38;
	conv['N'] = 13; conv['n'] = 39;
	conv['O'] = 14; conv['o'] = 40;
	conv['P'] = 15; conv['p'] = 41;
	conv['Q'] = 16; conv['q'] = 42;
	conv['R'] = 17; conv['r'] = 43;
	conv['S'] = 18; conv['s'] = 44;
	conv['T'] = 19; conv['t'] = 45;
	conv['U'] = 20; conv['u'] = 46;
	conv['V'] = 21; conv['v'] = 47;
	conv['W'] = 22; conv['w'] = 48;
	conv['X'] = 23; conv['x'] = 49;
	conv['Y'] = 24; conv['y'] = 50;
	conv['Z'] = 25; conv['z'] = 51;
}

int shortest_path()
{
	int mino, j;
	for (int i = 0; i < 52; i++)
	{
		mino = 100000001, j = 25;
		for (int k = 0; k < 52; k++)
		{
			if (dijkstra[k][0] < mino && !visited[k])
			{
				mino = dijkstra[k][0];
				j = k;
			}
		}
		visited[j] = true;
		for (int m = 0; m < 52; m++)
			if (adj[j][m] < 10001 && dijkstra[j][0] + adj[j][m] < dijkstra[m][0])
			{
				dijkstra[m][0] = dijkstra[j][0] + adj[j][m];
				dijkstra[m][1] = j;
			}
	}
	mino = 100000001;
	for (int x = 0; x < 25; x++)
		if (dijkstra[x][0] < mino)
		{
			mino = dijkstra[x][0];
			j = x;
		}
	return j;
}

int main()
{
	ofstream fout("comehome.out");
	ifstream fin("comehome.in");
	make_indicies();
	int paths;
	fin >> paths;
	for (int a = 0; a < 52; a++)
	{
		for (int b = 0; b < 52; b++)
		{
			adj[a][b] = 10001;
			adj[a][b] = 10001;
		}
	}
	for (int x = 0; x < 52; x++)
	{
		visited[x] = false;
		dijkstra[x][0] = 100000000;
		dijkstra[x][1] = 0;
	}
	dijkstra[25][0] = 0;
	for (int x = 0; x < paths; x++)
	{
		char a, b;
		int c;
		fin >> a >> b >> c;
		if (c < adj[conv[a]][conv[b]])
		{
			adj[conv[a]][conv[b]] = c;
			adj[conv[b]][conv[a]] = c;
		}
	}
	int out = shortest_path();
	cout << adj[17][25];
	switch(out)
	{
		case 0:
		{
			fout << 'A' << " " << dijkstra[out][0] << endl;
			break;
		}
		case 1:
		{
			fout << 'B' << " " << dijkstra[out][0] << endl;
			break;
		}
		case 2:
		{
			fout << 'C' << " " << dijkstra[out][0] << endl;
			break;
		}
		case 3:
		{
			fout << 'D' << " " << dijkstra[out][0] << endl;
			break;
		}
		case 4:
		{
			fout << 'E' << " " << dijkstra[out][0] << endl;
			break;
		}
		case 5:
		{
			fout << 'F' << " " << dijkstra[out][0] << endl;
			break;
		}
		case 6:
		{
			fout << 'G' << " " << dijkstra[out][0] << endl;
			break;
		}
		case 7:
		{
			fout << 'H' << " " << dijkstra[out][0] << endl;
			break;
		}
		case 8:
		{
			fout << 'I' << " " << dijkstra[out][0] << endl;
			break;
		}
		case 9:
		{
			fout << 'J' << " " << dijkstra[out][0] << endl;
			break;
		}
		case 10:
		{
			fout << 'K' << " " << dijkstra[out][0] << endl;
			break;
		}
		case 11:
		{
			fout << 'L' << " " << dijkstra[out][0] << endl;
			break;
		}
		case 12:
		{
			fout << 'M' << " " << dijkstra[out][0] << endl;
			break;
		}
		case 13:
		{
			fout << 'N' << " " << dijkstra[out][0] << endl;
			break;
		}
		case 14:
		{
			fout << 'O' << " " << dijkstra[out][0] << endl;
			break;
		}
		case 15:
		{
			fout << 'P' << " " << dijkstra[out][0] << endl;
			break;
		}
		case 16:
		{
			fout << 'Q' << " " << dijkstra[out][0] << endl;
			break;
		}
		case 17:
		{
			fout << 'R' << " " << dijkstra[out][0] << endl;
			break;
		}
		case 18:
		{
			fout << 'S' << " " << dijkstra[out][0] << endl;
			break;
		}
		case 19:
		{
			fout << 'T' << " " << dijkstra[out][0] << endl;
			break;
		}
		case 20:
		{
			fout << 'U' << " " << dijkstra[out][0] << endl;
			break;
		}
		case 21:
		{
			fout << 'V' << " " << dijkstra[out][0] << endl;
			break;
		}
		case 22:
		{
			fout << 'W' << " " << dijkstra[out][0] << endl;
			break;
		}
		case 23:
		{
			fout << 'X' << " " << dijkstra[out][0] << endl;
			break;
		}
		case 24:
		{
			fout << 'Y' << " " << dijkstra[out][0] << endl;
			break;
		}
	}
}
