#include <SFML/Graphics.hpp>
#include <iostream>
#include "GlobalVariables.h"
#include "InputBox.h"
using namespace sf;


int main() {

	RenderWindow window(VideoMode(1200, 800), "Bankomat", Style::Close);
	Event event;

	Texture texture;
	texture.loadFromFile("signUpBg.png");

	Sprite sprite;
	sprite.setTexture(texture);

	InputBox pinInput(20, appConf.getAccentColor());
	pinInput.setLimit(8);
	pinInput.setType(inputType(NUMBER));
	RectangleShape& bg = pinInput.background;
	bg.setPosition({ 886, 194 });
	bg.setSize({ 270, 55 });
	bg.setFillColor(appConf.getPrimaryColor());
	pinInput.setBackgound(bg);

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			switch (event.type) {
				case Event::Closed:
					window.close();
					break;
				case Event::MouseMoved:
					
					break;
				case Event::MouseButtonPressed:
					pinInput.setFocused(pinInput.isMouseOver(window));
					break;
				case Event::TextEntered:
					pinInput.onTyped(event);
					break;
			}
		}
		window.clear();
		window.draw(sprite);
		window.draw(pinInput);
		window.display();
	}

	return 0;
}