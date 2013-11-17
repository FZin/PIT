
#include "GraphErzeuger.h"


GraphErzeuger::GraphErzeuger()
{
	bibliothek = NULL;
	startElement = NULL;
	endElement = NULL;
	signale = NULL;
	anzahlSignale = 0;

}


GraphErzeuger::~GraphErzeuger() {

	ListenElement* lauf = startElement;

	while(lauf != NULL) {
		if(lauf->getSchaltwerkElement() != NULL) {
			delete lauf->getSchaltwerkElement();
			lauf->setSchaltwerkElement(NULL);
		}
		ListenElement* temp = lauf;
		lauf = lauf->getNextListenElement();
		delete temp;
		startElement = NULL;
		endElement = NULL;
	}

};


void GraphErzeuger::graphBau( Bibliothek* bib, Signal* sig, short anzahlSig ) {
	bibliothek = bib;
	signale = sig;
	anzahlSignale = anzahlSig;

	bool error = false;
	
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

			cout<<signale[i].getQuellenTyp()<<endl; 

			GatterTyp* gTyp = bibliothek->getBibElement(signale[i].getQuellenTyp() ); 

			//debug
			cout<<gTyp<<endl;


			SchaltwerkElement* tempSchaltwerkElement = new SchaltwerkElement(gTyp) ;
			
			if(tempSchaltwerkElement->getTyp() == NULL) {
				error = true;
			}
			
			temp->setSchaltwerkElement(tempSchaltwerkElement);
			//Atribute des SchaltwerkElements inizialisieren
			temp->getSchaltwerkElement()->setName(signale[i].getQuelle() );			//name
			if (signale[i].getSignalTyp() == ausgang ) {
				temp->getSchaltwerkElement()->setIsAusgangsElement(true);
			}
			temp->getSchaltwerkElement()->setAnzahlNachfolger(signale[i].getAnzahlZiele() );

			//set isEingang
			for(int j = 0; j < anzahlSignale; j++ ) {

				if(signale[j].getQuelle() == "NULL") {

					for(int k = 1; k <= signale[j].getAnzahlZiele() ; k++ ) {

						if( signale[j].getZiel(k) == temp->getSchaltwerkElement()->getName() ) {
							temp->getSchaltwerkElement()->setIsEingangsElement(true);
						}

					}

				}

			}
			


			if( vorgaenger != NULL ) {
				vorgaenger->setNextElement(temp);

			}


			vorgaenger = temp;


		}
	
	}


	//Graph aufbauen

	for(int i = 0; i<anzahlSignale; i++) {

		ListenElement* temp = startElement;
		while(temp != NULL && ( temp->getSchaltwerkElement()->getName() != signale[i].getQuelle() )  ) {
			temp = temp->getNextListenElement();

		}
		if(temp != NULL) {

			for(int j = 1; j <= signale[i].getAnzahlZiele(); j++) {

				ListenElement* ziel;

				





			}


		}

		







	}

	//wenn ein fehler aufgetreten ist
	
	if(error == true) {

		ListenElement* lauf = startElement;

		while(lauf != NULL) {
			if(lauf->getSchaltwerkElement() != NULL) {
				delete lauf->getSchaltwerkElement();
				lauf->setSchaltwerkElement(NULL);
			}
			ListenElement* temp = lauf;
			lauf = lauf->getNextListenElement();
			delete temp;
			startElement = NULL;
			endElement = NULL;
		}
		cout<<endl<<"Es entstand ein Fehler beim erzeugen des Graphen."<<endl;
		system("pause");

		

	}




};

void GraphErzeuger::ausgabeGraphenstruktur() {

	ListenElement* test = startElement;
	
	cout<<"Graphenstruktur"<<endl<<endl<<endl;



	while(test != NULL) {

		cout<<"Gattername : "<< test->getSchaltwerkElement()->getName()<<endl;
		
		cout<<"Gattertyp : "<< test->getSchaltwerkElement()->getTyp() /*->getName() */<<endl;
		
		



		test = test->getNextListenElement();
	}


};