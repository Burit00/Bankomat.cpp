#include "Cashmachine.h"
#include "GlobalVariables.h"
#include <fstream>

Cashmachine::Cashmachine()
{
	loadCash();
}

Cashmachine::~Cashmachine() {
	saveCash();
}

void Cashmachine::loadCash() {
	std::ifstream nominalFile(basePath);
	int i = 0, numberOfNominal;

	nominalFile >> withdrawalLimit;
	while (nominalFile >> numberOfNominal) {
		cash.setNumberOfNominals(i++, numberOfNominal);
	}
}

void Cashmachine::saveCash() {
	std::ofstream nominalFile(basePath);
	nominalFile << withdrawalLimit << "	";
	for (int numOfNominal: cash.numberOfNominals) {
		nominalFile << numOfNominal << "	";
	}
}

PiggyBank Cashmachine::getCash() const {
	return cash;
}

const int Cashmachine::getWithdrawalLimit() const {
	return withdrawalLimit;
}

void Cashmachine::deposite(PiggyBank deposite) {
	for (int i = 0; i < PiggyBank::numberOfNominalTypes; i++) {
		cash.numberOfNominals[i] += deposite.numberOfNominals[i];
	}
	accService.addCashToAccount(deposite.calculateCash());
}

bool Cashmachine::isWithdrawalAvailable(int money) {
	return (bool)(money <= withdrawalLimit && money <= cash.calculateCash() && cash.calculateForWithdrawal(money).calculateCash() == money);
}

PiggyBank Cashmachine::wihdrawal(int money) {
	if (!isWithdrawalAvailable(money)) return PiggyBank();

	PiggyBank tempWithdrawal = cash.calculateForWithdrawal(money);

	for(int i = PiggyBank::numberOfNominalTypes - 1; i >= 0; i--)
		cash.numberOfNominals[i] -= tempWithdrawal.numberOfNominals[i];
	accService.getActiveAccount().withdrawal(tempWithdrawal.calculateCash());

	return tempWithdrawal;
}
