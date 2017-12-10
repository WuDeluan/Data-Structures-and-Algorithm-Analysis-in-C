#include <stdio.h>

int MaxSubsequenceSum(int A[], int N)
{
	int ThisSum, MaxSum, j;
	ThisSum = MaxSum = 0;
	for (j = 0; j < N; j++)
	{
		ThisSum += A[j];
		if (ThisSum > MaxSum)
			MaxSum = ThisSum;
		else if (ThisSum < 0)
			ThisSum = 0;
	}
	return MaxSum;
}

int main()
{
	int A[] = { 4,-3,5,2,-1,2,6,-2 };
	printf("%d\n", MaxSubsequenceSum(A, 8));
}
