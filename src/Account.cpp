#include "Account.h"

Account::Account(std::string pinCode, int AccountBalance):
	pin(pinCode), cash(AccountBalance)
{}

void Account::payIn(int cash)
{
	if (cash < 0) return;
	this->cash += cash;
}

void Account::payOut(int cash)
{
	if (this->cash < cash) return;
	this->cash -= cash;
}

int Account::getAccountBalance()
{
	return this->cash;
}

std::string Account::getPin() const
{
	return this->pin;
}

Account& Account::operator=(Account& account)
{
	this->pin = account.pin;
	this->cash = account.cash;
	return *this;
}

bool Account::operator==(Account& account)
{
	return this->pin == account.pin;
}
