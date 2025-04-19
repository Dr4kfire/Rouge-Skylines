#ifndef TXT_FORMAT_H
#define TXT_FORMAT_H

#include "raylib.h"
#include <string>

class TxtFormat
{
public:
	static void drawFormatedString(std::string text, Vector2 position, Font font);
	void loadFont();
};

#endif // TXT_FORMAT_H