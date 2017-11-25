#include <stdio.h>
#include <stdlib.h>

typedef struct PolyNode
{
	int Coefficient;
	int Exponent;
	struct PolyNode *Next;
}*Polynomial, *Position;

void Add(Polynomial Poly, int Coefficient,int Exponent)
{
	Position P1 = (PolyNode*)malloc(sizeof(PolyNode));
	P1->Coefficient = Coefficient;
	P1->Exponent = Exponent;
	P1->Next = NULL;
	Position P2 = Poly;
	while (P2->Next)
		P2 = P2->Next;
	P2->Next = P1;
}

int Delete(Polynomial Poly,Position P1)
{
	Position P2 = Poly->Next;
	while (P2)
	{
		if (P2 == P1) //!!!
		{
			Poly->Next = P1->Next;
			free(P1);
			return 0;
		}
		else if (P2->Next == P1)
		{
			P2->Next = P1->Next;
			free(P1);
			return 0;
		}
		P2 = P2->Next;
	}
	return -1;
}
void PrintAll(Polynomial Poly)
{
	Position P;
	for (P = Poly->Next; P; P = P->Next)
		printf("%d#%d  ", P->Coefficient,P->Exponent);
	printf("\n");
}

void AddPolinomial(Polynomial Poly1, Polynomial Poly2, Polynomial PolySum)
{
	Position P1, P2;
	P1 = Poly1->Next;
	P2 = Poly2->Next;
	while (P1 && P2)
	{
		if (P1->Exponent == P2->Exponent)
		{
			Add(PolySum, P1->Coefficient + P2->Coefficient, P1->Exponent);
			P1 = P1->Next;
			P2 = P2->Next;
		}
		else if (P1->Exponent > P2->Exponent)
		{
			Add(PolySum, P1->Coefficient, P1->Exponent);
			P1 = P1->Next;
		}
		else if (P1->Exponent < P2->Exponent)
		{
			Add(PolySum, P2->Coefficient, P2->Exponent);
			P2 = P2->Next;
		}
	}
	while (P1)
	{
		Add(PolySum, P1->Coefficient, P1->Exponent);
		P1 = P1->Next;
	}
	while (P2)
	{
		Add(PolySum, P2->Coefficient, P2->Exponent);
		P2 = P2->Next;
	}
}

int Find(Polynomial Poly, int Coefficient, int Exponent)
{
	Position P;
	for (P = Poly->Next; P; P = P->Next)
	{
		if (P->Exponent == Exponent)
		{
			P->Coefficient += Coefficient;
			return 0;
		}

	}
	return -1;
}

void MuiltPolynomial(Polynomial Poly1, Polynomial Poly2, Polynomial PolyProd)
{
	Position P1, P2, P3;
	if (Poly1->Next->Exponent > Poly2->Next->Exponent)
	{
		P1 = Poly1->Next;
		P3 = Poly2->Next;
	}
	else
	{
		P1 = Poly2->Next;
		P3 = Poly1->Next;
	}
	for (; P1; P1 = P1->Next)
		for (P2 = P3; P2; P2 = P2->Next)
			if(Find(PolyProd,P1->Coefficient * P2->Coefficient,P1->Exponent + P2->Exponent) != 0)
			   Add(PolyProd, P1->Coefficient * P2->Coefficient, P1->Exponent + P2->Exponent);
}

int main()
{
	int n, m;
	Polynomial Poly1, Poly2, PolySum, PolyProd;
	Poly1 = (PolyNode*)malloc(sizeof(PolyNode)); Poly1->Next = NULL; //!!!
	Poly2 = (PolyNode*)malloc(sizeof(PolyNode)); Poly2->Next = NULL;
	PolySum = (PolyNode*)malloc(sizeof(PolyNode)); PolySum->Next = NULL;
	PolyProd = (PolyNode*)malloc(sizeof(PolyNode)); PolyProd->Next = NULL;
	do {
		scanf("%d %d", &n, &m);
		if (n != 0)
		   Add(Poly1, n, m);
	} while (n != 0);
	do {
		scanf("%d %d", &n, &m);
		if (n != 0)
		  Add(Poly2, n, m);
	} while (n != 0);
	AddPolinomial(Poly1, Poly2, PolySum);
	MuiltPolynomial(Poly1, Poly2, PolyProd);
	PrintAll(PolySum);
	PrintAll(PolyProd);
}

/*
1 4
2 3
3 2
4 1
5 0
0 0
5 5
4 3
3 1
7 0
0 0

*/
