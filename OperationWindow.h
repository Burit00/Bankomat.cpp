#pragma once
#include "WindowAbstract.h"
#include "Button.h"

class OperationWindow : public WindowAbstract
{
private:
	Text accountBalanceText[2];
	RectangleShape accountBalanceTextBg;
	void setAccountBalanceText();
	Button depositeButton;
	void setDepositeButton();
	Button withdrawalButton;
	void setWithdrawalButton();
	Button logoutButton;
	void setLogoutButton();
	void setFields();
	void handleEvent(Event event);
public:
	OperationWindow(RenderWindow& window);
	void draw();
};

