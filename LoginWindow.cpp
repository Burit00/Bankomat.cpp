#include "LoginWindow.h"
#include "GlobalVariables.h"
#include "InputBox.h"
#include "Button.h"

LoginWindow::LoginWindow(RenderWindow& window):
	WindowAbstract(window),
	loginTextBg({350, 280}),
	confirmButton("Zatwierdz"),
	alertText(appSett.getText())
{}

void LoginWindow::setFields() {
	setLoginField();
	setPinInput();
	setConfirmButton();
	setAlertText();
}

void LoginWindow::setLoginField()
{
	loginTextBg.setPosition({ 806, 40 });
	loginTextBg.setFillColor(Color(appSett.primaryClr.toInteger() - 0x000000CC));

	loginTexts[0] = appSett.getText("Witaj w bankomacie");
	loginTexts[1] = appSett.getText("firmy Fortune's Vault");
	loginTexts[2] = appSett.getText("podaj Pin aby potwierdzic");
	loginTexts[3] = appSett.getText("swoja tozsamosc");
	loginTexts[4] = appSett.getText("PIN:");

	loginTexts[0].setCharacterSize(32);
	loginTexts[1].setCharacterSize(32);
	loginTexts[2].setCharacterSize(20);
	loginTexts[3].setCharacterSize(20);
	loginTexts[4].setCharacterSize(28);

	const float rowHeight = 30;
	const float padding = 35;

	for (int i = 0; i < 4; i++) {
		const float sideOfText = loginTexts[i].getGlobalBounds().width / 2;
		const float sideOfXBg = loginTextBg.getPosition().x + loginTextBg.getGlobalBounds().width / 2;
		loginTexts[i].setFillColor(Color::White);
		loginTexts[i].setOrigin({ sideOfText , 0 });
		loginTexts[i].setPosition({ sideOfXBg, loginTextBg.getPosition().y + padding + rowHeight * i + (i == 2 ? 15 : (i == 3 ? 10 : 0))});
	}

	loginTexts[4].setFillColor(Color::White);
	loginTexts[4].setOrigin({ 0 , loginTexts[4].getGlobalBounds().height});
	loginTexts[4].setPosition({ loginTextBg.getPosition().x + padding, loginTextBg.getPosition().y + loginTextBg.getSize().y - padding * 2 + 10});
}

void LoginWindow::setPinInput()
{
	const float padding = 35;
	pinInput.setText("");
	pinInput.isPassword();
	pinInput.setLimit(8);
	pinInput.setType(NUMBER);
	pinInput.setFocused(true);
	RectangleShape inputBg = pinInput.background;
	inputBg.setSize({ 180, 55 });
	inputBg.setOrigin({ inputBg.getSize().x, inputBg.getSize().y});
	inputBg.setPosition({ loginTextBg.getPosition().x + loginTextBg.getSize().x - 35, loginTextBg.getPosition().y + loginTextBg.getSize().y - padding });
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
	Event event;
	Sprite background;
	background.setTexture(bgTexture);

	while (window.isOpen() && !accService.isAuthorised()) {
		while (window.pollEvent(event)) {
			handleEvent(event);
		}
		window.clear();
		window.draw(background);
		window.draw(loginTextBg);
		for (Text& text : loginTexts)
			window.draw(text);
		window.draw(pinInput);
		if (!alertText.getString().isEmpty()) 
			window.draw(alertText);
		window.draw(confirmButton);
		window.display();
	}
}
