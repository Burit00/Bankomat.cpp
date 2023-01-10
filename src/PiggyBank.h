#pragma once

class PiggyBank
{
	friend class Cashmachine;
private:
	int numberOfNominals[9];
public:
	static const int nominalsTypes[9];
	static const int numberOfNominalTypes;
	PiggyBank();
	void incrementNominal(int nominalIndex);
	bool setNumberOfNominals(int nominalIndex, int amountOfNominals);
	int* getNumberOfNominals();
	void resetPiggyBank();
	int calculateCash();

};

