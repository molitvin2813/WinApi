#pragma once
#include <string>
#include <iostream>
using std::string;
class Product
{
private:
	/*
	Ќазвание товара
	*/
	string nameOfProduct;
	/*
	ID товара
	*/
	int idProduct;
	/*
	ѕеременна€, котра€ показывает был ли обработан данный товар
	*/
	bool isProcessed;
public:
	Product();
	Product(string name, int idProd, bool proc);
	void setNameOfProduct(char* newName);
	void setIdProduct(int newID);
	void setIsProcessed(bool newProc);

	string getNameOfProduct();
	int	  getIdProduct();
	bool  getIsProcessed();
};

