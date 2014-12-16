/*
 ID: !cowlovers
 LANG: C++
 TASK: perlbrac
 */

#include <iostream>
#include <vector>

using namespace std;

int necklace[20000], max_necklace[20000], neck_i = 0;
int max_len = 0, modNum;
	
bool canAdd(int nextNum)
{
	necklace[neck_i++] = nextNum;
	for (int x = 1; x < neck_i; x++)
	{
		int rightNum = 0;
		int leftNum = 0;
		for (int y = 0; y <= x && x+y+1 < neck_i; y++)
		{
			leftNum += necklace[x-y];
			rightNum += necklace[x+y+1];
			if (leftNum % modNum == rightNum % modNum)
			{
				neck_i--;
				return false;
			}
		}
	}
	neck_i--;
	return true;
}

void addNum()
{
	if (neck_i == 20000)
		return;
	for (int x = 0; x < modNum; x++)
	{
		if (neck_i > 0 && x == necklace[neck_i - 1])
			continue;
		if (neck_i == 0 || canAdd(x))
		{
			necklace[neck_i++] = x;
			if (neck_i > max_len)
			{
				max_len = neck_i;
				cout << "Intermediate: " << max_len << endl;
				for (int i = 0; i < neck_i; i++)
				{
					max_necklace[i] = necklace[i];
					cout << max_necklace[i] << endl;
				}
				cout << endl;
			}
			addNum();
			neck_i--;
		}
	}
}


int main() 
{
	int taskNum;
	cin >> taskNum >> modNum;
	addNum();
	cout << "#FILE perlbrac " << taskNum << endl;
	cout << max_len << endl;
	for (int x = 0; x < max_len; x++)
		cout << max_necklace[x] << endl;
}
		
		 
	