#pragma once
#include "Product.h"
class LineToWorkPlace
{
public:
	/*
	���������� �������, ������� ������������ ����� ���������� �� �����
	*/
	int N;
	/*
	���������� ������� �� ������ � �������� ������
	*/
	int countProductOnLine;
	Product arrayOfProduct[50];
	
public:
	LineToWorkPlace();
	LineToWorkPlace(int n);
	void setN(int n);
	int getN();
	/*
	�������� ����� ������� �� ������
	*/
	void addNewProduct(Product newProduct);

};

