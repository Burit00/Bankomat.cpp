#include "InputBox.h"

InputBox::InputBox(int size, Color color, bool focus) :
	_type(TEXT),
	_maxLength(50),
	_isFocused(focus),
	_hasBackgound(false),
	_isPassword(false),
	background({ 350, 70 })
{
	_textBox.setCharacterSize(size);
	_textBox.setFillColor(color);
	_textBox.setFont(appSett.getFont());
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

void InputBox::isPassword()
{
	_isPassword = true;
}

void InputBox::setFocused(bool isFocused)
{
	_isFocused = isFocused;
	setTextOnScreen();
}

bool InputBox::getFocused()
{
	return _isFocused;
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

void InputBox::onTyped(char sign)
{
	if (!_isFocused) return;
	if (sign < 128) {
		if(!_maxLength || _text.str().length() < _maxLength || sign == DELETE_KEY) inputLogic(sign);
	}
}

void InputBox::setType(inputTypeEnum type)
{
	_type = type;
}

void InputBox::setText(string text)
{
	_text.str("");
	_text.str(text);
	setTextOnScreen();
	
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
	setTextOnScreen();
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

void InputBox::setTextOnScreen()
{
	_textBox.setString((_isPassword ? hashText(_text.str()) : _text.str()) + (_isFocused ? "_" : ""));
}

string InputBox::hashText(string text)
{
	string password("");
	for (int i = 0; i < text.length(); i++) password += char(42);
	return password;
}

bool InputBox::isEmpty() {
	return _text.str().empty();
}
