#pragma once

#include <string>

class formater
{
public:
	static std::string formatText(std::string text, int maxLength, std::string toManyText);

	static int niceNumber(int num);
};

