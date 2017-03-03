// homework.cpp : for Zheda data structure open course.
//

#include "stdafx.h"

#include <iostream>
#include <vector>

int Max3(int A, int B, int C) 
{
	/* return the maximum number among this 3 number*/
	return A > B ? (A > C ? A : C) : (B > C ? B : C);
}

int DivideAndConquer(const std::vector<int> &List, int left, int right)
{
	// get the maximum subsequence from left to right using divide and conquer

	if (left == right)
		if (List[left] > 0) 
			return List[left];
		else 
			return 0;

	int center = (left + right) / 2;
	int MaxLeftSum = DivideAndConquer(List, left, center);
	int MaxRightSum = DivideAndConquer(List, center + 1, right);

	int MaxLeftBorderSum = 0, LeftBorderSum = 0;
	for (int i = center; i >= left; i--)
	{
		LeftBorderSum += List[i];
		if (LeftBorderSum > MaxLeftBorderSum)
			MaxLeftBorderSum = LeftBorderSum;
	}

	int MaxRightBorderSum = 0, RightBorderSum = 0;
	for (int j = center+1; j <= right ; j++)
	{
		RightBorderSum += List[j];
		if (RightBorderSum > MaxRightBorderSum)
			MaxRightBorderSum = RightBorderSum;
	}
	return Max3(MaxLeftSum, MaxRightSum, MaxLeftBorderSum + MaxRightBorderSum);
}

int MaxSubseqSum3(const std::vector<int> & a, int N)
{
	return DivideAndConquer(a, 0, N - 1);
}
int test()
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

	int sum = MaxSubseqSum3(DataList, DataNumber);
	std::cout << sum << std::endl;

    return 0;
}

