#pragma once
#include <string>
#include "PiggyBank.h"

class Cashmachine
{
private:
	PiggyBank cash;
	int withdrawalLimit = 0;
	std::string basePath = "assets/nominalsBase.txt";
	void loadCash();
	void saveCash();
public:
	Cashmachine();
	~Cashmachine();
	PiggyBank getCash() const;
	const int getWithdrawalLimit() const;
	void deposite(PiggyBank deposite);
	PiggyBank wihdrawal(int money);
	bool isWithdrawalAvailable(int money);
};

