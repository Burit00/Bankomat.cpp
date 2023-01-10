#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

class Button : public Drawable
{
private:
	Text _text;
	Color defaultColor;
	void setTextPositionForBackground();
public:
	RectangleShape background;
	Button(string text = "", Vector2f size = { 350, 70 });
	void draw(RenderTarget& terget, RenderStates states) const override;
	void setFillColor(Color bgColor);
	void setPosition(Vector2f pos);
	bool isInRange(int pos, int x1, int x2) const;
	bool isMouseOver(RenderWindow& window);
	void changeToHoverColor();
};

