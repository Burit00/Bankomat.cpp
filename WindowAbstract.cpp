#include "WindowAbstract.h"

WindowAbstract::WindowAbstract(RenderWindow& targetWindow):
	window(targetWindow)
{
	setBackground("assets/operationBg.png");
}

void WindowAbstract::setBackground(string filePath)
{
	bgTexture.loadFromFile(filePath);
}

bool WindowAbstract::isOpen()
{
	return window.isOpen();
}
