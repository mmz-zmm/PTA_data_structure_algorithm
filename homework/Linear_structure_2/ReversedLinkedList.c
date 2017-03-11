#include <stdio.h>
#include <stdlib.h>

//Given a constant KK and a singly linked list LL, you are supposed to reverse the links of every KK elements on LL. For example, given LL being 1¡ú2¡ú3¡ú4¡ú5¡ú6, if K = 3K=3, then you must output 3¡ú2¡ú1¡ú6¡ú5¡ú4; if K = 4K=4, you must output 4¡ú3¡ú2¡ú1¡ú5¡ú6.

typedef struct Link * pLink;
struct Link
{
	int address;
	int value;
	int NextAddress;
	pLink next;
};
void LinkAdd(int address, int value,int NextAddress, pLink *tail);
pLink LinkReversed(pLink Link1, int N, int K);
void LinkPrint(pLink Link1);
pLink LinkRead();

int K;
int N;
int HeadAddress;


int ReversedLinkedList()
//int main()
{
	pLink link1, link2;
	link1 = LinkRead();
	link2 = LinkReversed(link1, N, K);
	LinkPrint(link2);

	return 0;
}
void LinkPrint(pLink Link1)
{
	while (Link1)
	{
		if (Link1->NextAddress == -1)
			printf("%05d %d %d\n", Link1->address, Link1->value, Link1->NextAddress);
		else
			printf("%05d %d %05d\n", Link1->address, Link1->value, Link1->NextAddress);
		Link1 = Link1->next;
	}
}

pLink LinkRead()
{
	pLink head, tail, temp;
	int address, value, NextAddress;
	int i;
	FILE *f1;
	fopen_s(&f1, "test.txt", "r");


	head = (pLink)malloc(sizeof(struct Link));
	head->next = NULL;
	tail = head;
	//scanf_s("%05d %d %d", &HeadAddress, &N, &K);
	fscanf_s(f1, "%05d %d %d", &HeadAddress, &N, &K);
	for (i = 0; i < N; i++)
	{
		//scanf_s("%05d %d %05d", &address, &value, &NextAddress);
		fscanf_s(f1, "%05d %d %05d", &address, &value, &NextAddress);
		LinkAdd(address, value, NextAddress, &tail);

	}
	fclose(f1);
	// sort the linked list
	pLink psorted, p1, p2;
	int AimAddress;
	int number = 0;
	psorted = head;
	p1 = head;
	p2 = p1->next;
	AimAddress = HeadAddress;
	for (i = 0; i < N; i++)
	{
		if (AimAddress == -1)
			break;
		else if (p2->address == AimAddress)  // already sorted
		{
			psorted = p2;
			AimAddress = p2->NextAddress;
			p1 = psorted;
			p2 = p1->next;
		}
		else
		{
			while (p2)
			{
				if (p2->address == AimAddress)
				{
					p1->next = p2->next;
					p2->next = psorted->next;
					psorted->next = p2;
					psorted = p2;
					AimAddress = p2->NextAddress;
					p1 = psorted;
					p2 = p1->next;
					break;
				}
				else
				{
					p1 = p2;
					p2 = p1->next;
				}
			}
		}
		number++;
	}
	if (number != N)  // actual node number is different from real node number
	{
		psorted->next = NULL;
		N = number;
	}	

	temp = head;
	head = head->next;
	free(temp);
	return head;
}

pLink LinkReversed(pLink Link1, int N, int K)
{
	pLink head, sorted, p1, p2, temp;
	head = (pLink)malloc(sizeof(struct Link));
	head->next = Link1;
	sorted = head;

	p1 = sorted->next;
	p2 = p1->next;

	if (N == 1 || K > N) return Link1;

	int NR = (int)N / K;

	if (NR)
	{
		if (NR == N) return Link1;   // K == 1

		for (int i = 0; i < NR; i++)
		{
			int j = 1;
			while (j < K)
			{
				if (p2->NextAddress == -1)
				{
					p1->next = p2->next;
					p1->NextAddress = p2->NextAddress;
				}
				else
				{
					p1->next = p2->next;
					p1->NextAddress = p2->next->address;
				}
				p2->next = sorted->next;
				p2->NextAddress = sorted->next->address;
				sorted->next = p2;
				sorted->NextAddress = p2->address;
				p2 = p1->next;
				if (p2)
					j++;
				else
					break;

			}
			if (p2 == NULL) break;
			sorted = p1;
			p1 = p1->next;
			p2 = p1->next;
		}
	}
	else
		return Link1;

	temp = head;
	head = head->next;
	free(temp);
	return head;

}

void LinkAdd(int address, int value, int NextAddress, pLink *tail)
{
	pLink P;

	P = (pLink)malloc(sizeof(struct Link));
	P->address = address;
	P->value = value;
	P->NextAddress = NextAddress;
	P->next = NULL;

	(*tail)->next = P;
	*tail = P;
}
