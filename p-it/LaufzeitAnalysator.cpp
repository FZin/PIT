
#include "LaufzeitAnalysator.h"


LaufzeitAnalysator::LaufzeitAnalysator()
{
	frequenz = 0;
	laufzeitUebergangspfad = 0.0;
	laufzeitAusgangspfad = 0.0;
	uebergangspfad = "";
	ausgangspfad = "";
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
			for (int i = 1; i <= nachfolger; i++) {   // Berechnung von c_last für jedes Nachfolgegatter
				c_last += node->getSchaltwerkElement()->getNachfolger(i)->getTyp()->getLastKapazitaet(); //Ermittlung des Typs des Elementes (Gatter/Flipflop)	
				//cout << c_last << endl;
			}
		}
		double spgFaktor;
		double tmpFaktor;
		double przFaktor;
		faktoren->getFaktoren(spgFaktor, tmpFaktor, przFaktor);  //Kv, Kp, Kt aus Klasse Faktoren holen
		node->getSchaltwerkElement()->setLaufzeitEinzelgatter((node->getSchaltwerkElement()->getTyp()->getGrundlaufzeit() + node->getSchaltwerkElement()->getTyp()->getLastFaktor() * c_last / 1000.0) * spgFaktor * tmpFaktor * przFaktor); //Formel umsetzen (auf Einheiten achten!)
		//cout << node->getSchaltwerkElement()->getName() << ":" << node->getSchaltwerkElement()->getLaufzeitEinzelgatter() << endl;
		cout << node->getSchaltwerkElement()->getName() << ":" << node->getSchaltwerkElement()->getTyp()->getLastKapazitaet() << endl;
	}
	system("pause");
}


void LaufzeitAnalysator::dfs_Visit(SchaltwerkElement* k, SchaltwerkElement* s)
{
	for(unsigned int i = 1;i<=k->getAnzahlNachfolger();i++) { //Gibt getNachfolger(i) für zu große i NULL zurück?
		SchaltwerkElement* v = k->getNachfolger(i);
		if( v->getTyp()->getIsFlipflop()) {
			if( laufzeitUebergangspfad < (DFS_Zwischenspeicher[k].PfadLaufzeit + k->getLaufzeitEinzelgatter())) {
				laufzeitUebergangspfad = DFS_Zwischenspeicher[k].PfadLaufzeit + k->getLaufzeitEinzelgatter();
				uebergangspfad = "";
				for(SchaltwerkElement* s = k; s!=NULL ; s = DFS_Zwischenspeicher[s].VaterElement) {
					uebergangspfad = s->getName() + " -> " + uebergangspfad;
				}
				uebergangspfad += v->getName();
			}
		}else if(DFS_Zwischenspeicher[v].PfadLaufzeit < (DFS_Zwischenspeicher[k].PfadLaufzeit + k->getLaufzeitEinzelgatter())) {
			if(( DFS_Zwischenspeicher[v].PfadLaufzeit != 0 || v == s ) && ( DFS_Zwischenspeicher[v].VaterElement != k )) {
				DFS_Zwischenspeicher[v].VaterElement = k;
				if( zyklensuche( v )) {
					fehlerbehandlung();
					return;
				}
			}
			DFS_Zwischenspeicher[v].PfadLaufzeit = DFS_Zwischenspeicher[k].PfadLaufzeit + k->getLaufzeitEinzelgatter();
			DFS_Zwischenspeicher[v].VaterElement = k;
			dfs_Visit(v,s);
		}
	}
	if( k->getIsAusgangsElement() && ( laufzeitAusgangspfad < (DFS_Zwischenspeicher[k].PfadLaufzeit + k->getLaufzeitEinzelgatter()))) {
		laufzeitAusgangspfad = DFS_Zwischenspeicher[k].PfadLaufzeit + k->getLaufzeitEinzelgatter();
		ausgangspfad = "";
		for(SchaltwerkElement* s = k; s!=NULL ; s = DFS_Zwischenspeicher[s].VaterElement) {
			ausgangspfad = s->getName() + " -> " + ausgangspfad;
		}
	}
}


void LaufzeitAnalysator::dfs(ListenElement* s) {
	for( ListenElement* i = s; i != NULL; i = i->getNextListenElement()) {
		DFS_Daten dfsd;
		dfsd.PfadLaufzeit = 0;
		dfsd.VaterElement = NULL;
		DFS_Zwischenspeicher[i->getSchaltwerkElement()] = dfsd;
	}
	dfs_Visit(s->getSchaltwerkElement(),s->getSchaltwerkElement());
}


bool LaufzeitAnalysator::zyklensuche(SchaltwerkElement* v)
{
	for(SchaltwerkElement* s= DFS_Zwischenspeicher[v].VaterElement; !(s->getIsEingangsElement()); s = DFS_Zwischenspeicher[s].VaterElement) {
		if ( v == s ){
			return true;
		}
	}
	return false;
}


void LaufzeitAnalysator::fehlerbehandlung(void)
{
	cout << "FEHLAAA" << endl;
	system("pause");
}


void LaufzeitAnalysator::reset(void)
{
	frequenz = 0;
	laufzeitUebergangspfad = 0.0;
	laufzeitAusgangspfad = 0.0;
	uebergangspfad = "";
	ausgangspfad = "";
}


bool LaufzeitAnalysator::analyse(void)
{
	berechnungLaufzeitEinzelgatter();
	for(ListenElement* l = startElement; l!=NULL; l=l->getNextListenElement()) {
		if( (l->getSchaltwerkElement()->getIsEingangsElement()) || (l->getSchaltwerkElement()->getTyp()->getIsFlipflop())) {
			dfs(l);
		}
	}
	cout << "Laengster Pfad im Ueberfuehrungsschaltnetz:" << endl;
	cout << uebergangspfad << endl;
	cout << "Maximale Laufzeit der Pfade im Ueberfuehrungsschaltnetz: " << laufzeitUebergangspfad << " ps" << endl << endl;
	cout << "Laengster Pfad im Ausgangsschaltnetz:" << endl;
	cout << ausgangspfad << endl;
	cout << "Maximale Laufzeit der Pfade im Ausgangsschaltnetz: " << laufzeitAusgangspfad << " ps" << endl << endl;
	cout << "----------------------------------------" << endl;
	frequenz = 1/(laufzeitUebergangspfad+26)*1000000; // Setuptime einlesen!!
	cout << "Die maximal zulaessige Frequenz fuer das Schaltnetz/-werk betraegt: " << frequenz << "MHz" << endl;
	system("pause");

	return false;
}
