#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include "GlobalVariables.h"
using namespace std;
using namespace sf;

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

enum inputTypeEnum {
	TEXT = 0,
	NUMBER = 1
};

class InputBox: public Drawable
{
private:
	ostringstream _text;
	Text _textBox;
	inputTypeEnum _type;
	bool _isFocused;
	int _maxLength;
	bool _hasBackgound;
	bool _isPassword;
	void inputLogic(int charTyped);
	void deleteLastChar();
	bool isInRange(int pos, int x1, int x2) const;
	void setTextPositionForBackground();
	void setTextOnScreen();
	string hashText(string text);
public:
	RectangleShape background;
	InputBox(int size = 20, Color color = appSett.accentClr, bool focus = false);
	void draw(RenderTarget&target, RenderStates state) const override;
	void setBackgound(const RectangleShape bg);
	void setFont(Font& font);
	void setPositon(Vector2f pos);
	void setLimit(int limit);
	void isPassword();
	void setFocused(bool isFocused);
	bool getFocused();
	bool isMouseOver(RenderWindow& window);
	void onTyped(char sign);
	void setType(inputTypeEnum type);
	bool isEmpty();
	void setText(string text = "");
	string getText();

};

