
#include "LaufzeitAnalysator.h"


LaufzeitAnalysator::LaufzeitAnalysator()
{
}

LaufzeitAnalysator::~LaufzeitAnalysator()
{
}

//Objektübergabe durch Zeiger
void LaufzeitAnalysator::init(Faktoren* f, ListenElement* s)
{
	faktoren = f;
	startElement = s;
}

//Berechnung der Einzelgatterlaufzeit und anschließendes Speichern im Attribut LaufzeitEinzelgatter der Klasse SchaltwerkElement
void LaufzeitAnalysator::berechnungLaufzeitEinzelgatter(void) {
	short c_last = 0;
	for (ListenElement* node = startElement; node != NULL; node = node->getNextListenElement()) {   //Zeiger auf Anfang verkettete Liste, durchlaufen aller Elemente der Liste
		int nachfolger = node->getSchaltwerkElement()->getAnzahlNachfolger();     //Ermittlung der Anzahl von Nachfolgegattern durch entsprechende Funktion
		if (nachfolger != 0) {   //Überprüfung ob aktuelles Gatter Ausgangselement ist (würde bedeuten keine Nachfolgegatter)
			for (int i = 0; i < nachfolger; i++) {   // Berechnung von c_last für jedes Nachfolgegatter
				GatterTyp* element = node->getSchaltwerkElement()->getNachfolger(i)->getTyp(); //Ermittlung des Typs des Elementes (Gatter/Flipflop)
					if (element->getIsFlipflop() == false) {   //wenn Gatter...
						c_last += element->getEingaenge() * element->getLastKapazitaet();     //Berechnung c_last
					}
					else{   //wenn Flipflop...
						c_last += element->getEingaenge() * element->getLastKapazitaet() + 1 * dynamic_cast<Flipflop*>(element)->getLastKapazitaetClock();  //Berechnung c_last
					}
			}
		}
		double spgFaktor;
		double tmpFaktor;
		double przFaktor;
		faktoren->getFaktoren(spgFaktor, tmpFaktor, przFaktor);  //Kv, Kp, Kt aus Klasse Faktoren holen
		startElement->getSchaltwerkElement()->setLaufzeitEinzelgatter((startElement->getSchaltwerkElement()->getTyp()->getGrundlaufzeit() + startElement->getSchaltwerkElement()->getTyp()->getLastFaktor() * c_last / 1000) * spgFaktor * tmpFaktor * przFaktor); //Formel umsetzen (auf Einheiten achten!)
	}
}