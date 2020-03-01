#include "LineToWorkPlace.h"

LineToWorkPlace::LineToWorkPlace()
{
	countProductOnLine = 0;
	N = 5;
	for (int i = 0; i < N; i++)
		arrayOfProduct[i] = Product();
}

LineToWorkPlace::LineToWorkPlace(int n)
{
	countProductOnLine = 0;
	for (int i = 0; i < n; i++)
		arrayOfProduct[i] = Product();
	N = n;
}

void LineToWorkPlace::setN(int n)
{
	N = n;
}

int LineToWorkPlace::getN()
{
	return N;
}

void LineToWorkPlace::addNewProduct(Product newProduct)
{
	arrayOfProduct[countProductOnLine] = newProduct;
	countProductOnLine++;
}
