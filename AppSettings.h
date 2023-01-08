#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

class AppGlobalSettings
{
private:
	Font _font;
	const Color primary = Color(0x790037FF);
	const Color accent = Color(0xFEC600FF);
	const int fontSize = 24;
public:
	AppGlobalSettings();
	Font& getFont();
	Color getPrimaryColor();
	Color getAccentColor();
};

