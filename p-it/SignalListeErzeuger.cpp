#include "SignalListeErzeuger.h"



SignalListeErzeuger::SignalListeErzeuger() {
signale = NULL;
anzahlSignale = 0;
datei = "";
frequenz = 0;
};

SignalListeErzeuger::~SignalListeErzeuger() {
if(signale != NULL) {
	delete[] signale;
	
}

};

void SignalListeErzeuger::ausgabeSchaltnetzdatei() {
	string Schaltnetzdatei = "";

	//
	ifstream myfile;
	myfile.open(datei);
	if(!myfile) {
	cout<<endl<<"Es gab einen Fehler beim oeffnen der datei. Ueberpruefen sie den eingegebenen Pfad auf Korrektheit!"<<endl;
	}
	else {
		string zeile;
		while(getline(myfile,zeile)) {
		Schaltnetzdatei = Schaltnetzdatei + zeile + "\n";
		};
		myfile.close();
		cout<<Schaltnetzdatei;
	}

};

void SignalListeErzeuger::setPfad(string pfad) {

	datei=pfad;

	
	bool error = false;
	ifstream myfile;
	myfile.open(datei);

	if(!myfile) {
		cout<<endl<<"Es gab einen Fehler beim oeffnen der datei. Ueberpruefen sie den eingegebenen Pfad auf Korrektheit!"<<endl;
		system("pause");
		
	} else {
		
		bool kurzschluss = false;

		//textdatei in string datei speichern
		string temp = "";
		string zeile;
		while(getline(myfile,zeile)) {
		temp = temp + zeile + "\n";
		}
		myfile.close();
	



		//Kommentare entfernen
	
		int pos = 0;
		while(pos != string::npos) {
			pos = temp.find("//",pos);
			int posend = temp.find("\n",pos);

			if(pos != string::npos) {
				temp.erase(pos, posend-pos);
			}

		}

	
		int posStart = temp.find("ARCHITECTURE");
		int posEntity = temp.find("ENTITY", posStart);
		int posInput = temp.find("INPUT", posEntity);
		int posOutput = temp.find("OUTPUT", posEntity);
		int posSignals = temp.find("SIGNALS", posEntity);
		int posClock = temp.find("CLOCK",posEntity );
	

		//Anzahl der Signale herrausfinden
		//Inputsignale
		pos = temp.find("s", posInput);

		while(pos < temp.find(";",posInput)) {
			pos = temp.find("s",pos+1);
			anzahlSignale++;
		}
	
		//Outputsignale
		pos = temp.find("s", posOutput);

		while(pos < temp.find(";",posOutput)) {
			pos = temp.find("s",pos+1);
			anzahlSignale++;
		}
	
		//Interne Signale
		pos = temp.find("s", posSignals);

		while(pos < temp.find(";",posSignals)) {
			pos = temp.find("s",pos+1);
			anzahlSignale++;
		}

	
	
		//Frequenz herrausfinden

		pos = temp.find("clk,", posClock );

		int zahl = atoi(temp.substr(pos + 4).c_str());

		int faktor = 1;
		pos = temp.find("kHz", temp.find("clk,", posClock ) );
		if(pos < temp.find(";", posClock ) && pos != string::npos ) {
			faktor = 1000;
		}
		pos = temp.find("MHz", temp.find("clk,", posClock ) );
		if(pos < temp.find(";", posClock ) && pos != string::npos ) {
			faktor = 1000000;
		}
		frequenz = faktor * zahl;


	


		int posBegin = temp.find("BEGIN",posEntity );
		int posEnd = temp.find("END",posBegin );

		//bereits erzeugte signale loeschen
		if(signale != NULL) {
			delete[] signale;
		}
		
		//arry anlegen
		signale = new Signal[anzahlSignale];

		//signaltyp definieren
		//Inputsignale
		pos = temp.find("s", posInput);

		while(pos < temp.find(";",posInput)) {
		
			int nummer = atoi(temp.substr(pos + 1).c_str());
			if(nummer <= anzahlSignale) {
				signale[nummer-1].setSignalTyp(eingang);
			} else {
				error = true;
			}
			
			pos = temp.find("s",pos+1);
		}
		
		//Ouputsignale
		pos = temp.find("s", posOutput);

		while(pos < temp.find(";",posOutput)) {
		
			int nummer = atoi(temp.substr(pos + 1).c_str());
			if(nummer <= anzahlSignale) {
				signale[nummer-1].setSignalTyp(ausgang);
			} else {
				error = true;
			}
			
			pos = temp.find("s",pos+1);
		}
	
		//Interne Signale

		pos = temp.find("s", posSignals);

		while(pos < temp.find(";",posSignals)) {
		
			int nummer = atoi(temp.substr(pos + 1).c_str());
			if(nummer <= anzahlSignale) {
				signale[nummer-1].setSignalTyp(intern);
			} else {
				error = true;
			}
			
			pos = temp.find("s",pos+1);
		}


	

		
		//unnötiges löschen
		if( (posEnd-temp.find("g",posBegin)) > 0 ) {
			temp = temp.substr( temp.find("g",posBegin), posEnd-temp.find("g",posBegin) );
		} else {
			error = true;
		}
	
		
		pos = temp.find("g");
		while(pos != string::npos && error == false) { 

			//anzahl der signal dieses Gatters herrausfinden
			int anzahlSig = 0;
			int posTemp = temp.find("s",temp.find("(",pos) );
			while(posTemp < temp.find(";",pos)) {
				anzahlSig++;
				posTemp = temp.find("s" , posTemp + 1);
		
			}
					
			
			//ziel ins signal speichern
			posTemp = temp.find("s",temp.find("(",pos) );
			for(int i = 0; i < (anzahlSig-1);i++ ) {
			

				int nummer = atoi( temp.substr(posTemp+1).c_str() );
				string ziel = temp.substr(pos, 4);
			
				if(nummer <= anzahlSignale) {
					signale[nummer-1].zielHinzufuegen(ziel, (signale[nummer-1].getAnzahlZiele()) + 1 );
				} else {
					error = true;
				}

				
				posTemp = temp.find("s", posTemp + 1 );
				
				//wenn letztes Ziel abgearbeitet quelle definiern und auf Kurzschluss pruefen
				if(i == (anzahlSig-2)) {


					nummer = atoi( temp.substr(posTemp+1).c_str() );
					ziel = temp.substr(pos, 4);

					//auf Kurzschluss prüfen
					if(nummer <= anzahlSignale) {
						if(signale[nummer-1].getQuelle() != "NULL") {
						kurzschluss=true;
						}
					} else {
						error = true;
					}

					//quelle definieren
					if(nummer <= anzahlSignale) {
						signale[nummer-1].setQuelle(ziel);
						ziel = temp.substr( temp.find(":",pos) + 1 , temp.find("(",pos)-temp.find(":",pos) - 1 );
						signale[nummer-1].setQuellenTyp(ziel);


					} else {
						error = true;
					}




				}
		
			}
	
			pos =temp.find("g",pos+1);
		}
		

		//wenn ein Fehler auftritt, signale loeschen
		if(error == true) {
			delete[] signale;
			signale = NULL;
			anzahlSignale = 0;
			frequenz = 0;
			cout<<endl<<"Fehler: Die Datei ist Fehlerhaft!"<<endl;
			system("pause");
	
		}


		//wenn ein Kurzschluss auftritt, signale loeschen
		if(kurzschluss == true) {
			delete[] signale;
			signale = NULL;
			anzahlSignale = 0;
			frequenz = 0;
			cout<<endl<<"Fehler: Es ist ein Kurzschluss vorhanden!"<<endl;
			system("pause");
	
		}

	}
};



void SignalListeErzeuger::ausgabeSignale() {

	if(anzahlSignale > 0 ) {
		cout<<"Signale:"<<endl<<endl<<endl;

		for(int i = 0; i < anzahlSignale;i++ ) {

			cout<<"Signalname : s";
			if(i<9) {
				cout<<"00"<<i+1;
			} else if(i<99) {
				cout<<"0"<<i+1;
			} else {
				cout<<i+1;
			}
			
			cout<<endl<<"Signaltyp : ";
			if(signale[i].getSignalTyp() == eingang) {
				cout<<"Eingangssignal";
			}
			if(signale[i].getSignalTyp() == intern) {
				cout<<"Internes Signal";
			}
			if(signale[i].getSignalTyp() == ausgang) {
				cout<<"Ausgangssignal";
			}
			if(signale[i].getSignalTyp() == unbekannt) {
				cout<<"unbekanntes Signal";
			}

			cout<<endl<<"Signalquelle : ";
			if(signale[i].getQuelle() == "NULL") {
				cout<<"keine Quelle";
			} else {
				cout<<signale[i].getQuelle();
			}

			cout<<endl<<"-->Das Signal hat "<<signale[i].getAnzahlZiele()<<" Ziele"<<endl;
			cout<<"Ziel-Gatter : ";
			for(int j = 1; j <= signale[i].getAnzahlZiele(); j++) {
				cout<<signale[i].getZiel(j)<<" ";
			}
			cout<<endl<<endl;


		}
	
	} else {
		cout<<"Keine Signale vorhanden."<<endl;
	}
};

