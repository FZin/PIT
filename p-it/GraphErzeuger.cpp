
#include "GraphErzeuger.h"


GraphErzeuger::GraphErzeuger()
{
	bibliothek = NULL;
	startElement = NULL;
	endElement = NULL;
	signale = NULL;
	anzahlSignale = 0;

}


GraphErzeuger::~GraphErzeuger()
{
}


void GraphErzeuger::graphBau( Bibliothek* bib, Signal* sig, short anzahlSig ) {
	bibliothek = bib;
	signale = sig;
	anzahlSignale = anzahlSig;

	

	for(int i = 0; i<anzahlSignale; i++) { 
	
	}




};