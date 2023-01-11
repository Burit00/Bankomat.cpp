#include "Cashmachine.h"
#include "GlobalVariables.h"
#include <fstream>
#include <iostream>

Cashmachine::Cashmachine():
	withdrawalLimit(2000)
{
	loadCash();
}

void Cashmachine::loadCash() {
	std::ifstream nominalFile("assets/nominals.txt");
	int i = 0, numberOfNominal;

	while (nominalFile >>  numberOfNominal) {
		cash.setNumberOfNominals(i++, numberOfNominal);
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
	return (money <= withdrawalLimit && money < cash.calculateCash());
}

PiggyBank Cashmachine::wihdrawal(int money)
{
	PiggyBank tempWithdrawal;
	if (!isWithdrawalAvailable(money)) return tempWithdrawal;

	for (int i = PiggyBank::numberOfNominalTypes - 1; i >= 0; i--) {
		const int maxNominalValue = (money / PiggyBank::nominalsTypes[i]);
		const int avaliableNominalFromCashmachine = cash.numberOfNominals[i] < maxNominalValue ? cash.numberOfNominals[i] : maxNominalValue;

		cash.numberOfNominals[i] -= avaliableNominalFromCashmachine;
		tempWithdrawal.setNumberOfNominals(i, avaliableNominalFromCashmachine);
		money -= avaliableNominalFromCashmachine * PiggyBank::nominalsTypes[i];

		if (money == 0) break;
	}
	accService.getActiveAccount().withdrawal(tempWithdrawal.calculateCash());

	return tempWithdrawal;
}
