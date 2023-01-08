#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

class Button : public Drawable
{
private:
	Text _text;
	void setTextPositionForBackground();
public:
	RectangleShape background;
	Button(string text = "");
	void draw(RenderTarget& terget, RenderStates states) const override;
	void setPositon(Vector2f pos);
	bool isInRange(int pos, int x1, int x2) const;
	bool isMouseOver(RenderWindow& window);
};

