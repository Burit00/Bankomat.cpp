#include "DepositWindow.h"
#include "GlobalVariables.h"

DepositWindow::DepositWindow(RenderWindow& window):
	WindowAbstract(window),
	nominalBtnBg({350,420}),
	description1(appSett.getText("Wybierz nominaly ktore")),
	description2(appSett.getText("wplacisz")),
	alertText(appSett.getText("Wprowadz kwote")),
	resetButton("Wyczysc"),
	depositeButton("Wplac"),
	backButton("Powrot")
{
}

void DepositWindow::setCashInput()
{
	cashInput.setText("0");
	cashInput.setType(NUMBER);
	RectangleShape inputBg = cashInput.background;
	inputBg.setPosition({ 806, 475 });
	inputBg.setSize({ 350,70 });
	inputBg.setFillColor(appSett.primaryClr);
	cashInput.setBackgound(inputBg);
}

void DepositWindow::setResetButton()
{
	resetButton.background.setSize({169, 70});
	resetButton.setPosition({ 806, 560 });
}

void DepositWindow::setDepositeButton()
{
	depositeButton.background.setSize({ 169, 70 });
	depositeButton.setPosition({ 991, 560 });
}

void DepositWindow::setNominalsButtons()
{
	int row = -1;
	const float pos[2] = { 841, 145 };
	nominalButtons.clear();
	for (int i = 0; i < PiggyBank::numberOfNominalTypes; i++) {
		if (i % 3 == 0) row++;
		const int offsetX = 105 * (i % 3);
		const int offsetY = 105 * row;
		Button nominalBtn(to_string(PiggyBank::nominalsTypes[i]));
		nominalBtn.background.setSize({ 70, 70 });
		nominalBtn.setPosition({ pos[0] + offsetX, pos[1] + offsetY });
		nominalButtons.push_back(nominalBtn);
	}
}

void DepositWindow::setNominalBtnBg()
{
	nominalBtnBg.setFillColor(Color(appSett.primaryClr.toInteger() - 0x000000CC));
	nominalBtnBg.setPosition({806, 40});

	const float sideOfBg = nominalBtnBg.getPosition().x + nominalBtnBg.getGlobalBounds().width / 2;

	description1.setPosition({ sideOfBg - description1.getGlobalBounds().width / 2, 55});
	description2.setPosition({ sideOfBg - description2.getGlobalBounds().width / 2, 85 });
	description1.setFillColor(Color::White);
	description2.setFillColor(Color::White);
}

void DepositWindow::setAlertText(string content)
{
	const float sideOfBg = nominalBtnBg.getPosition().x + nominalBtnBg.getGlobalBounds().width / 2;
	alertText.setString(content);
	alertText.setFillColor(Color(0x373737FF));
	alertText.setCharacterSize(16);
	alertText.setOrigin({ (float) alertText.getGlobalBounds().width / 2, 0 });
	alertText.setPosition({ sideOfBg, 435 });
}

void DepositWindow::setBackButton()
{
	backButton.setPosition({ 806, 658 });
}

void DepositWindow::setFields()
{
	setNominalsButtons();
	setNominalBtnBg();
	setAlertText("");
	setCashInput();
	setResetButton();
	setDepositeButton();
	setBackButton();
}

void DepositWindow::onMouseMoved(Event event)
{
	for (Button& button : nominalButtons) {
		button.isMouseOver(window);
	}
	resetButton.isMouseOver(window);
	depositeButton.isMouseOver(window);
	backButton.isMouseOver(window);
}

void DepositWindow::onClick(Event event)
{
	for (int i = 0; i < nominalButtons.size(); i++) {
		if (nominalButtons[i].isMouseOver(window)) {
			setAlertText("");
			deposite.incrementNominal(i);
			cashInput.setText(to_string(deposite.calculateCash()));
		}
	}
	if (resetButton.isMouseOver(window)) {
		deposite.resetPiggyBank();
		cashInput.setText(to_string(deposite.calculateCash()));
	}
	if (depositeButton.isMouseOver(window)) {
		if (deposite.calculateCash()) {
			cashmachine.deposite(deposite);
			appController = OPERATION_WINDOW;
		}
		else {
			setAlertText("Wprowadz kwote");
		}
		
	}
	if (backButton.isMouseOver(window))
		appController = OPERATION_WINDOW;
}

void DepositWindow::handleEvent(Event event)
{
	switch (event.type)
	{
	case Event::Closed:
		window.close();
		break;
	case Event::MouseMoved:
		onMouseMoved(event);
		break;
	case Event::MouseButtonPressed:
		onClick(event);
		break;
	}
}

void DepositWindow::draw()
{
	Event event;
	Sprite background;
	background.setTexture(bgTexture);
	deposite.resetPiggyBank();
	setFields();

	while (window.isOpen() && appController == DEPOSITE_WINDOW) {
		while (window.pollEvent(event)) {
			handleEvent(event);
		}
		window.clear();
		window.draw(background);
		window.draw(nominalBtnBg);
		window.draw(description1);
		window.draw(description2);
		window.draw(alertText);
		for (Button btn : nominalButtons) {
			window.draw(btn);
		}
		window.draw(cashInput);
		window.draw(resetButton);
		window.draw(depositeButton);
		window.draw(backButton);
		window.display();
	}
}
