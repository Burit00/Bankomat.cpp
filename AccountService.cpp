#include <fstream>
#include <iostream>
#include "AccountService.h"

AccountService::AccountService() {
	loadAccounts();
}

AccountService::~AccountService() {
	logout();
	saveAccounts();
}

bool AccountService::authorise(const std::string pin)
{
	for (Account& account: accounts) {
		if (account.getPin() == pin) {
			activeAccount = account;
			isAccountAuthorised = true;
			return true;
		}
	}
	return false;
}

void AccountService::loadAccounts() {
	std::ifstream accountsFile(basePath);
	std::string pin("");
	int cash{};
	while (accountsFile >> pin >> cash) {
		Account account(pin, cash);
		accounts.push_back(account);
	}
}

void AccountService::saveAccounts() {
	std::ofstream accountsFile(basePath);
	for (Account account: accounts) {
		accountsFile << account.pin << "	" << account.cash << "\n";
	}
}

bool AccountService::isAuthorised() {
	return isAccountAuthorised;
}

Account& AccountService::getActiveAccount() {
	return activeAccount;
}

void AccountService::logout() {
	isAccountAuthorised = false;
	for (Account& account : accounts) {
		if (account == activeAccount)
			account = activeAccount;
	}
}

void AccountService::addCashToAccount(const int money) {
	activeAccount.cash += money;
}
