/*
 ID: arpon.r1
 PROG: namenum
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	ofstream fout("namenum.out");
	ifstream fin("namenum.in");
	ifstream din("dict.txt");
	string serial;
	char pad[256];
	pad['A'] = pad['B'] = pad['C'] = '2';
	pad['D'] = pad['E'] = pad['F'] = '3';
    pad['G'] = pad['H'] = pad['I'] = '4';
    pad['J'] = pad['K'] = pad['L'] = '5';
    pad['M'] = pad['N'] = pad['O'] = '6';
    pad['P'] = pad['R'] = pad['S'] = '7';
    pad['T'] = pad['U'] = pad['V'] = '8';
    pad['W'] = pad['X'] = pad['Y'] = '9';
	int valid = 0;
	fin >> serial;
	for (int x = 0; x < 4617; x++)
	{
		string temp;
		din >> temp;
		if (temp.length() == serial.length())
		{
			for (int y = 0; y < temp.length(); y++)
			{
				if (pad[temp.at(y)] != serial.at(y))
					break;
				else if (y == temp.length() - 1)
				{
					valid++;
					fout << temp << endl;
				}
			}
		}
	}
	if (valid == 0)
		fout << "NONE" << endl;
	fout.close();
	exit(0);
	return 0;
}
			