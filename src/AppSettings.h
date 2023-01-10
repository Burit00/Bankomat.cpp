#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class AppGlobalSettings
{
private:
	Text text;
	Font font;
public:
	const Color primaryClr = Color(0x790037FF);
	const Color accentClr = Color(0xFEC600FF);
	const int fontSize = 24;
	AppGlobalSettings();
	Text getText();
	Text getText(std::string content);
	Font& getFont();
};

