#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

class WindowAbstract abstract
{
protected:
	RenderWindow &window;
	Texture bgTexture;
	void setBackground(string filePath);
	virtual void handleEvent(Event event) = 0;
	virtual void setFields() = 0;
	virtual void draw() = 0;
public:
	WindowAbstract(RenderWindow& window);
	void open();
	bool isOpen();
};

