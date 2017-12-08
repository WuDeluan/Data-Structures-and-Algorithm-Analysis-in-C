#include <stdio.h>

typedef int ElementType;

//原始希尔排序
void ShellSort(ElementType A[], int N)
{
	int i, j, k,Increment;
	ElementType Tmp;
	for(Increment = N / 2;Increment > 0;Increment /= 2)
		for (i = Increment; i < N; i++)
		{
			Tmp = A[i];
			for (j = i; j >= Increment; j -= Increment)
				if (Tmp < A[j - Increment])
					A[j] = A[j - Increment];
				else
					
					break;
			A[j] = Tmp;
		}
}

//Hibbard增量序列
![](http://latex.codecogs.com/gif.latex?\\D^{k} = 2^{k} - 1
