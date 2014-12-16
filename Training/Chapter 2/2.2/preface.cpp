/*
 ID: arpon.r1
 PROG: preface
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int to[256], cnts[256];
char map[1001];
string ones[10] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

void digit(int n, int mult)
{
	for (int i = 0; i < ones[n].length(); i++)
		cnts[map[(to[ones[n].at(i)] * mult)]]++;
}

void solve(int num)
{
	digit(num/1000, 1000);
	digit(num/100 % 10, 100);
	digit(num/10 % 10, 10);
	digit(num % 10, 1);
}

int main()
{
	ofstream fout("preface.out");
	ifstream fin("preface.in");
	map[1] = 'I'; map[5] = 'V'; map[10] = 'X'; map[50] = 'L'; map[100] = 'C'; map[500] = 'D'; map[1000] = 'M';
	to['I'] = 1; to['V'] = 5; to['X'] = 10; to['L'] = 50; to['C'] = 100; to['D'] = 500; to['M'] = 1000;
	cnts['I'] = 0; cnts['V'] = 0; cnts['X'] = 0; cnts['L'] = 0; cnts['C'] = 0; cnts['D'] = 0; cnts['M'] = 0;
	int N;
	fin >> N;
	for (int i = 1; i <= N; i++)
		solve(i);
	if (cnts['I'])
		fout << "I" << " " << cnts['I'] << endl;
	if (cnts['V'])
		fout << "V" << " " << cnts['V'] << endl;
	if (cnts['X'])
		fout << "X" << " " << cnts['X'] << endl;
	if (cnts['L'])
		fout << "L" << " " << cnts['L'] << endl;
	if (cnts['C'])
		fout << "C" << " " << cnts['C'] << endl;
	if (cnts['D'])
		fout << "D" << " " << cnts['D'] << endl;
	if (cnts['M'])
		fout << "M" << " " << cnts['M'] << endl;
	return 0;
}