#include <SFML/Graphics.hpp>
#include "GlobalVariables.h"
#include <iostream>
#include "Button.h"


Button::Button(string text, Vector2f size):
	_text(appConf.getText()), background(size)
{
	_text.setString(text);
	background.setFillColor(appConf.primaryClr);
	defaultColor = appConf.primaryClr;
}

void Button::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(background, states);
	target.draw(_text, states);
}

void Button::setPosition(Vector2f pos)
{
	background.setPosition(pos);
	background.setFillColor(defaultColor);
	setTextPositionForBackground();
}

bool Button::isMouseOver(RenderWindow& window)
{
	const int mouseX = Mouse::getPosition(window).x;
	const int mouseY = Mouse::getPosition(window).y;
	const int inputStartX = (int)background.getPosition().x;
	const int inputEndX = (int)background.getPosition().x + background.getSize().x;
	const int inputStartY = (int)background.getPosition().y;
	const int inputEndY = (int)background.getPosition().y + background.getSize().y;

	if (isInRange(mouseX, inputStartX, inputEndX) && isInRange(mouseY, inputStartY, inputEndY)) {
		changeToHoverColor();
		return true;
	} else {
		background.setFillColor(defaultColor);
		return false;
	}
}

void Button::setFillColor(Color bgColor)
{
	defaultColor = bgColor;
}

void Button::changeToHoverColor()
{
	Uint32 hoverColor = defaultColor.toInteger() - 0x00000022;
	background.setFillColor(Color(hoverColor));
}

bool Button::isInRange(int pos, int x1, int x2) const
{
	return pos > x1 && pos < x2;
}

void Button::setTextPositionForBackground()
{
	float textOriginX = (float)_text.getLocalBounds().width / 2;
	float textOriginY = (float)_text.getCharacterSize() / 2;
	float textPosX = (float)background.getPosition().x + background.getSize().x / 2;
	float textPosY = (float)background.getPosition().y + background.getSize().y / 2;

	_text.setOrigin({ textOriginX + 2.5f, textOriginY + 2.5f });
	_text.setPosition({ textPosX,  textPosY });
}