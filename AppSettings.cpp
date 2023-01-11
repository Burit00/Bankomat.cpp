#include "AppSettings.h"
#include <SFML/Graphics.hpp>

AppGlobalSettings::AppGlobalSettings()
{
	font.loadFromFile("assets/Roboto.ttf");
	Text text("", font, 24);
	text.setFillColor(accentClr);
	this->text = text;
}

Text AppGlobalSettings::getText()
{
	return text;
}

Text AppGlobalSettings::getText(std::string content)
{
	Text newText = text;
	newText.setString(content);
	return newText;
}

Font& AppGlobalSettings::getFont()
{
	return font;
}
