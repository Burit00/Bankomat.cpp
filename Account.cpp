#include "Account.h"

Account::Account(std::string pinCode, int AccountBalance):
	pin(pinCode), cash(AccountBalance)
{}

void Account::deposite(int cash)
{
	if (cash < 0) return;
	this->cash += cash;
}

bool Account::withdrawal(int cash)
{
	if (this->cash < cash) return false;
	this->cash -= cash;
	return true;
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
