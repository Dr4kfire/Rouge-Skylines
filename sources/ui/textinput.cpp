#include "textinput.h"

#include "raylib.h"
#include <string>
#include <vector>

using namespace std;

TxtInput::TxtInput(int maxSize, Vector2 screenSize)
	: maxInputSize(maxSize), inputBox{ 0, screenSize.y - _height, screenSize.x, _height } 
{

}

vector<string> TxtInput::split(const string& s, const string& delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

void TxtInput::handleInput() {
    int key = GetCharPressed();

    while (key > 0) {
        if (key >= 32 && key <= 125 && textInput.length() < this->maxInputSize) {
            finalInput = "";
            textInput += static_cast<char>(key);
        }

        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && !textInput.empty()) {
        textInput.erase(textInput.length() - 1);
    }
    if (IsKeyPressed(KEY_ENTER)) {
        this->finalInput = textInput;
        this->isInputReady = true;
        textInput = "";
    }
}
string TxtInput::getTextInput() {
    if (!finalInput.empty()) {
        string input = this->finalInput;
        isInputReady = false;
        return input;
    }
    else {
        return "";
    }
}
void TxtInput::drawInputBox() {
    DrawRectangleRec(this->inputBox, BLACK);

    string prefix = "> ";
    DrawText(prefix.c_str(), 
        static_cast<int>(this->inputBox.x), 
        static_cast<int>(this->inputBox.y), 
        20, WHITE
    );

    int offset = MeasureText(prefix.c_str(), 20);
    string text = this->textInput;
    DrawText(text.c_str(), 
        static_cast<int>(this->inputBox.x) + offset, 
        static_cast<int>(this->inputBox.y), 
        20, SKYBLUE
    );

    if (framesCounter >= 20) {
        framesCounter = 0;
        carotVisible = !carotVisible;
    } if (carotVisible) {
        string measuredText = prefix + text;
        offset = MeasureText(measuredText.c_str(), 20);
        DrawRectangle(
            static_cast<int>(this->inputBox.x) + offset,
            static_cast<int>(this->inputBox.y) - 2,
            2, 20, BLUE
        );
    }
}