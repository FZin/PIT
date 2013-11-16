
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

			cout<<signale[i].getQuellenTyp()<<endl; 

			GatterTyp* gTyp = bibliothek->getBibElement(signale[i].getQuellenTyp() ); 

			//debug
			cout<<gTyp<<endl;


			SchaltwerkElement* tempSchaltwerkElement = new SchaltwerkElement(gTyp) ;

			
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




	}




};

void GraphErzeuger::ausgabeGraphenstruktur() {

	ListenElement* test = startElement;
	
	cout<<"Graphenstruktur"<<endl<<endl<<endl;

	system("pause");

	while(test != NULL) {

		cout<<"Gattername : "<< test->getSchaltwerkElement()->getName()<<endl;
		system("pause");
		cout<<"Gattertyp : "<< test->getSchaltwerkElement()->getTyp() /*->getName() */<<endl;
		
		//debug
		system("pause");



		test = test->getNextListenElement();
	}


};