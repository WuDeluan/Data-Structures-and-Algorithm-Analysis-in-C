//平方探测为加减i ^ 2
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXTABLESIZE 100000 // 允许开辟的最大散列表长度 
typedef int ElementType;    // 关键词类型用整型 
typedef int Index;          // 散列地址类型 
typedef Index Position;     // 数据所在位置与散列地址是同一类型 

// 散列单元状态类型，分别对应：有合法元素、空单元、有已删除元素
typedef enum { Legitimate, Empty, Deleted } EntryType;   //注意这里使用逗号！！！

// 散列表单元类型
typedef struct HashEntry {
	ElementType Data; // 存放元素 
	EntryType Info;   // 单元状态 
}Cell;                

// 散列表类型
typedef struct TableNode {   // 散列表结点定义 
	int TableSize;         // 表的最大长度 
	Cell *TheCells;           // 存放散列单元数据的数组 
}*HashTable;                

// 返回大于N且不超过MAXTABLESIZE的最小素数
int NextPrime(int N)
{                   
	int i, p = (N % 2) ? N + 2 : N + 1; //从大于N的下一个奇数开始

	while (p <= MAXTABLESIZE) {
		for (i = (int)sqrt(p); i>2; i--)
			if (!(p%i)) break;      // p不是素数
		if (i == 2) break;          // for正常结束，说明p是素数 
		else  p += 2;               // 否则试探下一个奇数
	}
	return p;
}

HashTable CreateTable(int TableSize)
{
	HashTable H;
	int i;

	H = (HashTable)malloc(sizeof(TableNode));
	// 保证散列表最大长度是素数
	H->TableSize = NextPrime(TableSize);
	// 声明单元数组
	H->TheCells = (Cell *)malloc(H->TableSize * sizeof(Cell));
	// 初始化单元状态为“空单元” 
	for (i = 0; i<H->TableSize; i++)
		H->TheCells[i].Info = Empty;

	return H;
}

//哈希函数
int Hash(ElementType Key, int TableSize)
{
	return (int)Key % 13;
}

Position Find(HashTable H, ElementType Key)
{
	Position CurrentPos, NewPos;
	int CNum = 0;          // 记录冲突次数

	NewPos = CurrentPos = Hash(Key, H->TableSize); // 初始散列位置 
    // 当该位置的单元非空，并且不是要找的元素时，发生冲突
	while (H->TheCells[NewPos].Info != Empty && H->TheCells[NewPos].Data != Key) {
		// 字符串类型的关键词需要 strcmp 函数!!
		// 统计1次冲突，并判断奇偶次 
		//下列代码分别使用两种方式调整地址
		if (++CNum % 2) { // 奇数次冲突
			NewPos = CurrentPos + (CNum + 1)*(CNum + 1) / 4; // 增量为+[(CNum+1)/2]^2
			if (NewPos >= H->TableSize)
				NewPos = NewPos % H->TableSize; // 调整为合法地址
		}
		else {    // 偶数次冲突
			NewPos = CurrentPos - CNum * CNum / 4; // 增量为-(CNum/2)^2
			while (NewPos < 0)
				NewPos += H->TableSize;    // 调整为合法地址 
		}
	}
	return NewPos; // 此时NewPos或者是Key的位置，或者是一个空单元的位置（表示找不到）
}

bool Insert(HashTable H, ElementType Key)
{
	Position Pos = Find(H, Key); // 先检查Key是否已经存在

	if (H->TheCells[Pos].Info != Legitimate) 
	{ // 如果这个单元没有被占，说明Key可以插入在此 
		H->TheCells[Pos].Info = Legitimate;
		H->TheCells[Pos].Data = Key;
		//字符串类型的关键词需要 strcpy 函数!!
		return true;
	}
	else {
		printf("键值已存在");
		return false;
	}
}
