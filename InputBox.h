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

class InputBox: public Drawable
{
private:
	ostringstream _text;
	Text _textBox;
	inputType _type;
	bool _isFocused;
	int _maxLength;
	bool _hasBackgound;
	void inputLogic(int charTyped);
	void deleteLastChar();
	bool isInRange(int pos, int x1, int x2) const;
	void setTextPositionForBackground();
public:
	RectangleShape background;
	InputBox(int size, Color color, bool focus = false);
	void draw(RenderTarget&target, RenderStates state) const override;
	void setBackgound(const RectangleShape bg);
	void setFont(Font& font);
	void setPositon(Vector2f pos);
	void setLimit(int limit);
	void setFocused(bool isFocused);
	bool isMouseOver(RenderWindow& window);
	void onTyped(Event keyboardEvent);
	void setType(inputType type);
	void setText(string text = "");
	string getText();

};

