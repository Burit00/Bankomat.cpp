#pragma once
#include <SFML/Graphics.hpp>
#include "WindowAbstract.h"
#include "Button.h"
#include "InputBox.h"
using namespace sf;

class WithdrawWindowal : public WindowAbstract
{
	bool isTransactionComplete;
	PiggyBank withdrawal;
	Text accountBalanceText[2];
	RectangleShape accountBalanceTextBg;
	void setAccountBalanceText();

	InputBox cashInput;
	void setCashInput();
	sf::Text alertText;
	void setAlertText(string content);
	Button confirmButton;
	void setConfirmButton();

	Text transactionDetailsTitle;
	Text withdrawalAmount;
	vector<vector<Text>> transactionDetailsTexts;
	RectangleShape transactionDetailsBg;
	RectangleShape transactionDetailsLine;
	void prepareTransactionDetailsView();
	void updateTransactionDetailsView();

	Button backButton;
	void setBackButton();
	void setFields();
	void handleEvent(Event event);
	void onMouseMoved(Event event);
	void onClick(Event event);
	void onType(Event event);
public:
	WithdrawWindowal(RenderWindow& window);
	void draw();
};

