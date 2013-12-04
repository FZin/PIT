#ifndef LAUFZEITANALYSATOR_H
#define LAUFZEITANALYSATOR_H

#include <cstdlib>
#include "Faktoren.h"
#include "Bibliothek.h"
#include "SchaltwerkElement.h"
#include "ListenElement.h"
#include "GraphErzeuger.h"
#include <map>



class LaufzeitAnalysator
{
private:
	Faktoren* faktoren;
	ListenElement* startElement;
	long frequenz;
	string uebergangspfad;
	string ausgangspfad;
	double laufzeitUebergangspfad;
	double laufzeitAusgangspfad;
	struct DFS_Daten {SchaltwerkElement* VaterElement; double PfadLaufzeit;};
	map<SchaltwerkElement*, DFS_Daten> DFS_Zwischenspeicher;

public:
	LaufzeitAnalysator();
	~LaufzeitAnalysator();
	void init(Faktoren* f, ListenElement* s);
	void berechnungLaufzeitEinzelgatter(void);
	void dfs_Visit(SchaltwerkElement* k, SchaltwerkElement* s);
	void dfs(ListenElement* s);
	bool zyklensuche(SchaltwerkElement* v);
	void fehlerbehandlung(void);
	void reset(void);
	bool analyse(long sollFrequenz);
};
#endif
