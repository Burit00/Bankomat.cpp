#include "Cashmachine.h"
#include "GlobalVariables.h"
#include <fstream>
#include <iostream>

Cashmachine::Cashmachine():
	withdrawalLimit(2000)
{
	loadCash();
}

Cashmachine::~Cashmachine()
{
	saveCash();
}

void Cashmachine::loadCash() {
	std::ifstream nominalFile("assets/nominals.txt");
	int i = 0, numberOfNominal;

	while (nominalFile >> numberOfNominal) {
		cash.setNumberOfNominals(i++, numberOfNominal);
	}
}

void Cashmachine::saveCash() {
	std::ofstream nominalFile("assets/nominals.txt");

	for (int numOfNominal: cash.numberOfNominals) {
		nominalFile << numOfNominal << "	";
	}
}

PiggyBank Cashmachine::getCash()
{
	return cash;
}

void Cashmachine::deposite(PiggyBank deposite)
{
	for (int i = 0; i < PiggyBank::numberOfNominalTypes; i++) {
		cash.numberOfNominals[i] += deposite.numberOfNominals[i];
	}
	accService.addCashToAccount(deposite.calculateCash());
}

bool Cashmachine::isWithdrawalAvailable(int money)
{
	return (bool)(money <= withdrawalLimit && money <= cash.calculateCash() && cash.calculateForWithdrawal(money).calculateCash() == money);
}

PiggyBank Cashmachine::wihdrawal(int money)
{
	if (!isWithdrawalAvailable(money)) return PiggyBank();

	PiggyBank tempWithdrawal = cash.calculateForWithdrawal(money);

	for(int i = PiggyBank::numberOfNominalTypes - 1; i >= 0; i--)
		cash.numberOfNominals[i] -= tempWithdrawal.numberOfNominals[i];
	accService.getActiveAccount().withdrawal(tempWithdrawal.calculateCash());

	return tempWithdrawal;
}
