#include "AppSettings.h"
#include <SFML/Graphics.hpp>

AppGlobalSettings::AppGlobalSettings()
{
	_font.loadFromFile("Roboto.ttf");
}

Font& AppGlobalSettings::getFont()
{
	return _font;
}

Color AppGlobalSettings::getPrimaryColor()
{
	return primary;
}

Color AppGlobalSettings::getAccentColor()
{
	return accent;
}
