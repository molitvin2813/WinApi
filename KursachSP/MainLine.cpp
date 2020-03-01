#include "MainLine.h"
#include <string>
#include <iostream>
using std::string;
MainLine::MainLine(){


	string s2 = "";
	char m[50];
	for (int i = 0; i < 15; i++) {
		_itoa_s(i,m,10);
		s2 = "Tovarff: ";
		s2.append(m);
		
		arrayOfProduct[i] = Product(s2, i, false);
	}
		
	countProduct = 0;
	currentProduct = 0;
	firstWorkPlace = WorkPlace();
	secondWorkPlace = WorkPlace();

	firstLine = LineToWorkPlace(10);
	secondLine = LineToWorkPlace(5);
}

MainLine::MainLine(int countProd, int firstLineProduct, int secondLineProduct) {


	string s2 = "";
	char m[50];
	for (int i = 0; i < countProd; i++) {
		_itoa_s(i, m, 10);
		s2 = "Tovar: ";
		s2.append(m);

		arrayOfProduct[i] = Product(s2, i, false);
	}
	totcount = countProd;
	countProduct = 0;
	currentProduct = 0;
	firstWorkPlace = WorkPlace();
	secondWorkPlace = WorkPlace();

	firstLine = LineToWorkPlace(firstLineProduct);
	secondLine = LineToWorkPlace(secondLineProduct);
}



