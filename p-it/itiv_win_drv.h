/* 
    Windows-Treiber für das ITIV-Windows-Gerät
    ------------------------------------------
    
    Autor:              Stephan Werner
    letzte Änderung:    07.09.2013
*/

#ifndef ITIV_WIN_DRV_H
#define ITIV_WIN_DRV_H

#include <stdint.h>

/*
	Struktur für die Geräte-Konfiguration
*/
typedef struct {
    uint32_t    DeviceId;
    volatile uint8_t*    BaseAddress;
} ItivDev_Config;


#define	CTRL_REG	0x00000000
#define	STAT_REG	0x00000004
#define	DATA_REG	0x00000008

/*
	Initialisieren der Gerätestruktur

	Die Funktion nimmt den Gerätenamen entgegen, um die
	Konfiguration des Gerätes zu ermitteln.
	Zurückgegeben wird ein Pointer auf eine Struktur vom Typ
		ItivDev_Config
	Der Pointer zeigt auf eine Struktur, welche die Hardware-ID
	und die Basisadresse enthält.
*/
extern ItivDev_Config* ItivDev_GetConfigByName(const char* DevName);

/*
	Freigeben des Gerätes

	Um das Gerät wieder freizugeben, muss der Pointer als
	Argument übergeben werden, der zuvor von der Init-Funktion
	zurückgegeben wurde.
*/
extern uint32_t ItivDev_ReleaseDevice(ItivDev_Config* DevStructure);

#endif
