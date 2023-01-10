#include <SFML/Graphics.hpp>
#include "GlobalVariables.h"
#include "LoginWindow.h"
#include "OperationWindow.h"
#include "DepositWindow.h"
using namespace sf;

//AppControllerEnum appController = OPERATION_WINDOW;

int main() {
	RenderWindow window(VideoMode(1200, 800), "Bankomat", Style::Close);
	LoginWindow loginWindow(window);
	OperationWindow operationWindow(window);
	DepositWindow depositWindow(window);

	while (window.isOpen()) {
		if(!accService.isAuthorised())
			loginWindow.draw();
		else {
			switch (appController) {
			case OPERATION_WINDOW:
				operationWindow.draw();
				break;
			case DEPOSIT_WINDOW:
				depositWindow.draw();
				break;
			case WITHDRAW_WINDOW:
				break;
			}
		}
	}

	return 0;
}