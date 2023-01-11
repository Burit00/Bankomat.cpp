#include "PiggyBank.h"

const int PiggyBank::nominalsTypes[9] = { 1, 2, 5, 10, 20, 50, 100, 200, 500 };
const int PiggyBank::numberOfNominalTypes = 9;

PiggyBank::PiggyBank()
{
	resetPiggyBank();
}

void PiggyBank::incrementNominal(int nominalIndex)
{
	numberOfNominals[nominalIndex]++;
}

int* PiggyBank::getNumberOfNominals()
{
	return numberOfNominals;
}

void PiggyBank::resetPiggyBank()
{
	for (int& nominal : numberOfNominals) nominal = 0;
}

int PiggyBank::calculateCash()
{
	int sum = 0;
	for (int i = 0; i < numberOfNominalTypes; i++) {
		sum += nominalsTypes[i] * numberOfNominals[i];
	}

	return sum;
}

bool PiggyBank::setNumberOfNominals(int nominalIndex, int amountOfNominals)
{
	if (amountOfNominals < 0) return false;
	numberOfNominals[nominalIndex] = amountOfNominals;
	return true;
}

PiggyBank PiggyBank::calculateForWithdrawal(int money)
{
	PiggyBank tempWithdrawal;

	if (money >= calculateCash()) return tempWithdrawal;

	for (int i = PiggyBank::numberOfNominalTypes - 1; i >= 0 && money > 0; i--) {
		const int maxNominalValue = (money / PiggyBank::nominalsTypes[i]);
		const int avaliableNominalFromCashmachine = numberOfNominals[i] < maxNominalValue ? numberOfNominals[i] : maxNominalValue;

		tempWithdrawal.setNumberOfNominals(i, avaliableNominalFromCashmachine);
		money -= avaliableNominalFromCashmachine * PiggyBank::nominalsTypes[i];
	}

	return tempWithdrawal;
}