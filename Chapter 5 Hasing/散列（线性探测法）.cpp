#include <stdio.h>
#include <stdlib.h>

enum State
{
	EXIST,
	EMPTY,
	DELETE
};

typedef struct HashCell
{
	int Key;
	int Searchtime;
	State Info;
};

typedef struct HashTable
{
	int TableSize;
	HashCell *TheCells;
}*Hash;

void InitHash(Hash H)
{
	H->TheCells = (HashCell*)malloc(sizeof(HashCell) * H->TableSize);
	for (int i = 0; i < H->TableSize; i++)
		H->TheCells[i].Info = EMPTY;
}

int InsertHash(Hash H, int Key)
{
	int Index, i, j = 0, searchtime = 0;
	Index = Key % H->TableSize;
	for (i = Index; i < H->TableSize; i++)
	{
		j++;
		searchtime++;
		if (H->TheCells[i].Info != EXIST)
			break;
		if (i == H->TableSize - 1)
			i = -1;
		if (j == H->TableSize)
			return -1;
	}
	H->TheCells[i].Info = EXIST;
	H->TheCells[i].Key = Key;
	H->TheCells[i].Searchtime = searchtime;
	return 0;
}

int FindHash(Hash H, int Key)
{
	int Index, i, j = 0;
	Index = Key % H->TableSize;
	for (i = Index; i < H->TableSize; i++)
	{
		j++;
		if (H->TheCells[i].Key == Key && H->TheCells[i].Info == EXIST)
			return i;
		if (i == H->TableSize - 1)
			i = -1;
		if (j == H->TableSize)
			return -1;
	}
	return 0;
}

int DeleteHash(Hash H, int Key)
{
	int Index = FindHash(H, Key);
	if (Index != -1)
		H->TheCells[Index].Info = DELETE;
	else
		return -1;
	return 0;
}

double ASL(Hash H)
{
	double j = 0, asl = 0;
	for (int i = 0; i < H->TableSize; i++)
	{
		if (H->TheCells[i].Info != EXIST)
			asl += 0;
		else
		{
			j++;
			asl += H->TheCells[i].Searchtime;
		}
	}
	asl /= j;
	return asl;
}

void PrintHash(Hash H)
{
	int i;
	printf("哈希表地址:       ");
	for (i = 0; i < H->TableSize; i++)
		printf("%d\t", i);
	printf("\n哈希表关键字:     ");
	for (i = 0; i < H->TableSize; i++)
	{
		if (H->TheCells[i].Info != EXIST)
			printf(" \t");
		else
			printf("%d\t", H->TheCells[i].Key);
	}
	printf("\n搜索次数:          ");
	for (i = 0; i < H->TableSize; i++)
	{
		if (H->TheCells[i].Info != EXIST)
			printf(" \t");
		else
			printf("%d\t", H->TheCells[i].Searchtime);
	}
	printf("\n平均搜索长度ASL(11)= %lf\n", ASL(H));
}

int main()
{
	Hash H;
	H = (Hash)malloc(sizeof(HashTable));
	H->TableSize = 13;
	InitHash(H);	
	int data[] = { 16,74,60,43,54,90,46,31,29,88,77 };
	for (int i = 0; i < 11; i++)
		InsertHash(H, data[i]);
	PrintHash(H);
	printf("ha[%d].key=29\n", FindHash(H,29));
	printf("删除关键字77\n");
	(DeleteHash(H, 77) == 0) ? PrintHash(H) : printf("删除失败!\n");
	(FindHash(H, 77) == 0) ? PrintHash(H) : printf("未找到77!\n");
	(InsertHash(H,77) == 0) ? PrintHash(H) : printf("插入失败！!\n");
}
