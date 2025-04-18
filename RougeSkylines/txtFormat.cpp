#include "txtFormat.h"

#include "raylib.h"
#include <vector>
#include <string>
#include <map>

using namespace std;

void txtFormat::drawFormatedString(string text, Vector2 position, Font font) {
    vector<pair<pair<string, Color>, int>> slicedText;

    map<int, Color> colorFormats = {
        {0, GRAY},
        {1, WHITE},
        {2, BLACK},
        {3, GREEN},
        {4, BLUE},
        {5, VIOLET},
        {6, GOLD},
        {7, MAROON}
    };

    int currentLine = 0;
    int currentSlice = -1;
    int currentColor = 0;
    for (int i = 0; i < text.size(); i++) {
        if (currentSlice == -1) {
            currentSlice += 1;
            slicedText.emplace_back(make_pair("", colorFormats[currentColor]), currentLine);
        }

        if (text[i] == '\n') {
            currentLine += 1;
            currentSlice += 1;
            slicedText.emplace_back(make_pair("", colorFormats[currentColor]), currentLine);
            continue;
        }

        if (text[i] == '&' && text.size() > i + 1) {
            char nextChar = text[i + 1];
            if (nextChar >= '0' && nextChar <= '7') {
                currentColor = (nextChar - '0');
                currentSlice += 1;
                slicedText.emplace_back(make_pair("", colorFormats[currentColor]), currentLine);
                i += 1;
                continue;
            }
        }

        slicedText[currentSlice].first.first += text[i];
    }

    int fontSize = 25;
    int offsetX = 0;
    int offsetLine = 0;
    for (int slice = 0; slice < slicedText.size(); slice++) {
        string display = slicedText[slice].first.first;
        int line = slicedText[slice].second;
        Color textColor = slicedText[slice].first.second;

        int offsetY = line * 20;
        if (offsetLine != line) {
            offsetX = 0;
            offsetLine = line;
        }
        
        /*DrawText(display.c_str(), position.x + offsetX, position.y + offsetY, fontSize, textColor);*/
        DrawTextEx(font, display.c_str(), Vector2{ position.x + offsetX, position.y + offsetY }, fontSize, 0, textColor);
        offsetX += MeasureTextEx(font, display.c_str(), fontSize, 0).x;
    }
}