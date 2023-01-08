#include <SFML/Graphics.hpp>
#include <iostream>
#include "GlobalVariables.h"
#include "InputBox.h"

InputBox::InputBox(int size, Color color, bool focus):
	_type(TEXT), _maxLength(0), _isFocused(focus), _hasBackgound(false)
{
	_textBox.setCharacterSize(size);
	_textBox.setFillColor(color);
	_textBox.setFont(appConf.getFont());
	_textBox.setString(focus ? "_" : "");
}

void InputBox::draw(RenderTarget & target, RenderStates state) const
{
	if (_hasBackgound) { 
		target.draw(this->background, state);
	}
	target.draw(this->_textBox, state);
}

void InputBox::setBackgound(RectangleShape bg)
{
	_hasBackgound = true;
	background = bg;
	setTextPositionForBackground();
}

void InputBox::setFont(Font& font)
{
	_textBox.setFont(font);
}

void InputBox::setPositon(Vector2f pos)
{
	_textBox.setPosition(pos);
}

void InputBox::setLimit(int limit)
{
	_maxLength = limit;
}

void InputBox::setFocused(bool isFocused)
{
	_isFocused = isFocused;
	_textBox.setString(_text.str() + (_isFocused ? "_" : ""));
}

bool InputBox::isMouseOver(RenderWindow& window)
{
	const int mouseX = Mouse::getPosition(window).x;
	const int mouseY = Mouse::getPosition(window).y;
	const int inputStartX = (int) background.getPosition().x;
	const int inputEndX = (int) background.getPosition().x + background.getSize().x;
	const int inputStartY = (int) background.getPosition().y;
	const int inputEndY = (int) background.getPosition().y + background.getSize().y;

	if (_hasBackgound) {
		if (isInRange(mouseX, inputStartX, inputEndX) && isInRange(mouseY, inputStartY, inputEndY)) {
			return true;
		} else {
			return false;
		}
	}
	else {
		return false;
	}
}

void InputBox::onTyped(Event keyboardEvent)
{
	if (!_isFocused) return;
	int text = keyboardEvent.text.unicode;
	if (text < 128) {
		if(!_maxLength || _text.str().length() <= _maxLength || text == DELETE_KEY) inputLogic(text);
	}
}

void InputBox::setType(inputType type)
{
	_type = type;
}

void InputBox::setText(string text)
{
	_text.str("");
	_text.str(text);
}

string InputBox::getText()
{
	return _text.str();
}

void InputBox::inputLogic(int charTyped)
{
	switch (charTyped) {
	case DELETE_KEY:
		if (_text.str().length() > 0) deleteLastChar();
	break;
	
	case ENTER_KEY:
	break;
	
	case ESCAPE_KEY:
	break;
	
	default:
		switch (_type)
		{
		case TEXT:
			_text << static_cast<char>(charTyped);
			break;
		case NUMBER:
			if (charTyped > 47 && charTyped < 58)
				_text << static_cast<char>(charTyped);
			break;
		}
	}

	_textBox.setString(_text.str() + "_");
}

void InputBox::deleteLastChar()
{
	string text = _text.str();
	string temp = "";
	for (int i = 0; i < text.length() - 1; i++) {
		temp += text[i];
	}
	_text.str("");
	_text << temp;
}

bool InputBox::isInRange(int pos, int x1, int x2) const
{
	return pos > x1 && pos < x2;
}

void InputBox::setTextPositionForBackground()
{
	float textOriginY = (float) _textBox.getCharacterSize() / 2;
	float textPosX = (float) background.getPosition().x + (background.getSize().y - _textBox.getCharacterSize())/2;
	float textPosY = (float) background.getPosition().y + background.getSize().y / 2;

	_textBox.setOrigin({ 0, textOriginY });
	_textBox.setPosition({ textPosX,  textPosY });
}
