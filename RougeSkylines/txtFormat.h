#pragma once

#include "raylib.h"
#include <string>

class txtFormat
{
public:
	static void drawFormatedString(std::string text, Vector2 position, Font font);
	void loadFont();
};
