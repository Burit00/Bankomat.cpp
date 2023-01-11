#include "WithdrawWindow.h"
#include "GlobalVariables.h"

WithdrawWindowal::WithdrawWindowal(RenderWindow& window) :
	WindowAbstract(window),
	isTransactionComplete(false),
	accountBalanceTextBg({ 350, 70 }),
	alertText(appSett.getText()),
	confirmButton("Wyplac"),
	transactionDetailsTitle(appSett.getText("Szczegoly transakcji:")),
	transactionDetailsBg({ 350, 70}),
	transactionDetailsLine({350, 10}),
	backButton("Powrot")
{
}

void WithdrawWindowal::setAccountBalanceText() {
	accountBalanceText[0] = appSett.getText();
	accountBalanceText[1] = appSett.getText();
	accountBalanceText[0].setFillColor(Color::White);
	accountBalanceText[1].setFillColor(Color::White);
	accountBalanceText[0].setString("Twoj stan konta:");
	accountBalanceText[1].setString(to_string(accService.getActiveAccount().getAccountBalance()) + " PLN");
	accountBalanceTextBg.setPosition({ 806, 40 });
	accountBalanceTextBg.setFillColor(Color(appSett.primaryClr.toInteger() - 0x000000CC));

	const float text0OriginX = accountBalanceText[0].getGlobalBounds().width / 2;
	const float text0OriginY = accountBalanceText[0].getGlobalBounds().height / 2;
	const float text1OriginX = accountBalanceText[1].getGlobalBounds().width / 2;
	const float text1OriginY = accountBalanceText[1].getGlobalBounds().height / 2;

	accountBalanceText[0].setOrigin({ text0OriginX, text0OriginY });
	accountBalanceText[1].setOrigin({ text1OriginX, text1OriginY });

	const float textPosX = accountBalanceTextBg.getPosition().x + accountBalanceTextBg.getSize().x / 2;
	const float text0PosY = accountBalanceTextBg.getPosition().y + accountBalanceTextBg.getSize().y / 3 - 5;
	const float text1PosY = accountBalanceTextBg.getPosition().y + accountBalanceTextBg.getSize().y * 2 / 3 - 5;

	accountBalanceText[0].setPosition({ textPosX, text0PosY });
	accountBalanceText[1].setPosition({ textPosX, text1PosY });
}

void WithdrawWindowal::setCashInput() {
	cashInput.setText("");
	cashInput.setFocused(true);
	cashInput.setLimit(to_string(cashmachine.getWithdrawalLimit()).length());
	cashInput.setType(NUMBER);
	RectangleShape inputBg = cashInput.background;
	inputBg.setPosition({ 806, 140 });
	inputBg.setSize({ 350,70 });
	inputBg.setFillColor(appSett.primaryClr);
	cashInput.setBackgound(inputBg);
}

void WithdrawWindowal::setAlertText(string content) {
	alertText.setString(content);
	alertText.setFillColor(Color(0x373737FF));
	alertText.setCharacterSize(20);
	alertText.setPosition({ 806, 220 });
}

void WithdrawWindowal::setConfirmButton() {
	confirmButton.setPosition({806, 550});
}

void WithdrawWindowal::prepareTransactionDetailsView() {
	transactionDetailsTexts.clear();
	transactionDetailsLine.setPosition({ 806, 195 });
	transactionDetailsBg.setPosition({ 806, 120 });
	transactionDetailsLine.setFillColor(appSett.primaryClr);
	transactionDetailsBg.setFillColor(Color(appSett.primaryClr.toInteger() - 0x000000CC));

	const float padding = 35;
	const float posXSideOfBg = transactionDetailsBg.getPosition().x + transactionDetailsBg.getSize().x / 2;

	transactionDetailsTitle.setFillColor(Color::White);
	transactionDetailsTitle.setOrigin({ (float)transactionDetailsTitle.getGlobalBounds().width / 2, 0 });
	transactionDetailsTitle.setPosition({ (float)posXSideOfBg, transactionDetailsBg.getPosition().y + padding - 15 });
}

void WithdrawWindowal::updateTransactionDetailsView() {
	const float rowHeight = 40;
	const float paddingTopBottom = 35;
	const float paddingLeftRight = 25;


	for (int row = 0; row < PiggyBank::numberOfNominalTypes; row++) {
		if (withdrawal.getNumberOfNominals()[row] == 0) continue;
		const int nominalInt = PiggyBank::nominalsTypes[row];
		const int numberOfNominalsInt = withdrawal.getNumberOfNominals()[row];
		const string nominal = to_string(PiggyBank::nominalsTypes[row]);
		const string numberOfNominals = to_string(withdrawal.getNumberOfNominals()[row]);

		const string text1 = nominal;
		const string text2 = "PLN   x         =";
		const string text3 = numberOfNominals;
		const string text4 = to_string(nominalInt * numberOfNominalsInt) + " PLN";
		vector<Text> texts;

		texts.push_back(appSett.getText(text1));
		texts.push_back(appSett.getText(text2));
		texts.push_back(appSett.getText(text3));
		texts.push_back(appSett.getText(text4));

		const float posX = 806 + paddingLeftRight;
		const float posY = 190 + paddingTopBottom + rowHeight * transactionDetailsTexts.size() - 5;
		const float offsetXText2 = 43;
		const float offsetXText3 = 150;
		const float posXText4 = transactionDetailsBg.getPosition().x + transactionDetailsBg.getSize().x - paddingLeftRight;

		texts[0].setPosition({ posX, posY});
		texts[1].setPosition({ posX + offsetXText2, posY});
		texts[2].setOrigin({ texts[2].getGlobalBounds().width , 0 });
		texts[2].setPosition({ posX + offsetXText3 , posY});
		texts[3].setOrigin({ texts[3].getGlobalBounds().width , 0});
		texts[3].setPosition({ posXText4 , posY});

		for (Text& text : texts) {
			text.setFillColor(Color::White);
		}

		transactionDetailsTexts.push_back(texts);
	}
	transactionDetailsBg.setSize({ 350, 3 * paddingTopBottom + rowHeight * transactionDetailsTexts.size() });
}

void WithdrawWindowal::setBackButton() {
	backButton.setPosition({ 806 , 650 });
}

void WithdrawWindowal::setFields() {
	setAccountBalanceText();
	setCashInput();
	setAlertText("");
	setConfirmButton();
	prepareTransactionDetailsView();
	setBackButton();
}

void WithdrawWindowal::handleEvent(Event event) {
	switch (event.type) {
	case Event::Closed:
		window.close();
		break;
	case Event::MouseMoved:
		onMouseMoved(event);
		break;
	case Event::MouseButtonPressed:
		onClick(event);
		break;
	case Event::TextEntered:
		onType(event);
		break;
	}
}

void WithdrawWindowal::onMouseMoved(Event event) {
	confirmButton.isMouseOver(window);
	backButton.isMouseOver(window);
}

void WithdrawWindowal::onClick(Event event) {
	cashInput.setFocused(cashInput.isMouseOver(window));

	if (confirmButton.isMouseOver(window)) {
		if (cashInput.isEmpty() || stoi(cashInput.getText()) == 0) {
			setAlertText("Wprowadz kwote");
		} else {
			int money = stoi(cashInput.getText());
			if (accService.getActiveAccount().getAccountBalance() < money) {
				setAlertText("Nie posiadasz tylu srodkow na koncie");
			} else if (money > cashmachine.getWithdrawalLimit()) {
				setAlertText("Nie mozesz wyplacic kwoty powyzej\n" + to_string(cashmachine.getWithdrawalLimit()) + " PLN");
			} else if (!cashmachine.isWithdrawalAvailable(money)) {
				setAlertText("W bankomacie brakuje nominalow");
			} else {
				withdrawal = cashmachine.wihdrawal(money);
				isTransactionComplete = true;
				setAccountBalanceText();
				updateTransactionDetailsView();
			}
		}
	} else {
		setAlertText("");
	}

	if (backButton.isMouseOver(window))
		appController = OPERATION_WINDOW;
}

void WithdrawWindowal::onType(Event event)
{
	cashInput.onTyped(event.text.unicode);
}

void WithdrawWindowal::draw()
{
	Event event;
	Sprite bg;
	bg.setTexture(bgTexture);
	isTransactionComplete = false;
	withdrawal.resetPiggyBank();
	setFields();

	while (window.isOpen() && 
		appController == WITHDRAWAL_WINDOW) {
		while (window.pollEvent(event)) handleEvent(event);

		window.clear();
		window.draw(bg);
		window.draw(accountBalanceTextBg);
		window.draw(accountBalanceText[0]);
		window.draw(accountBalanceText[1]);
		
		if (!isTransactionComplete) {
			window.draw(cashInput);
			window.draw(alertText);
			window.draw(confirmButton);
		} else {
			window.draw(transactionDetailsBg);
			window.draw(transactionDetailsLine);
			window.draw(transactionDetailsTitle);
			for(vector<Text> textPair: transactionDetailsTexts)
				for(Text text: textPair) window.draw(text);
		}
		window.draw(backButton);
		window.display();
	}
}
