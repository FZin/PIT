#include "Faktoren.h"
#include "Bibliothek.h"
#include "SignalListeErzeuger.h"
#include "GraphErzeuger.h"
#include "LaufzeitAnalysator.h"
#include "Signal.h"

class menue
{
public:
	menue();
	~menue();
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
	void menue::bibliothekMenue();
	void menue::schaltwerkMenue();
	void menue::analyse();
	void menue::menueKopf();
};
