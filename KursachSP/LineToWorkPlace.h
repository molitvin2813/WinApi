#pragma once
#include "Product.h"
class LineToWorkPlace
{
public:
	/*
	 оличество товаров, которое одновременно может находитьс€ на линии
	*/
	int N;
	/*
	 оличество товаров на линиии в теккущий момент
	*/
	int countProductOnLine;
	Product arrayOfProduct[50];
	
public:
	LineToWorkPlace();
	LineToWorkPlace(int n);
	void setN(int n);
	int getN();
	/*
	ƒобавить новый продукт на линиию
	*/
	void addNewProduct(Product newProduct);

};

