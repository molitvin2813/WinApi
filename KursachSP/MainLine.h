#pragma once
#include "WorkPlace.h"
#include "LineToWorkPlace.h"
 class MainLine
{
public:
	/*
	время, которое работала данная линия
	*/
	static int time;
	/*
	Количество товаров, которые были обработаны на данной линии;
	*/
	 int countProduct;
	 /*
	 Первое рабочее место
	 */
	 WorkPlace firstWorkPlace;
	 /*
	 Второе рабочее место
	 */
	 WorkPlace secondWorkPlace;
	 /*
	 Указатель на текущий товар 
	 в списке товаров, которые лоджны пройти обработку
	 */
	 int currentProduct;
	 /*
	 Список товаров
	 */
	 Product arrayOfProduct[100];
	 int totcount;
	 /*
	 Первая линия. Доставляет товары к первому рабочему месту
	 */
	 LineToWorkPlace firstLine;
	 /*
	 Вторая линия. Доставляет товары ко второму рабочему месту
	 */
	 LineToWorkPlace secondLine;
public:
	MainLine();
	MainLine(int countProduct, int firstLine, int secondLine);
};

