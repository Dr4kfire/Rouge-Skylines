#ifndef FORMATER_H
#define FORMATER_H

#include <string>

class formater
{
public:
	static std::string formatText(std::string text, int maxLength, std::string toManyText);

	static int niceNumber(int num);
};

#endif // FORMATER_H