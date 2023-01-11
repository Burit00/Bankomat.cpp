#pragma once
#include "PiggyBank.h"

class Cashmachine
{
private:
	PiggyBank cash;
	void loadCash();
public:
	const int withdrawalLimit;
	Cashmachine();
	PiggyBank getCash();
	void deposite(PiggyBank deposite);
	bool isWithdrawalAvailable(int money);
	PiggyBank wihdrawal(int money);
};

