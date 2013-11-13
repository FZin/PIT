#pragma once

#include <iostream>


#include "Bibliothek.h"
#include "Listenelemt.h"


class GraphErzeuger
{
private:
	Bibliothek* bibliothek;
	ListenElement* startElement;


public:
	GraphErzeuger();
	~GraphErzeuger();
};

