#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

class WindowAbstract abstract
{
public:
	Texture bgTexture;
	void setBackground(string filePath);
	RenderWindow &window;
	WindowAbstract(RenderWindow& window);
	virtual void draw() = 0;
	virtual void handleEvent(Event event) = 0;
	virtual void setFields() = 0;
	bool isOpen();
};

