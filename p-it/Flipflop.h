#pragma once
#include "gattertyp.h"
class Flipflop :
	public GatterTyp
{
public:
	Flipflop(void);
	~Flipflop(void);
private:
	short setupTime;
	short holdTime;
	short lastKapazitaetClock;
public:

	short getSetupTime(void)
	{
		return setupTime;
	}

	short getHoldTime(void)
	{
		return holdTime;
	}

	short getLastKapazitaetClock(void)
	{
		return lastKapazitaetClock;
	}
	bool getIsFlipflop();

	void setSetupTime(short st)
	{
		setupTime = st;
	}

	void setHoldTime(short ht)
	{
		holdTime = ht;
	}

	void setLastKapazitaetClock(short lkc)
	{
		lastKapazitaetClock = lkc;
	}
};

