
#include "Menue.h"





void Menue::menueKopf() {

	cout<<"**************************************"<<endl;
	cout<<"       IT-Praktikum WS2013/2014"<<endl;
	cout<<"Laufzeitanalyse synchroner Schaltwerke"<<endl;
	cout<<"**************************************"<<endl<<endl;

}

void Menue::start() {

	system("cls");
	menueKopf();

	cout<<"(1) auessere Faktoren"<<endl;
	cout<<"Spannung [Volt] : "<<meineFaktoren.getSpannung()<<endl;
	cout<<"Temperatur [Grad Celsius] : "<<meineFaktoren.getTemperatur()<<endl;
	cout<<"Prozess (1=slow, 2=typical, 3=fast) : "<<meineFaktoren.getProzess()<<endl<<endl;
	cout<<"(2) Bibliothek"<<endl;
	cout<<"Pfad zur Bibliotheksdatei: "<< meineBibliothek.getPfad()<< endl<<endl;
	cout<<"(3) Schaltwerk"<<endl;
	cout<<"Pfad zur Schaltwerksdatei: "<<meinSignalListeErzeuger.getdatei()<<endl<<endl;
	cout<<"(4) Analyse starten"<<endl<<endl;
	cout<<"(5) Programm beenden"<<endl<<endl<<endl;

	cout<<"Waehle einen Menuepunkt und bestaetige mit Enter:"<<endl;

	int eingabe;
	cin.clear();
	cin.sync();
	cin>>eingabe;
	
	bool erfolgreich; //markiert

	switch(eingabe){
	case 1:
		faktorenMenue();
		break;
	case 2:
		bibliothekMenue();
		break;
	case 3:
		schaltwerkMenue();
		break;
	case 4:
		analyse();
		break;
	case 5:
		exit(0); break;
	case 6:
		erfolgreich = meineBibliothek.pfadEinlesen("C:\\Users\\Fabian\\Documents\\pit\\bib.txt");
		meineBibliothek.dateiAuswerten();
		meinSignalListeErzeuger.setPfad("C:\\Users\\Fabian\\Documents\\pit\\csd.txt");
		start();
		break;
	default:
		start();
		break;
	}




}

void Menue::faktorenMenue()
{
	system("cls");
	menueKopf();
	cout<<"Untermenue Aeussere Faktoren"<<endl<<endl;
	cout<<"(1) Spannung [Volt]: "<< meineFaktoren.getSpannung() << " aendern" <<endl<<endl;
	cout<<"(2) Temperatur [Grad Celsius] : "<< meineFaktoren.getTemperatur()<< " aendern"<<endl<<endl;
	cout<<"(3) Prozess (1=slow, 2=typical, 3=fast) : "<< meineFaktoren.getProzess()<< " aendern"<<endl<<endl;
	cout<<"(4) Ausgabe errechneter Faktoren "<<endl<<endl;
	cout<<"(5) Debugmodus: ";
	if (meineFaktoren.debugVar){
		cout<< "ausschalten" << endl<<endl;
	}else{
		cout<< "einschalten" << endl<<endl;
	}
	cout<<"(6) Hauptmenue"<<endl<<endl<<endl;

	cout<<"Waehle einen Menuepunkt und bestaetige mit Enter:"<<endl;
	
	int eingabe;
	cin.clear();
	cin.sync();
	cin>>eingabe;
	

	switch(eingabe){
	case 1:
		double spannung;
		cout<<"Bitte geben Sie den gewuenschten Wert ein:"<<endl;
		cin.clear();
		cin.sync();
		cin>>spannung;
		meineFaktoren.setSpannung(spannung);
		faktorenMenue();
		break;
	case 2:
		double temperatur;
		cout<<"Bitte geben Sie den gewuenschten Wert ein:"<<endl;
		cin.clear();
		cin.sync();
		cin>>temperatur;
		meineFaktoren.setTemperatur(temperatur);
		faktorenMenue();
		break;
	case 3:
		short prozess;
		cout<<"Bitte geben Sie den gewuenschten Wert ein:"<<endl;
		do{
			cin.clear();
			cin.sync();
			cin>>prozess;
			if(prozess != 1 && prozess != 2 && prozess != 3){
				cout<<"Falsche Eingabe, bitte wiederholen:"<<endl;
			}
		}while(prozess != 1 && prozess != 2 && prozess != 3);
		meineFaktoren.setProzess(prozess);
		faktorenMenue();
		break;
	case 4:
		meineFaktoren.ausgabeFaktoren();
		break;
	case 5:
		if (meineFaktoren.debugVar){
			meineFaktoren.debugVar = false;
		}else{
			meineFaktoren.debugVar = true;
			meineFaktoren.setProzess(1);
			meineFaktoren.setSpannung(1.2);
			meineFaktoren.setTemperatur(55);//DEBUG
		}
		break;
	case 6:
		start();
		break;
	
	default:
		faktorenMenue();
		break;
	}
	faktorenMenue();


	
};

void Menue::bibliothekMenue(){
	system("cls");
	menueKopf();
	cout<<"Untermenue Bibliothek"<<endl<<endl;
	cout<<"(1) Pfad zur Bibliotheksdatei: "<< meineBibliothek.getPfad() <<endl<<endl;
	cout<<"(2) Ausgabe der Bibliotheksdatei "<<endl<<endl;
	cout<<"(3) Hauptmenue"<<endl<<endl<<endl;

	cout<<"Waehle einen Menuepunkt und bestaetige mit Enter:"<<endl;

	int eingabe;
	cin.clear();
	cin.sync();
	cin>>eingabe;
	string pfad;
	bool erfolgreich;
	switch(eingabe){
	case 1:
		cout<<"Bitte geben Sie den gewuenschten Pfad ein ('EXIT' zum abbrechen):"<<endl;
		cin.clear();
		cin.sync();
		//cin>>pfad;
		getline(cin, pfad);
		if(pfad != "EXIT" && pfad != "exit" && pfad != "Exit") {
			erfolgreich = meineBibliothek.pfadEinlesen(pfad);
			if(erfolgreich == false ) { 
				cout<<"Der Pfad konnte nicht eingelesen werden"<<endl;
				cout<<"Enter druecken zum fortfahren"<<endl;
				cin.clear();
				cin.sync();
			} else {
				meineBibliothek.dateiAuswerten();
			}
		}
		bibliothekMenue();
		break;
	case 2:
		meineBibliothek.dateiAusgabe();
		system("pause");
		bibliothekMenue();
		break;
	case 3:
		start();
		break;
	default:
		bibliothekMenue();
		break;
	}
};
void Menue::schaltwerkMenue(){

	system("cls");
	menueKopf();
	cout<<"Untermenue Schaltwerk"<<endl<<endl;
	cout<<"(1) Pfad zur Schaltwerksdatei: " <<meinSignalListeErzeuger.getdatei() <<endl<<endl;
	cout<<"(2) Ausgabe der Schaltwerksdatei" <<endl<<endl;
	cout<<"(3) Ausgabe der Signale"<<endl<<endl;
	cout<<"(4) Ausgabe der Graphenstruktur"<<endl<<endl;
	cout<<"(5) Hauptmenue"<<endl<<endl<<endl;

	cout<<"Waehle einen Menuepunkt und bestaetige mit Enter:"<<endl;

	int eingabe;
	cin.clear();
	cin.sync();
	cin>>eingabe;
	string pfad;

	switch(eingabe){
	case 1:
		
		cout<<"Bitte geben Sie den gewuenschten Pfad ein ('EXIT' zum abbrechen):"<<endl;
		cin.clear();
		cin.sync();
		//cin>>pfad;
		getline(cin, pfad);
		//Pfad der Schaltwerkelement
		if(pfad != "EXIT" && pfad != "exit" && pfad != "Exit") {
			meinSignalListeErzeuger.setPfad(pfad);
		}
		schaltwerkMenue();
		break;
	case 2:
		system("cls");
		meinSignalListeErzeuger.ausgabeSchaltnetzdatei();
		system("pause");
		schaltwerkMenue();
		break;
	case 3:
		meinSignalListeErzeuger.ausgabeSignale();
		system("pause");
		schaltwerkMenue();
		break;
	case 4:
		meinGraphErzeuger.graphBau(&meineBibliothek, meinSignalListeErzeuger.getSignale() , meinSignalListeErzeuger.getAnzahlSignale());
		meinGraphErzeuger.ausgabeGraphenstruktur();
		system("pause");
		schaltwerkMenue();
		break;
	case 5:
		start();
		break;
	default:
		schaltwerkMenue();
		break;
	}

};
void Menue::analyse(){

	meinGraphErzeuger.graphBau(&meineBibliothek, meinSignalListeErzeuger.getSignale() , meinSignalListeErzeuger.getAnzahlSignale());
	meinLaufzeitanalysator.reset();
	meinLaufzeitanalysator.init(&meineFaktoren, meinGraphErzeuger.getStartElement());
	bool egal = meinLaufzeitanalysator.analyse(meinSignalListeErzeuger.getFrequenz());
	//meinLaufzeitanalysator.berechnungLaufzeitEinzelgatter();
	//meinLaufzeitanalysator.dfs(meinGraphErzeuger.getStartElement());
	//Aufruf LaufzeitAnalysator
	//system("pause");
	start();
	
};