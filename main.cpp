#include <SFML/Graphics.hpp>
#include "GlobalVariables.h"
#include "LoginWindow.h"
#include "OperationWindow.h"
#include "DepositWindow.h"
#include "WithdrawWindow.h"
using namespace sf;

int main() {
	RenderWindow window(VideoMode(1200, 800), "Bankomat", Style::Close);
	LoginWindow loginWindow(window);
	OperationWindow operationWindow(window);
	DepositWindow depositWindow(window);
	WithdrawWindowal withdrawWindow(window);

	while (window.isOpen()) {
		if (!accService.isAuthorised())
			loginWindow.draw();
		else {
			switch (appController) {
			case OPERATION_WINDOW:
				operationWindow.draw();
				break;
			case DEPOSITE_WINDOW:
				depositWindow.draw();
				break;
			case WITHDRAWAL_WINDOW:
				withdrawWindow.draw();
				break;
			}
		}
	}

	return 0;
}