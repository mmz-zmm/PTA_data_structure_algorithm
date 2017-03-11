#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//Given a stack which can keep MM numbers at most. Push NN numbers in the order of 1, 2, 3, ..., NN and pop randomly. You are supposed to tell if a given sequence of numbers is a possible pop sequence of the stack. For example, if MM is 5 and NN is 7, we can obtain 1, 2, 3, 4, 5, 6, 7 from the stack, but not 3, 2, 1, 7, 5, 6, 4.
typedef int Position;
typedef int ElementType;

ElementType ERROR = -10;

struct Snode
{
	ElementType * Data;
	Position Top;
	int MaxSize;
};
typedef struct Snode * Stack;

Stack CreateStack(int MaxSize)
{
	Stack S = (Stack)malloc(sizeof(struct Snode));
	S->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
	S->Top = -1;
	S->MaxSize = MaxSize;
	return S;
}
bool IsFull(Stack S)
{
	return (S->Top == S->MaxSize - 1);
}
bool IsEmpty(Stack S)
{
	return (S->Top == - 1);
}
bool Push(Stack S, ElementType X)
{
	if (IsFull(S))
		return false;
	else
	{
		S->Data[++(S->Top)] = X;
		return true;
	}
}

ElementType Pop(Stack S)
{
	if (IsEmpty(S))
		return ERROR;
	else
	{
		return S->Data[(S->Top)--];
	}
}

bool PopSequence(FILE *f1, int M, int N);

void PopSequences()
{
	int M, N, Nseq;
	FILE *f1;
	
	bool IsPop;


	fopen_s(&f1, "test2.txt", "r");
	fscanf_s(f1,"%d %d %d", &M, &N, &Nseq);

	for (int i = 0; i < Nseq; i++)
	{
		IsPop = PopSequence(f1, M, N);
		if (IsPop)
			printf("YES\n");
		else
			printf("NO\n");
	}
	fclose(f1);
}

bool PopSequence(FILE *f1, int M, int N)
{
	int value, TempValue, MaxValue;
	Stack S;
	int *TempData;
	TempData = (int*)malloc(N * sizeof(int));

	TempValue = 0;
	MaxValue = 0;
	S = CreateStack(M);
	for (int j = 0; j < N; j++)
	{
		fscanf_s(f1, "%d", &TempData[j]);
	}
	for(int j = 0; j < N; j++)
	{
		value = TempData[j];
		if (j == 0)  // first data
		{
			if (value > M)
			{
				return false;
			}
			else
			{
				for (int k = 1; k <= value; k++)
					Push(S, k);
				Pop(S);
			}
			//TempValue = value;
		}
		else  // other data
		{
			if (value > TempValue)
			{
				if (MaxValue == N)
				{
					return false;
				}
				for (int k = MaxValue + 1; k <= value; k++)
				{
					if (!Push(S, k))
					{
						return false;
					}
				}
				Pop(S);
			}
			else if (value < TempValue)
			{
				while (1)
				{
					ElementType a = Pop(S);
					if (a == ERROR)
					{
						return false;
					}
					else if (a == value)
						break;
				}
			}
		}
		if (value > MaxValue) MaxValue = value; // record the current position
		TempValue = value;
	}
	free(TempData);
	free(S->Data);
	free(S);
	return true;

}

int main()
{
	PopSequences();
	return 0;
}