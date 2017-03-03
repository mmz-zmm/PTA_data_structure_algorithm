// homework.cpp : for Zheda data structure open course.
//

#include "stdafx.h"

#include <iostream>
#include <vector>


int MaxSubseqSum3(const std::vector<int> & a, int &LeftMark, int &RightMark)
{
	int MaxSum = 0, ThisSum = 0;
	int LeftMark2 = 0;
	int NegativeNum = 0;
	std::vector<int> b;

	for (int j = 0; j < a.size(); j++)
	{
		ThisSum += a[j];

		if (a[j] == 0)
			b.push_back(j);
		else if(a[j] < 0)
			NegativeNum++;

		if ( ThisSum > MaxSum)
		{
			MaxSum = ThisSum;
			LeftMark = LeftMark2;
			RightMark = j;

		}
		else if(ThisSum < 0)
		{
			ThisSum = 0;
			LeftMark2 = j + 1;
		}
	}

	if (MaxSum == 0) 
	{
		if (NegativeNum == a.size())
		{
			LeftMark = 0;
			RightMark = a.size() - 1;
		}
		else
		{
			LeftMark = RightMark = b[0];
		}
	}

	return MaxSum;
}

// return the max subsequence sum and the left and right boundary element.
int main()
{
	int DataNumber;
	std::vector<int> DataList;

	//
	std::cin >> DataNumber;



	for (int val = 0; val < DataNumber; ++val)
	{
		int temp;
		std::cin >> temp;
		DataList.push_back(temp);
	}
	
	int LeftMark = 0, RightMark = 0;
	int sum = MaxSubseqSum3(DataList, LeftMark, RightMark);
	std::cout << sum <<' '<< DataList[LeftMark]<<' ' << DataList[RightMark]<<std::endl;

	return 0;
}

