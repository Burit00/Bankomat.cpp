#pragma once
#include "WindowAbstract.h"
#include "Button.h"

class OperationWindow : public WindowAbstract
{
private:
	Text accountBalanceText[2];
	RectangleShape accountBalanceTextBg;
	void setAccountBalanceText();
	Button depositButton;
	void setPayInButton();
	Button withdrawButton;
	void setPayOutButton();
	Button logoutButton;
	void setLogoutButton();
	void handleEvent(Event event) override;
	void setFields() override;
public:
	OperationWindow(RenderWindow& window);
	void draw() override;
};

