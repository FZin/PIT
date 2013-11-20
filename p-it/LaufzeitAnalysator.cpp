
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
void LaufzeitAnalysator::berechnungLaufzeitEinzelgatter(void) 
{
	for (ListenElement* node = startElement; node != NULL; node = node->getNextListenElement()) { //Zeiger auf Anfang verkettete Liste, durchlaufen aller Elemente der Liste
		short c_last = 0;
		int nachfolger = node->getSchaltwerkElement()->getAnzahlNachfolger();     //Ermittlung der Anzahl von Nachfolgegattern durch entsprechende Funktion
		if (nachfolger != 0) {   //Überprüfung ob aktuelles Gatter Ausgangselement ist (würde bedeuten keine Nachfolgegatter)
			for (int i = 0; i < nachfolger; i++) {   // Berechnung von c_last für jedes Nachfolgegatter
				c_last += node->getSchaltwerkElement()->getNachfolger(i)->getTyp()->getLastKapazitaet(); //Ermittlung des Typs des Elementes (Gatter/Flipflop)	
			}
		}
		double spgFaktor;
		double tmpFaktor;
		double przFaktor;
		faktoren->getFaktoren(spgFaktor, tmpFaktor, przFaktor);  //Kv, Kp, Kt aus Klasse Faktoren holen
		node->getSchaltwerkElement()->setLaufzeitEinzelgatter((node->getSchaltwerkElement()->getTyp()->getGrundlaufzeit() + startElement->getSchaltwerkElement()->getTyp()->getLastFaktor() * c_last / 1000) * spgFaktor * tmpFaktor * przFaktor); //Formel umsetzen (auf Einheiten achten!)
	}
}