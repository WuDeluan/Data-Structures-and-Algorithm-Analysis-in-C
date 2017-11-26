#include <stdio.h>
#include <stdlib.h>
#define MaxDegree 20
typedef struct PolyNode
{
	int CoeffArray[MaxDegree + 1];
	int HighPower;
}*Polynomial;

void ZeroPolynomial(Polynomial Poly)
{
	for (int i = 0; i <= MaxDegree; i++)
		Poly->CoeffArray[i] = 0;
	Poly->HighPower = 0;
}

void AddPolynomial(Polynomial Poly1, Polynomial Poly2, Polynomial PolySum)
{
	ZeroPolynomial(PolySum);
	(Poly1->HighPower > Poly2->HighPower) ? PolySum->HighPower = Poly1->HighPower : PolySum->HighPower = Poly2->HighPower;
	for (int i = PolySum->HighPower; i >= 0; i--)
		PolySum->CoeffArray[i] = Poly1->CoeffArray[i] + Poly2->CoeffArray[i];
}

int MultPolynomial(Polynomial Poly1, Polynomial Poly2, Polynomial PolyProd)
{
	int i, j;
	ZeroPolynomial(PolyProd);
	PolyProd->HighPower = Poly1->HighPower + Poly2->HighPower;
	if (PolyProd->HighPower > MaxDegree)
		return -1;
	for (i = 0; i <= Poly2->HighPower; i++)
		for (j = 0; j < Poly2->HighPower; j++)
			PolyProd->CoeffArray[i + j] += Poly1->CoeffArray[i] * Poly2->CoeffArray[j];
}

int main()
{
	Polynomial Poly1, Poly2, PolySum, PolyProd;
	Poly1 = (PolyNode*)malloc(sizeof(PolyNode)); //!!!
	Poly2 = (PolyNode*)malloc(sizeof(PolyNode));
	PolySum = (PolyNode*)malloc(sizeof(PolyNode));
	PolyProd = (PolyNode*)malloc(sizeof(PolyNode));
	ZeroPolynomial(Poly1);
	ZeroPolynomial(Poly2);
	int i;
	for (i = 0; i < 8; i++)
	{
		Poly1->CoeffArray[i] = i;
		Poly2->CoeffArray[i] = 8 - i;
	}
	Poly1->HighPower = Poly2->HighPower = 8;
	AddPolynomial(Poly1, Poly2, PolySum);
	MultPolynomial(Poly1, Poly2, PolyProd);

	return 0;
}
