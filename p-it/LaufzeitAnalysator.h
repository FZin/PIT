#ifndef LAUFZEITANALYSATOR_H
#define LAUFZEITANALYSATOR_H

#include "Faktoren.h"
#include "Bibliothek.h"
#include "SchaltwerkElement.h"
#include "ListenElement.h"
#include "GraphErzeuger.h"

class LaufzeitAnalysator
{
public:
	LaufzeitAnalysator();
	~LaufzeitAnalysator();
	void init(Faktoren* f, ListenElement* s);
	void berechnungLaufzeitEinzelgatter(void);
private:
	Faktoren* faktoren;
	ListenElement* startElement;
};

#endif
