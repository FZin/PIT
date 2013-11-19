#ifndef LISTENELEMENT_H
#define LISTENELEMENT_H


#include <iostream>

#include "SchaltwerkElement.h"

class ListenElement
{
private:
	SchaltwerkElement* schaltwerkElement;
	ListenElement* next;

public:
	ListenElement();
	~ListenElement();
	SchaltwerkElement* getSchaltwerkElement() { return schaltwerkElement;};
	ListenElement* getNextListenElement() {return next; };
	void setSchaltwerkElement( SchaltwerkElement* schaltwerEl ) { schaltwerkElement = schaltwerEl; }; 
	void setNextElement( ListenElement* nextEl ) { next =nextEl; };
};
#endif