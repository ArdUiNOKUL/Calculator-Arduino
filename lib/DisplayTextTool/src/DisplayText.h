#ifndef DisplayText_h
#define DisplayText_h
#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
class DisplayText
{
private:
    char text[16][2];
    int textIndex = 0;
    LiquidCrystal_I2C *lcd;
    bool optionSelectMode;
public:
    DisplayText(LiquidCrystal_I2C *lcd);
    ~DisplayText();
    void addChar(char c);
    void addChar(char c, int index, int line);
    void removeChar();
    void removeChar(int index, int line);
    void clear();
    void clear(int line);
    void print();
    void print(const char *text);
    void print(const char *text, bool clear);
    void Error(const char *text);

    void selectOption(char options[]);
};

#endif // DisplayText_h