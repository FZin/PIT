
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

	
	//Einfach verkettete Liste erstellen
	ListenElement* vorgaenger = NULL;
	for(int i = 0; i<anzahlSignale; i++) { 

		if(signale[i].getQuelle() != "NULL") {

			ListenElement* temp = new ListenElement;

			if( startElement == NULL ) {
				startElement = temp;
			}
			endElement = temp;
			temp->setNextElement(NULL);

			GatterTyp* gTyp = bibliothek->getBibElement(signale[i].getQuellenTyp() ); 

			SchaltwerkElement* tempSchaltwerkElement = new SchaltwerkElement(gTyp) ;

			
			temp->setSchaltwerkElement(tempSchaltwerkElement);
			//Atribute des SchaltwerkElements inizialisieren
			temp->getSchaltwerkElement()->setName(signale[i].getQuelle() );			//name
			if (signale[i].getSignalTyp() == ausgang ) {
				temp->getSchaltwerkElement()->setIsAusgangsElement(true);
			}
			temp->getSchaltwerkElement()->setAnzahlNachfolger(signale[i].getAnzahlZiele() );

			


			if( vorgaenger != NULL ) {
				vorgaenger->setNextElement(temp);

			}


			vorgaenger = temp;


		}
	
	}




};