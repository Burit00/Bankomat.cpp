#pragma once
#include "WindowAbstract.h"
#include "InputBox.h"
#include "Button.h"

class LoginWindow : public WindowAbstract
{
private:
	Text loginTexts[5];
	RectangleShape loginTextBg;
	void setLoginField();
	InputBox pinInput;
	void setPinInput();
	Button confirmButton;
	void setConfirmButton();
	Text alertText;
	void setAlertText();
	void loginFailedHandle();
	void handleEvent(Event event);
	void setFields();
	void draw();
public:
	LoginWindow(RenderWindow& window);
};

