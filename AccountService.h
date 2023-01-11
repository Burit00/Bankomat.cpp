#pragma once
#include "Account.h"
#include <vector>
#include <string>

class AccountService
{
private:
	Account activeAccount;
	std::vector<Account> accounts;
	bool isAccountAuthorised = false;
	std::string basePath = "assets/accountsBase.txt";
	void loadAccounts();
	void saveAccounts();
public:
	AccountService();
	~AccountService();
	Account& getActiveAccount();
	void logout();
	bool authorise(const std::string pin);
	bool isAuthorised();
	void addCashToAccount(const int money);
};
