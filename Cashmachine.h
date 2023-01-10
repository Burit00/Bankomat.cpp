#pragma once
#include "PiggyBank.h"

class Cashmachine
{
private:
	PiggyBank cash;
	void loadCash();
public:
	Cashmachine();
	PiggyBank getCash();
	void deposite(PiggyBank deposite);
};

