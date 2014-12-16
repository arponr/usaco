/*
 ID: arpon.r1
 PROG: calfflac
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

char file[20000], text[20000];
int flen = 0, tlen = 0, pStart, pEnd, tmpIndex, tmpIndex2, indexes[20000], greatest = 0;


void pal(int a, int b)
{
	while (a >= 0 && b < tlen)
	{
		if (text[a] != text[b])
			break;
		a--;
		b++;
	}
	if (b - a - 1 > greatest)
	{
		pStart = a + 1;
		pEnd = b - 1;
		greatest = (b - 1) - a;
	}
}

int maxPal()
{
	for (int x = 0; x < tlen - 1; x++)
	{
		if (text[x] == text[x+1])
			pal(x-1, x+2);
		else if(x+2 < tlen && text[x] == text[x+2])
			pal(x-1, x+3);
	}
	return greatest;
}

int main()
{
	ofstream fout("calfflac.out");
	ifstream fin("calfflac.in");
	char temp;
	while(fin.good())
	{
		temp = fin.get();
		if (isalpha(temp))
		{
			text[tlen] = tolower(temp);
			indexes[tlen] = flen;
			tlen++;
		}
		file[flen] = temp;
		flen++;
	}
	int pal = maxPal();
	string output;
	pStart = indexes[pStart];
	pEnd = indexes[pEnd];
	for (int x = pStart, y = 0; x <= pEnd; x++, y++)
	{
		output += file[x];
	}
	fout << pal << endl << output << endl;
	return 0;	
}