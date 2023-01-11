#pragma once
#include <string>
class Account
{
	friend class AccountService;
private:
	std::string pin;
	int cash = 0;
public:
	Account(std::string pinCode = "", int AccountBalance = 0);
	void deposite(int cash);
	bool withdrawal(int cash);
	int getAccountBalance();
	std::string getPin() const;
	Account& operator=(Account& account);
	bool operator==(Account& account);
};

