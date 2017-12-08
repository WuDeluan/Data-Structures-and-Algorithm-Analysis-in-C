#include <stdio.h>

typedef int ElementType;

void Swap(ElementType *a, ElementType *b)
{
	ElementType Tmp;
	Tmp = *a;
	*a = *b;
	*b = Tmp;
}
void CelecteSort(ElementType A[], int N)
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		int Min = i;
		for (j = i + 1; j < N; j++)
		{
			if (A[j] < A[Min])
				Min = j;
		}
		Swap(&A[Min], &A[i]);
	}
}

/*
  时间复杂度：O(N^2);
  稳定性：不稳定
*/
