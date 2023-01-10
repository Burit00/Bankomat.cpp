#include <fstream>
#include <iostream>
#include "AccountService.h"

AccountService::AccountService() :
	activeAccount("", 0),
	isAccountAuthorised(false)
{
	loadAccounts();
}

bool AccountService::authorise(const std::string pin)
{
	for (int i = 0; i < accounts.size(); i++) {
		if (accounts.at(i).getPin() == pin) {
			activeAccount = accounts[i];
			isAccountAuthorised = true;
			return true;
		}
	}
	return false;
}

void AccountService::loadAccounts() {
	std::ifstream accountsFile("src/assets/accounts.txt");
	std::string pin("");
	int cash{};
	while (accountsFile >> pin >> cash) {
		Account account(pin, cash);
		accounts.push_back(account);
	}
}

bool AccountService::isAuthorised() {
	return isAccountAuthorised;
}

Account& AccountService::getActiveAccount()
{
	return activeAccount;
}

void AccountService::logout()
{
	isAccountAuthorised = false;
}

void AccountService::addCashToAccount(const int money)
{
	activeAccount.cash += money;
}
