#pragma once
#include "WindowAbstract.h"
#include "InputBox.h"
#include "Button.h"

class LoginWindow : public WindowAbstract
{
private:
	Texture bg;
	void setBackground();
	InputBox pinInput;
	void setPinInput();
	Button confirmButton;
	void setConfirmButton();
	Text validationText;
	void setValidationText();
	void loginFailedHandle();
	void handleEvent(Event event) override;
	void setFields() override;
public:
	LoginWindow(RenderWindow& window);
	void draw();
};

