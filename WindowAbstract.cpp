#include "WindowAbstract.h"

WindowAbstract::WindowAbstract(RenderWindow& targetWindow):
	window(targetWindow)
{
	setBackground("assets/backgroundImg.png");
}

void WindowAbstract::open()
{
	setFields();
	draw();
}

void WindowAbstract::setBackground(string filePath)
{
	bgTexture.loadFromFile(filePath);
}

bool WindowAbstract::isOpen()
{
	return window.isOpen();
}
