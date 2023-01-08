#include "AppSettings.h"
#include <SFML/Graphics.hpp>

AppGlobalSettings::AppGlobalSettings()
{
	font.loadFromFile("Roboto.ttf");
	Text text("", font, 24);
	text.setFillColor(accent);
	this->text = text;
}

Text AppGlobalSettings::getText()
{
	return text;
}

Font& AppGlobalSettings::getFont()
{
	return font;
}

Color AppGlobalSettings::getPrimaryColor()
{
	return primary;
}

Color AppGlobalSettings::getAccentColor()
{
	return accent;
}
