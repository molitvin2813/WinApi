#pragma once
#include "MainLine.h"
class Fabric
{
public:
	/*
	����� ����� ������ �������
	*/
	int time;
	/*
	����� ���������� �������
	*/
	int countProduct;
	/*
	���������� �������, ������� ������ ���������
	*/
	int countProcessingProduct;

	MainLine mainLineArray;
public:

	Fabric();
	Fabric(int countProduct, int firstLine, int secondLine);
};

