#pragma once
#include <Windows.h>
class WorkPlace
{
public:
	/*
	����� ����� ������ N-�� �������� �����
	*/
	 int timeWork;
	/*
	������ �� ������ ������� ����� � ������ ������
	*/
	 bool isWork;
public:
	WorkPlace();
	/*
	��������� ��������� ������ ������
	*/
	void doWork();
};

