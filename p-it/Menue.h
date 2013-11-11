#include "Faktoren.h"
#include "Bibliothek.h"
#include "SignalListeErzeuger.h"
#include "GraphErzeuger.h"
#include "LaufzeitAnalysator.h"
#include "Signal.h"

class Menue
{
public:
	Menue();
	~Menue();
private:
	Faktoren meineFaktoren;
	Bibliothek meineBibliothek;
	SignalListeErzeuger meinSignalListeErzeuger;
	GraphErzeuger meinGraphErzeuger;
	LaufzeitAnalysator meinLaufzeitAnalysator;
	Signal* signale;
public:
	void start();
private:
	void faktorenMenue();
	void bibliothekMenue();
	void schaltwerkMenue();
	void analyse();
	void menueKopf();
};
