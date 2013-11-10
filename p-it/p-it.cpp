// p-it.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "Faktoren.h"
#include <iostream>


int _tmain(int argc, _TCHAR* argv[])
{
	int i;
	Faktoren F;
	F.setProzess(1);
	F.setSpannung(1.23);
	F.setTemperatur(45);
	F.ausgabeFaktoren();
	std::cin >> i;
	return 0;
}

