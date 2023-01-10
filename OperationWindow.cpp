#include "OperationWindow.h"
#include "GlobalVariables.h"

OperationWindow::OperationWindow(RenderWindow& window) :
	WindowAbstract(window),
	depositButton("Wplatomat"),
	withdrawButton("Wyplatomat"),
	logoutButton("Wyloguj"),
	accountBalanceTextBg({ 350, 70 })
{}

void OperationWindow::setAccountBalanceText()
{
	accountBalanceText[0] = appConf.getText();
	accountBalanceText[1] = appConf.getText();
	accountBalanceText[0].setFillColor(Color::White);
	accountBalanceText[1].setFillColor(Color::White);
	accountBalanceText[0].setString("Twoj stan konta:");
	accountBalanceText[1].setString(to_string(accService.getActiveAccount().getAccountBalance()) + " PLN");
	accountBalanceTextBg.setPosition({ 806, 40 });
	accountBalanceTextBg.setFillColor(Color(appConf.primaryClr.toInteger() - 0x000000CC));

	const float text0OriginX = accountBalanceText[0].getGlobalBounds().width / 2;
	const float text0OriginY = accountBalanceText[0].getGlobalBounds().height /2;
	const float text1OriginX = accountBalanceText[1].getGlobalBounds().width / 2;
	const float text1OriginY = accountBalanceText[1].getGlobalBounds().height /2;

	accountBalanceText[0].setOrigin({ text0OriginX, text0OriginY });
	accountBalanceText[1].setOrigin({ text1OriginX, text1OriginY });

	const float textPosX = accountBalanceTextBg.getPosition().x + accountBalanceTextBg.getSize().x / 2;
	const float text0PosY = accountBalanceTextBg.getPosition().y + accountBalanceTextBg.getSize().y / 3 - 5;
	const float text1PosY = accountBalanceTextBg.getPosition().y + accountBalanceTextBg.getSize().y * 2/3 - 5;

	accountBalanceText[0].setPosition({ textPosX, text0PosY });
	accountBalanceText[1].setPosition({ textPosX, text1PosY });
}

void OperationWindow::setPayInButton()
{
	depositButton.setPosition({ 806, 143 });
}

void OperationWindow::setPayOutButton()
{
	withdrawButton.setPosition({ 806, 243 });
}

void OperationWindow::setLogoutButton()
{
	logoutButton.setPosition({ 806, 650 });
}

void OperationWindow::setFields() {
	setAccountBalanceText();
	setPayInButton();
	setPayOutButton();
	setLogoutButton();
}

void OperationWindow::handleEvent(Event event)
{
	switch (event.type)
	{
	case Event::Closed:
		window.close();
		break;
	case Event::MouseMoved:
		depositButton.isMouseOver(window);
		withdrawButton.isMouseOver(window);
		logoutButton.isMouseOver(window);
		break;
	case Event::MouseButtonPressed:
		if(depositButton.isMouseOver(window))
			appController = DEPOSIT_WINDOW;
		if(withdrawButton.isMouseOver(window))
			//appController = WITHDRAW_WINDOW;
		if (logoutButton.isMouseOver(window)) {
			accService.logout();
		}
			
		break;
	}
}

void OperationWindow::draw()
{
	setFields();
	Event event;
	Sprite bgSprite;
	bgSprite.setTexture(bgTexture);

	while (window.isOpen() && 
		accService.isAuthorised() &&
		appController == OPERATION_WINDOW) {
		while (window.pollEvent(event)) {
			handleEvent(event);
		}
		window.clear();
		window.draw(bgSprite);
		window.draw(accountBalanceTextBg);
		window.draw(accountBalanceText[0]);
		window.draw(accountBalanceText[1]);
		window.draw(depositButton);
		window.draw(withdrawButton);
		window.draw(logoutButton);
		window.display();
	}
}
