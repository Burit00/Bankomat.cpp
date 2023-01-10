#include "LoginWindow.h"
#include "GlobalVariables.h"
#include "InputBox.h"
#include "Button.h"


LoginWindow::LoginWindow(RenderWindow& window):
	WindowAbstract(window),
	confirmButton("Zatwierdz"),
	validationText(appConf.getText())
{}

void LoginWindow::setFields() {
	setPinInput();
	setConfirmButton();
	setBackground();
	setValidationText();
}

void LoginWindow::setBackground()
{
	bgTexture.loadFromFile("signUpBg.png");
}

void LoginWindow::setPinInput()
{
	pinInput.setText("");
	pinInput.isPassword();
	pinInput.setLimit(8);
	pinInput.setType(NUMBER);
	pinInput.setFocused(true);
	RectangleShape inputBg = pinInput.background;
	inputBg.setPosition({ 886, 253 });
	inputBg.setSize({ 270, 55 });
	inputBg.setFillColor(appConf.primaryClr);
	pinInput.setBackgound(inputBg);

}

void LoginWindow::setConfirmButton()
{
	confirmButton.setPosition({ 806, 650 });
}

void LoginWindow::setValidationText()
{
	validationText.setFillColor(Color(0x272727FF));
	validationText.setPosition({ 806, 325 });
}

void LoginWindow::loginFailedHandle()
{
			validationText.setString("wprowadzony PIN jest niepoprawny");
}

void LoginWindow::handleEvent(Event event)
{
	switch (event.type) {
	case Event::Closed:
		window.close();
		break;
	case Event::MouseMoved:
		confirmButton.isMouseOver(window);
		break;
	case Event::MouseButtonPressed:
		pinInput.setFocused(pinInput.isMouseOver(window));
		if (confirmButton.isMouseOver(window)) {
			if (!accService.authorise(pinInput.getText())) {
				loginFailedHandle();
			}
		}
		break;
	case Event::TextEntered:
		pinInput.onTyped(event);
		if (pinInput.getFocused()) 
			validationText.setString("");
		break;
	}
}

void LoginWindow::draw()
{
	setFields();
	Sprite background;
	background.setTexture(bgTexture);
	Event event;

	while (window.isOpen() && !accService.isAuthorised()) {
		while (window.pollEvent(event)) {
			handleEvent(event);
		}
		window.clear();
		window.draw(background);
		window.draw(pinInput);
		if (!validationText.getString().isEmpty()) 
			window.draw(validationText);
		window.draw(confirmButton);
		window.display();
	}
}
