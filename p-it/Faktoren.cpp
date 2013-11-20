
#include "Faktoren.h"

//#include <iomanip>

using namespace std;


Faktoren::Faktoren() {
	spannung = 0.0;
	temperatur = 0.0;
	prozess = 0.0;
	spannungFaktor = 0.0;
	temperaturFaktor = 0.0;
	prozessFaktor = 0.0;
	debugVar = false;
	//debugVar = !( InfoFromItivDevice()); //Auskommentiert, damit sich das Programm ohne ITIVDevice ausführen lässt. Anderenfalls müssen sowohl ITIVDevice als auch VS als Admin gestartet werden.
}


Faktoren::~Faktoren() {
}


/*
Diese Funktion berechnet aus einer gegebenen Spannung den Spannungsfaktor und gibt false zurück, 
falls die Spannung nicht nicht innerhalb der vom Faktoren-Array bestimmten Grenzen liegt.
*/

bool Faktoren::berechneSpannungFaktor( double spg ) {
	double spFaktoren[7][2] = { { 1.08, 1.121557 }, { 1.12, 1075332 }, { 1.16, 1.035161 }, { 1.20, 1.0 }, { 1.24, 0.968480 }, { 1.28, 0.940065 }, { 1.32, 0.914482 } };
	unsigned int asize = sizeof ( spFaktoren ) / sizeof( spFaktoren[0] );
	if( !(( spg < spFaktoren[0][0] ) || ( spg > spFaktoren[asize - 1][0] ))) {
		spannungFaktor = berechneFaktor( spg, spFaktoren, asize );
		return true;
	}
	cout << "ERR: Die angegebene Spannung liegt nicht innerhalb der vorgegebenen Grenzen!" << endl;
	return false;
}


/*
Diese Funktion berechnet aus einer gegebenen Temperatur den Temperaturfaktor und gibt false zurück, 
falls die Temperatur nicht nicht innerhalb der vom Faktoren-Array bestimmten Grenzen liegt.
*/

bool Faktoren::berechneTemperaturFaktor( double temp ) {
	double teFaktoren[15][2] = { { -25, 0.897498 }, { -15, 0.917532 }, { 0, 0.948338 }, { 15, 0.979213 }, { 25, 1.0 }, { 35, 1.020305 }, { 45, 1.040540 }, { 55, 1.061831 }, { 65, 1.082983 }, { 75, 1.103817 }, { 85, 1.124124 }, { 95, 1.144245 }, { 105, 1.164563 }, { 115, 1.184370 }, { 125, 1.204966 } };
	unsigned int asize = sizeof ( teFaktoren ) / sizeof( teFaktoren[0] );
	if( !(( temp < teFaktoren[0][0] ) || ( temp > teFaktoren[asize - 1][0] ))) {
		temperaturFaktor = berechneFaktor( temp, teFaktoren, asize );
		return true;
	}
	cout << "ERR: Die angegebene Temperatur liegt nicht innerhalb der vorgegebenen Grenzen!" << endl;
	return false;
}


/*
Diese Funktion weist dem Prozessfaktor den zum gegebenen Prozess gehoerenden Wert zu.
Gibt false zurück, falls der Prozess im Faktoren-Array nicht existiert.
*/

bool Faktoren::berechneProzessFaktor( short prz ) {
	double prFaktoren[3][2] = { { 1, 1.174235 }, { 2, 1.0 }, { 3, 0.876148 } };
	unsigned int asize = sizeof( prFaktoren ) / sizeof( prFaktoren[0] );
	for( unsigned int i = 0; i < asize; i++ ) {
		unsigned int help = prz;
		if( help == prFaktoren[i][0] ) {
			prozessFaktor = prFaktoren[i][1];
			return true;
		}
	}
	cout << "ERR: Der angegebene Prozess liegt nicht innerhalb der vorgegebenen Grenzen!" << endl;
	return false;
}

/*
berechneFaktor findet in einer Xx2-Matrix den zu <value> gehörenden Wert. Falls dieser nicht existiert wird er interpoliert 
*/

double Faktoren::berechneFaktor( double value, double arr[][2], unsigned int laenge ) {
	double r;
	for( unsigned int i = 0; i < laenge; i++ ) {
		if(( arr[i][0] <= value ) && ( value < arr[i + 1][0] )) {
			r = interpolation( value, arr[i][0], arr[i + 1][0], arr[i][1], arr[i + 1][1] );
		}
	}
	return r;
}

/*
Interpolation eines zu <value> gehoerenden Wertes zwischen 2 gegebenen Punkten
*/

double Faktoren::interpolation( double value, double x1, double x2, double y1, double y2 ) {
	double ip;
	ip = (( y2 - y1 ) / ( x2 - x1 ) * ( value - x1 )) + y1;
	return ip;
}

/*
Schreibt die berechneten Faktoren in die Standardausgabe
*/

void Faktoren::ausgabeFaktoren() {
	cout << "Faktoren: KV: " << spannungFaktor << "\|KT: " << temperaturFaktor << "\|KP: " << prozessFaktor << endl;
}


double Faktoren::getSpannung() {
	return spannung;
}


double Faktoren::getProzess() {
	return prozess;
}


double Faktoren::getTemperatur() {
	return temperatur;
}


/*
Gibt die Faktoren als Referenz zurueck
*/

void Faktoren::getFaktoren( double& spgFaktor, double& tmpFaktor, double& przFaktor ) {
		spgFaktor = spannungFaktor;
		tmpFaktor = temperaturFaktor;
		przFaktor = prozessFaktor;
}


/*
Setzt die Spannung und berechnet den Spannungsfaktor.
Gibt false zurück, falls die Spannung nicht in definierten Grenzen liegt.
*/

bool Faktoren::setSpannung( double spannung ) {
	this->spannung = spannung;
	return berechneSpannungFaktor( this->spannung );
}


/*
Setzt die Temperatur und berechnet den Temperaturfaktor.
Gibt false zurück, falls die Temperatur nicht in definierten Grenzen liegt.
*/

bool Faktoren::setTemperatur( double temperatur ) {
	this->temperatur = temperatur;
	return berechneTemperaturFaktor( this->temperatur );
}

/*
Setzt dden Prozess und berechnet den Prozessfaktorfaktor.
Gibt false zurück, falls der Prozess nicht existiert.
*/

bool Faktoren::setProzess( short prozess ) {
	this->prozess = prozess;
	return berechneProzessFaktor( this->prozess );
}

/*
Misst mit Hilfe des ITIVDevices Spannung, Temperatur und Prozess. VS und das Device müssen mit Administratorechten gestartet werden
*/

bool Faktoren::InfoFromItivDevice() {
	ItivDev_Config* DevPtr;
	DevPtr = ItivDev_GetConfigByName( "Global\\ITIV_WindowsDevice" );
	//volatile uint32_t* baseAddr = (uint32_t*)DevPtr->BaseAddress; //Caste die BaseAdresse als uint32 um den gesamten Speicherbereich ansprechen zu können
	//volatile uint32_t* reg_ctrl = baseAddr;
	//volatile uint32_t* reg_stat = baseAddr + 1;
	//volatile uint32_t* reg_data = baseAddr + 2;
	double neuerWert;
	int neuerInt;
	bool err = false;
	for( int i = 1; i < 4; i++ ) {
		err = false;
		while( !err ) {
			*( int* )( DevPtr->BaseAddress + CTRL_REG + 1 ) |= ~( 1 << 0 );
			while( !( *( int* )( DevPtr->BaseAddress + STAT_REG + 3) & 0x01 ));
			*( int* )( DevPtr->BaseAddress + CTRL_REG ) = i;
			*( int* )( DevPtr->BaseAddress + CTRL_REG + 1 ) |= ( 1 << 0 );
			while( *( int* )( DevPtr->BaseAddress + STAT_REG + 1 ) & 0x01 );
			_sleep(100); // Warte 100ms, da es sonst vorkommen kann, dass das DONE-Bit noch nicht gesetzt ist.
			if( *( int* )( DevPtr->BaseAddress + STAT_REG + 2 ) & 0x01 ) {
				switch( i ) {
				case 1:
					neuerWert = *( double* )( DevPtr->BaseAddress + DATA_REG ); //Greift nur auf die ersten 8bit des DATAREG zu, ist aber von ausreichender Genauigkeit 
					err = setSpannung( neuerWert );
					break;
				case 2:
					neuerInt = *( int* )( DevPtr->BaseAddress + DATA_REG );
					err = setTemperatur( neuerInt );
					break;
				case 3:
					neuerInt = *( int* )( DevPtr->BaseAddress + DATA_REG );
					err = setProzess( neuerInt + 1 );
				default:
					break;
				}
			}else {
				if( *( int* )( DevPtr->BaseAddress + STAT_REG ) & 0x01 ) {
					cout << "Error";
				}
			}
		}
	}
	ItivDev_ReleaseDevice( DevPtr );	
	return true;
}
