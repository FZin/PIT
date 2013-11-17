#ifndef GATTERTYP_H
#define GATTERTYP_H

#include<string>
using namespace std;

class GatterTyp
{
protected:
	string name;
	double grundlaufzeit;
	short lastFaktor;
	short lastKapazitaet;
	short eingaenge;
public:
	GatterTyp(void);
	~GatterTyp(void);
	virtual bool getIsFlipflop(void);

	//Inline get- und set-Methoden
	string getName(void)
	{
		return name;
	}

	double getGrundlaufzeit(void)
	{
		return grundlaufzeit;
	}

	short getLastFaktor(void)
	{
		return lastFaktor;
	}

	short getLastKapazitaet(void)
	{
		return lastKapazitaet;
	}

	short getEingaenge(void)
	{
		return eingaenge;
	}

	void setName(string n)
	{
		name = n;
	}

	void setGrundLaufzeit(double gl)
	{
		grundlaufzeit = gl;
	}

	void setLastKapazitaet(short lk)
	{
		lastKapazitaet = lk;
	}

	void setLastFaktor(short lf)
	{
		lastFaktor = lf;
	}

	void setEingaenge(short ei)
	{
		eingaenge = ei;
	}
};
#endif

