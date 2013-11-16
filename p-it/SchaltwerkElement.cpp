#include "SchaltwerkElement.h"

SchaltwerkElement::SchaltwerkElement( GatterTyp* gTyp) { 

	name = "";
	typ = gTyp;
	laufzeitEinzelGatter = 0;
	nachfolgerElement = NULL;
	anzahlNachfolger = 0;
	isEingangsElement = false;
	isAusgangsElement = false;
	anzahlEingangssignale = 0;

};

SchaltwerkElement::~SchaltwerkElement() {
	if( nachfolgerElement != NULL) { 
		delete[] nachfolgerElement;
	}

};

SchaltwerkElement* SchaltwerkElement::getNachfolgerElement(int pos) {

	SchaltwerkElement* temp = nachfolgerElement[pos-1];


	return temp;
};

void SchaltwerkElement::nachfolgerHinzufuegen( SchaltwerkElement* schaltwerkElement, int pos ) {
	

	
	if(pos == anzahlNachfolger + 1 ) {
		SchaltwerkElement** temp = new SchaltwerkElement*[anzahlNachfolger +1];

		for(int i = 0; i<anzahlNachfolger; i++) { 
			temp[i] = nachfolgerElement[i];
		}

		temp[anzahlNachfolger] = schaltwerkElement;
		anzahlNachfolger++;
		
		delete[] nachfolgerElement;
		nachfolgerElement = temp;

	} else {
		nachfolgerElement[pos-1] = schaltwerkElement;



	}



	
};