#include "WindowAbstract.h"

WindowAbstract::WindowAbstract(RenderWindow& targetWindow):
	window(targetWindow)
{
	setBackground("src/assets/operationBg.png");
}

void WindowAbstract::setBackground(string filePath)
{
	bgTexture.loadFromFile(filePath);
}

bool WindowAbstract::isOpen()
{
	return window.isOpen();
}
