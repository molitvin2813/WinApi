#pragma once
#include "MainLine.h"
class Fabric
{
public:
	/*
	Общее время работы фабрики
	*/
	int time;
	/*
	Общее количество товаров
	*/
	int countProduct;
	/*
	Количество товаров, которые прошли обработку
	*/
	int countProcessingProduct;

	MainLine mainLineArray;
public:

	Fabric();
	Fabric(int countProduct, int firstLine, int secondLine);
};

