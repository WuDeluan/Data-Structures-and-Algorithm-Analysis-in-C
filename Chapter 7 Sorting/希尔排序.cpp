#include <stdio.h>
#include <math.h>

typedef int ElementType;

/*
  原始希尔排序
  增量元素不互质，则小增量可能根本不起作用
 */
void ShellSort0(ElementType A[], int N)
{
	int i, j, Increment;
	ElementType Tmp;
	for(Increment = N / 2;Increment > 0;Increment /= 2)
	{
		for (i = Increment; i < N; i++)            //插入排序
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
}

/*Hibbard增量序列  
  Dk = 2^k - 1 —— 相邻元素互质
  {1，3，7，15，31，...}
*/
double log2(double input)
{
	return log(input) / log(2);
}

void ShellSort1(ElementType A[], int N)
{
	int i, j, k, Round, Increment;
	ElementType Tmp;
	for (Round = (int)log2(N); Round > 0; Round--)
	{
		Increment = (int)pow(2, Round) - 1;                //根据公式，计算Hibbard增量
		for (i = Increment; i < N; i++)                    //插入排序
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
}

/*Sedgewick增量序列
  9 * 4^i - 9 * 2^i + 1 或 4^i - 3 * 2^i - 1
  {1,5,19,41,109,...}
*/
void ShellSort2(ElementType A[], int N)
{
	int i, j, k, Increment;
	ElementType Tmp;
	int Sedgewick[] = { 929, 505, 209, 109, 41, 19, 5, 1, 0 };  // 这里只列出一小部分增量

	for (k = 0; Sedgewick[k] >= N; k++)
		;                               // 初始的增量Sedgewick[Si]不能超过待排序列长度 
	for (Increment = Sedgewick[k]; Increment > 0; Increment = Sedgewick[++k])
	{
		for (i = Increment; i < N; i++)                    //插入排序
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
}


/*
  时间复杂度：O(N^d),视增量的选择而定
  稳定性：不稳定
*/
