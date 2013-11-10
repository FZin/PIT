#include "stdafx.h"
#include "Faktoren.h"


Faktoren::Faktoren()
{
	spannung = 0.0;
	temperatur = 0.0;
	prozess = 0.0;
	spannungFaktor = 0.0;
	temperaturFaktor = 0.0;
	prozessFaktor = 0.0;
}


Faktoren::~Faktoren()
{
}


bool Faktoren::berechneSpannungFaktor(double spg)
{
	return false;
}


bool Faktoren::berechneTemperaturFaktor(double temp)
{
	return false;
}


bool Faktoren::berechneProzessFaktor(short prz)
{
	return false;
}


double Faktoren::berechneFaktor(double value, double arr, int laenge)
{
	return 0;
}


double Faktoren::interpolation(double value, double x1, double x2, double y1, double y2)
{
	return 0;
}


void Faktoren::ausgabeFaktoren()
{
}


double Faktoren::getSpannung()
{
}


double Faktoren::getProzess()
{
}


double Faktoren::getTemperatur()
{
}


void Faktoren::getFaktoren(double spgFaktor, double tmpFaktor, double przFaktor)
{
}

bool Faktoren::setSpannung(double spannung)
{
	
}


bool Faktoren::setTemperatur(double temperatur)
{

}


bool Faktoren::setProzess(double prozess)
{

}