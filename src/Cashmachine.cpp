#include "Cashmachine.h"
#include "GlobalVariables.h"
#include <fstream>

Cashmachine::Cashmachine()
{
	loadCash();
}

void Cashmachine::loadCash() {
	std::ifstream nominalFile("src/assets/nominals.txt");
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
