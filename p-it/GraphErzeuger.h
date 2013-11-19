#ifndef GRAPHERZEUGER_H
#define GRAPHERZEUGER_H

#include <iostream>
#include <string>

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
	void graphBau( Bibliothek* bib, Signal* sig, short anzahlSig );
	void ausgabeGraphenstruktur();
};
#endif

