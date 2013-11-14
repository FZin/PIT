#pragma once

#include <iostream>


#include "Bibliothek.h"
#include "ListenElement.h"
#include "Signal.h"


class GraphErzeuger
{
private:
	Bibliothek* bibliothek;
	ListenElement* startElement;
	ListenElement* endElement;
	Signal* signale;
	short anzahlSignale;


public:
	GraphErzeuger();
	~GraphErzeuger();
};

