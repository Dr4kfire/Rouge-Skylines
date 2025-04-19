#ifndef TEXT_INPUT_H
#define TEXT_INPUT_H

#include "raylib.h"
#include <string>
#include <vector>

class TxtInput
{
	int maxInputSize;

	float _height = 20;
	Rectangle inputBox;

	bool carotVisible = false;

	std::string finalInput;
	std::string textInput;
public:
	int framesCounter = 0;
	bool isInputReady = false;

	TxtInput(int maxSize, Vector2 screenSize);

	static std::vector<std::string> split(const std::string& s, const std::string& delimiter);

	void handleInput();
	std::string getTextInput();

	void drawInputBox();
};

#endif