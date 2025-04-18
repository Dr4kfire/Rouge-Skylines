#include "formater.h"

#include <string>

using namespace std;

string formater::formatText(string text, int maxLength, string toManyText = "...")
{
	string result;

	for (int i = 0; i < (int)text.length(); i++)
	{
		if (i == maxLength - (int)toManyText.length())
		{
			result += toManyText;
		}
		else if (i > maxLength - (int)toManyText.length())
		{
			result += "";
		}
		result += text[i];
	}

	return result;
}

int formater::niceNumber(int num)
{
	return (int)round((double)num / 10) * 10;
}
