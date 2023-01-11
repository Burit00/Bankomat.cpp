#pragma once
#include "PiggyBank.h"

class Cashmachine
{
private:
	PiggyBank cash;
	void loadCash();
	void saveCash();
public:
	const int withdrawalLimit;
	Cashmachine();
	~Cashmachine();
	PiggyBank getCash();
	void deposite(PiggyBank deposite);
	PiggyBank wihdrawal(int money);
	bool isWithdrawalAvailable(int money);
};

