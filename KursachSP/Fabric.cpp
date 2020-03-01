#include "Fabric.h"

Fabric::Fabric()
{
	mainLineArray= MainLine(15,10,5);
}

Fabric::Fabric(int countProduct, int firstLine, int secondLine)
{
	mainLineArray = MainLine(countProduct, firstLine, secondLine);
}
