#pragma once
#include <Windows.h>
class WorkPlace
{
public:
	/*
	ќбщее врем€ работы N-го рабочего места
	*/
	 int timeWork;
	/*
	«ан€то ли данное рабочее место в данный момент
	*/
	 bool isWork;
public:
	WorkPlace();
	/*
	¬ыполнить обработку одного товара
	*/
	void doWork();
};

