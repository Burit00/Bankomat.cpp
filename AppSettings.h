#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

class AppGlobalSettings
{
private:
	Text text;
	Font font;
	const Color primary = Color(0x790037FF);
	const Color accent = Color(0xFEC600FF);
	const int fontSize = 24;
public:
	AppGlobalSettings();
	Text getText();
	Font& getFont();
	Color getPrimaryColor();
	Color getAccentColor();
};

