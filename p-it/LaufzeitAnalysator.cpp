
#include "LaufzeitAnalysator.h"


LaufzeitAnalysator::LaufzeitAnalysator()
{
}

LaufzeitAnalysator::~LaufzeitAnalysator()
{
}

void LaufzeitAnalysator::init(Faktoren* f, ListenElement* s)
{
	faktoren = f;
	startElement = s;
}

void LaufzeitAnalysator::berechnungLaufzeitEinzelgatter(void) {
	short c_last = 0;
	for(ListenElement* node = startElement; node != NULL; node = node->getNextListenElement()){   // zeiger auf anfang verkettete liste, läuft durch bis ende
		int nachfolger = node->getSchaltwerkElement()->getAnzahlNachfolger();     //methode aus schaltwerkelemnt um anzahl von folgegatter zu bekommen
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
		faktoren->getFaktoren(spgFaktor, tmpFaktor, przFaktor);  // Kv, Kp, Kt aus klasse faktoren holen
		startElement->getSchaltwerkElement()->setLaufzeitEinzelgatter((startElement->getSchaltwerkElement()->getTyp()->getGrundlaufzeit() + startElement->getSchaltwerkElement()->getTyp()->getLastFaktor() * c_last / 1000) * spgFaktor * tmpFaktor * przFaktor); //formel umsetzen
	}
}