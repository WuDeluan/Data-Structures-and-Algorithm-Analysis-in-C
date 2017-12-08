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
<img src="http://latex.codecogs.com/gif.latex?\frac{\partial J}{\partial \theta_k^{(j)}}=\sum_{i:r(i,j)=1}{\big((\theta^{(j)})^Tx^{(i)}-y^{(i,j)}\big)x_k^{(i)}}+\lambda \theta_k^{(j)}" />  

