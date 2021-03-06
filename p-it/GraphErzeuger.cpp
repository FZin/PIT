
#include "GraphErzeuger.h"

//Konstruktor

GraphErzeuger::GraphErzeuger() {
    bibliothek = NULL;
    startElement = NULL;
    endElement = NULL;
    signale = NULL;
    anzahlSignale = 0;

}

//Destruktor

GraphErzeuger::~GraphErzeuger() {
    ListenElement* lauf = startElement;

    while (lauf != NULL) {
        if (lauf->getSchaltwerkElement() != NULL) {
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

//erstellt den Graphen aus der Signalliste

void GraphErzeuger::graphBau(Bibliothek* bib, Signal* sig, short anzahlSig) {
    bibliothek = bib;
    signale = sig;
    anzahlSignale = anzahlSig;
    bool error = false;

    //Loescht einen vorher erstellten graphen 
    {
        ListenElement* lauf = startElement;

        while (lauf != NULL) {
            if (lauf->getSchaltwerkElement() != NULL) {
                delete lauf->getSchaltwerkElement();
                lauf->setSchaltwerkElement(NULL);
            }
            ListenElement* temp = lauf;
            lauf = lauf->getNextListenElement();
            delete temp;
            startElement = NULL;
            endElement = NULL;
        }

    }

    //Einfach verkettete Liste erstellen
    ListenElement* vorgaenger = NULL;
    for (int i = 0; i < anzahlSignale; i++) {



        if (signale[i].getQuelle() != "NULL") {

            ListenElement* temp = new ListenElement;

            if (startElement == NULL) {
                startElement = temp;
            }
            endElement = temp;
            temp->setNextElement(NULL);



            GatterTyp* gTyp = bibliothek->getBibElement(signale[i].getQuellenTyp());




            SchaltwerkElement* tempSchaltwerkElement = new SchaltwerkElement(gTyp);

            if (tempSchaltwerkElement->getTyp() == NULL) {
                error = true;
            }

            temp->setSchaltwerkElement(tempSchaltwerkElement);

            //Atribute des SchaltwerkElements inizialisieren
            //name
            temp->getSchaltwerkElement()->setName(signale[i].getQuelle());
            //isAusngang
            if (signale[i].getSignalTyp() == ausgang) {
                temp->getSchaltwerkElement()->setIsAusgangsElement(true);
            }




            //isEingang
            for (int j = 0; j < anzahlSignale; j++) {

                if (signale[j].getQuelle() == "NULL") {

                    for (int k = 1; k <= signale[j].getAnzahlZiele(); k++) {

                        if (signale[j].getZiel(k) == temp->getSchaltwerkElement()->getName()) {
                            temp->getSchaltwerkElement()->setIsEingangsElement(true);
                        }

                    }

                }

            }


            //nachfolger des ListenElements erstellen
            if (vorgaenger != NULL) {
                vorgaenger->setNextElement(temp);

            }

            vorgaenger = temp;

        }

    }

    //Graph aufbauen

    for (int i = 0; i < anzahlSignale; i++) {

        ListenElement* temp = startElement;
        while (temp != NULL && (temp->getSchaltwerkElement()->getName() != signale[i].getQuelle())) {
            temp = temp->getNextListenElement();

        }
        if (temp != NULL) {

            for (int j = 1; j <= signale[i].getAnzahlZiele(); j++) {

                ListenElement* ziel = startElement;

                while (ziel != NULL && (ziel->getSchaltwerkElement()->getName() != signale[i].getZiel(j))) {
                    ziel = ziel->getNextListenElement();
                }

                //erstellt die Verbindungen unter den gattern, fuegt Nachfolger hinzu
                if (ziel != NULL) {
                    temp->getSchaltwerkElement()->nachfolgerHinzufuegen(ziel->getSchaltwerkElement(), temp->getSchaltwerkElement()->getAnzahlNachfolger() + 1);
                } else {
                    error = true;

                }
            }
        }
    }


    //auf unbenutzte Signale pruefen

    for (int i = 0; i < anzahlSignale; i++) {

        if ((signale[i].getQuelle() == "NULL") && (signale[i].getAnzahlZiele() == 0) && (error == false)) {
            error = true;
            cout << "Es gibt ein unbenutztes Signal." << endl << endl;
            system("pause");
            exit(0);
        }


    }

    //auf unbeschaltete Gattereingaenge und zu viel beschaltete Gatter pruefen

    if (error == false) {


        ListenElement* lauf = startElement;
        while (lauf != NULL) {

            short anzahlVorgaenger = 0;




            for (int i = 0; i < anzahlSignale; i++) {
                for (int j = 1; j <= signale[i].getAnzahlZiele(); j++) {
                    if (signale[i].getZiel(j) == lauf->getSchaltwerkElement()->getName()) {
                        anzahlVorgaenger++;
                    }

                }

            }



            if (anzahlVorgaenger != lauf->getSchaltwerkElement()->getTyp()->getEingaenge()) {

                error = true;
                cout << lauf->getSchaltwerkElement()->getName() << endl;
                cout << "Anzahl Eingaenge laut Bibliothek : " << lauf->getSchaltwerkElement()->getTyp()->getEingaenge() << endl;
                cout << "Anzahl Eingaenge laut Schaltwerk : " << anzahlVorgaenger << endl << endl;
                system("pause");
                exit(0);
            }



            lauf = lauf->getNextListenElement();
        }


    }








    //wenn ein fehler aufgetreten ist

    if (error == true) {

        ListenElement* lauf = startElement;

        while (lauf != NULL) {
            if (lauf->getSchaltwerkElement() != NULL) {
                delete lauf->getSchaltwerkElement();
                lauf->setSchaltwerkElement(NULL);
            }
            ListenElement* temp = lauf;
            lauf = lauf->getNextListenElement();
            delete temp;
            startElement = NULL;
            endElement = NULL;
        }
        cout << endl << "Es entstand ein Fehler beim erzeugen des Graphen." << endl;
        system("pause");
    }




};


//gibt den Erzeugten Graphen aus

void GraphErzeuger::ausgabeGraphenstruktur() {
    ListenElement* test = startElement;

    cout << "Graphenstruktur" << endl << endl << endl;



    while (test != NULL) {

        cout << "Gattername : " << test->getSchaltwerkElement()->getName() << endl;

        cout << "Gattertyp : " << test->getSchaltwerkElement()->getTyp()->getName() << endl;

        cout << "-->Das Gatter hat " << test->getSchaltwerkElement()->getAnzahlNachfolger() << " Ziele" << endl;

        cout << "Angeschlossene Gatter : ";

        for (int i = 1; i <= test->getSchaltwerkElement()->getAnzahlNachfolger(); i++) {
            cout << test->getSchaltwerkElement()->getNachfolger(i)->getName() << " ";
        }

        cout << endl << endl;

        test = test->getNextListenElement();
    }


};

ListenElement* GraphErzeuger::getStartElement(void) {
    return startElement;
}
