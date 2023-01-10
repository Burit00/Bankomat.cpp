#pragma once
#include "WindowAbstract.h"
#include "Button.h"
#include "InputBox.h"
class DepositWindow : public WindowAbstract
{
private:
	PiggyBank deposite;
	std::vector<Button> nominalButtons;
	void setNominalsButtons();
	Text description1;
	Text description2;
	RectangleShape nominalBtnBg;
	void setNominalBtnBg();
	InputBox cashInput;
	void setCashInput();
	Button resetButton;
	void setResetButton();
	Button depositeButton;
	void setDepositeButton();
	Button backButton;
	void setBackButton();
	void setFields();
	void handleEvent(Event event);
	void onMouseMoved(Event event);
	void onClick(Event event);
public:
	DepositWindow(RenderWindow& window);
	void draw() override;
};

