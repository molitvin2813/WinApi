#include "Product.h"

Product::Product()
{
	nameOfProduct = "PROSO_TOVAR";
	idProduct = -1;
	isProcessed = false;
}

Product::Product(string name, int idProd, bool proc)
{
	nameOfProduct = name;
	idProduct = idProd;
	isProcessed = proc;
}

void Product::setNameOfProduct(char* newName)
{
	nameOfProduct = newName;
}

void Product::setIdProduct(int newID)
{
	idProduct = newID;
}

void Product::setIsProcessed(bool newProc)
{
	isProcessed = newProc;
}

string Product::getNameOfProduct()
{
	return nameOfProduct;
}

int Product::getIdProduct()
{
	return idProduct;
}

bool Product::getIsProcessed()
{
	return isProcessed;
}
