
#include "LaufzeitAnalysator.h"


LaufzeitAnalysator::LaufzeitAnalysator()
{
}

void LaufzeitAnalysator::init(Faktoren* f, ListenElement* s)
{
	faktoren = f;
	startElement = s;
}

LaufzeitAnalysator::~LaufzeitAnalysator()
{
}

void LaufzeitAnalysator::berechnungLaufzeitEinzelgatter(void) {
	short c_last = 0;
	ListenElement* node = NULL;
	for(node = startElement; node != NULL; node = node->getNextListenElement()){ // zeiger auf anfang verkettete liste, läuft durch bis ende
		int nachfolger = node->getSchaltwerkElement()->getAnzahlNachfolger(); //methode aus schaltwerkelemnt um anzahl von folgegatter zu bekommen
		if (nachfolger !=0){ //überprüfen ob letztes gatter vorliegt
			for( int i=0; i<nachfolger; i++){ // berechnung von C_last für jeweilige Folgegatter, unterscheidung zw. flipflop und gatter
				GatterTyp* element = node->getSchaltwerkElement()->getNachfolger(i)->getTyp();
					if( element->getIsFlipflop() == false){
						c_last += element->getEingaenge() * element->getLastKapazitaet();
					}
					else{
						c_last += element->getEingaenge() * element->getLastKapazitaet() + 1 * dynamic_cast<Flipflop*>(element)->getLastKapazitaetClock();
					}
			}
		}
		double spgFaktor;
		double tmpFaktor;
		double przFaktor;
		faktoren->getFaktoren(spgFaktor, tmpFaktor,przFaktor);  // Kv, Kp, Kt aus klasse faktoren hol
		SchaltwerkElement* p = NULL;
		GatterTyp* y = NULL;
		p->setLaufzeitEinzelgatter((y->getGrundlaufzeit() + y->getLastFaktor() * c_last) * spgFaktor * tmpFaktor * przFaktor); //formel umsetzen
	}
}