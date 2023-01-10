#pragma once
#include "Account.h"
#include <vector>

class AccountService
{
private:
	Account activeAccount;
	bool isAccountAuthorised;
	std::vector<Account> accounts;
	void loadAccounts();
public:
	AccountService();
	Account& getActiveAccount();
	void logout();
	bool authorise(const std::string pin);
	bool isAuthorised();
	void addCashToAccount(const int money);
};
