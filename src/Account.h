#pragma once
#include <string>
#include <SFML/Graphics/Color.hpp>
class Account
{
	friend class AccountService;
private:
	std::string pin;
	int cash = 0;
public:
	Account(std::string pinCode, int AccountBalance);
	void payIn(int cash);
	void payOut(int cash);
	int getAccountBalance();
	std::string getPin() const;
	Account& operator=(Account& account);
	bool operator==(Account& account);
};

