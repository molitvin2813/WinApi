#pragma once
#include "WorkPlace.h"
#include "LineToWorkPlace.h"
 class MainLine
{
public:
	/*
	�����, ������� �������� ������ �����
	*/
	static int time;
	/*
	���������� �������, ������� ���� ���������� �� ������ �����;
	*/
	 int countProduct;
	 /*
	 ������ ������� �����
	 */
	 WorkPlace firstWorkPlace;
	 /*
	 ������ ������� �����
	 */
	 WorkPlace secondWorkPlace;
	 /*
	 ��������� �� ������� ����� 
	 � ������ �������, ������� ������ ������ ���������
	 */
	 int currentProduct;
	 /*
	 ������ �������
	 */
	 Product arrayOfProduct[100];
	 int totcount;
	 /*
	 ������ �����. ���������� ������ � ������� �������� �����
	 */
	 LineToWorkPlace firstLine;
	 /*
	 ������ �����. ���������� ������ �� ������� �������� �����
	 */
	 LineToWorkPlace secondLine;
public:
	MainLine();
	MainLine(int countProduct, int firstLine, int secondLine);
};

