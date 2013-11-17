// p-it.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "Faktoren.h"
#include <iostream>

#include "Menue.h"

//debug
//#include "Bibliothek.h"
//using namespace std;

int main()
{
	Menue meinMenue;
	meinMenue.start();

	//debug:
	//Bibliothek test;
	//bool ja = test.pfadEinlesen("C:\\Users\\Stefan\\Documents\\Studium\\3.Semester\\IT-Praktikum\\bib.txt");

	//GatterTyp* typ = test.getBibElement("inv1a");
	//cout<<typ;
	//getchar();
	//getchar();

	return 0;
}

