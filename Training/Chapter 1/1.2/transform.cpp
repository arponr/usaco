/*
 ID: arpon.r1
 PROG: transform
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct board
{
	int n;
	char b[10][10];
};

board rot(board input)
{
	board temp;
	temp = input;
	for (int x = 0; x < input.n; x++)
	{
		int z = input.n;
		for (int y = 0; y < input.n; y++)
		{
			z--;
			temp.b[y][x] = input.b[x][z];
		}
	}
	return temp;
}

board refl(board input)
{
	board temp;
	temp = input;
	for (int x = 0; x < input.n; x++)
	{
		int z = input.n;
		for (int y = 0; y < input.n; y++)
		{
			temp.b[y][x] = input.b[z - y - 1][x];
		}
	}
	return temp;
}

bool eq(board a, board b)
{
	for (int x = 0; x < a.n; x++)
	{
		for (int y = 0; y < a.n; y++)
		{
			if (a.b[y][x] != b.b[y][x])
				return false;
		}
	}
	return true;
}

int main()
{
	ofstream fout("transform.out");
	ifstream fin("transform.in");
	int n, change;
	fin >> n;
	board board1, board2;
	board1.n = n;
	board2.n = n;
	for (int i = 0; i < n; i++)
	{
		string temp;
		fin >> temp;
		for (int j = 0; j < n; j++)
			board1.b[j][i] = temp.at(j);
	}
	for (int i = 0; i < n; i++)
	{
		string temp;
		fin >> temp;
		for (int j = 0; j < n; j++)
			board2.b[j][i] = temp.at(j);
	}
	if (eq(rot(board1), board2))
		change = 1;
	else if (eq(rot(rot(board1)), board2))
		change = 2;
	else if (eq(rot(rot(rot(board1))), board2))
		change = 3;
	else if (eq(refl(board1), board2))
		change = 4;
	else if (eq(refl(rot(board1)), board2) || eq(refl(rot(rot(board1))), board2) || eq(refl(rot(rot(rot(board1)))), board2))
		change = 5;
	else if (eq(board1,  board2))
		change = 6;
	else
		change = 7;
	fout << change << endl;
	exit(0);
	return 0;
}
