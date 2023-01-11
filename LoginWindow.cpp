#include "LoginWindow.h"
#include "GlobalVariables.h"
#include "InputBox.h"
#include "Button.h"

LoginWindow::LoginWindow(RenderWindow& window):
	WindowAbstract(window),
	confirmButton("Zatwierdz"),
	alertText(appSett.getText())
{}

void LoginWindow::setFields() {
	setPinInput();
	setConfirmButton();
	setBackground();
	setAlertText();
}

void LoginWindow::setBackground()
{
	bgTexture.loadFromFile("assets/signUpBg.png");
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
	inputBg.setFillColor(appSett.primaryClr);
	pinInput.setBackgound(inputBg);
}

void LoginWindow::setConfirmButton()
{
	confirmButton.setPosition({ 806, 650 });
}

void LoginWindow::setAlertText()
{
	alertText.setCharacterSize(20);
	alertText.setFillColor(Color(0x272727FF));
	alertText.setPosition({ 806, 325 });
}

void LoginWindow::loginFailedHandle()
{
	alertText.setString("wprowadzony PIN jest niepoprawny");
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
		pinInput.onTyped(event.text.unicode);
		if (pinInput.getFocused()) 
			alertText.setString("");
		break;
	}
}

void LoginWindow::draw()
{
	setFields();
	Event event;
	Sprite background;
	background.setTexture(bgTexture);

	while (window.isOpen() && !accService.isAuthorised()) {
		while (window.pollEvent(event)) {
			handleEvent(event);
		}
		window.clear();
		window.draw(background);
		window.draw(pinInput);
		if (!alertText.getString().isEmpty()) 
			window.draw(alertText);
		window.draw(confirmButton);
		window.display();
	}
}
