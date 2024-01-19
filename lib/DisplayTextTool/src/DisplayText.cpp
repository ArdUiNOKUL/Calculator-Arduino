#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <DisplayText.h>

DisplayText::DisplayText(LiquidCrystal_I2C *lcd)
{
    this->lcd = lcd;
}

DisplayText::~DisplayText()
{
    this->lcd->clear();
    this->lcd->backlight();
    this->lcd->off();
}

void DisplayText::addChar(char c)
{
    if (this->textIndex < 16)
    {
        this->text[this->textIndex][0] = c;
        this->text[this->textIndex][1] = '\0';
        this->textIndex++;
    }
    else if (this->textIndex < 32)
    {
        this->text[this->textIndex - 16][1] = c;
        this->text[this->textIndex - 16][2] = '\0';
        this->textIndex++;
    }
    DisplayText::print();
}

void DisplayText::addChar(char c, int index, int line)
{
    if(line == 1){
        this->text[index][0] = c;
    } else if(line == 2){
        this->text[index][1] = c;
    }
    DisplayText::print();
}

void DisplayText::removeChar()
{
    if (this->textIndex > 0)
    {
        this->textIndex--;
        if (this->textIndex < 16)
        {
            this->text[this->textIndex][0] = '\0';
        }
        else if (this->textIndex < 32)
        {
            this->text[this->textIndex - 16][1] = '\0';
        }
    }
    DisplayText::print();
}

void DisplayText::removeChar(int index, int line)
{
    if(line == 1){
        this->text[index][0] = '\0';
    } else if(line == 2){
        this->text[index][1] = '\0';
    }
    DisplayText::print();
}

void DisplayText::clear()
{
    this->textIndex = 0;
    for (int i = 0; i < 16; i++)
    {
        this->text[i][0] = '\0';
        this->text[i][1] = '\0';
    }
    DisplayText::print();
    this->lcd->setCursor(0, 0);
}
void DisplayText::clear(int line)
{
    if(line == 1){
        for (int i = 0; i < 16; i++)
        {
            this->text[i][0] = '\0';
        }
        this->lcd->setCursor(0, line - 1);
    } else if(line == 2){
        for (int i = 0; i < 16; i++)
        {
            this->text[i][1] = '\0';
        }
        this->lcd->setCursor(0, line - 1);
    }
    DisplayText::print();
}

void DisplayText::print()
{
    this->lcd->clear();
    this->lcd->setCursor(0, 0);
    this->lcd->print(this->text[0]);
    this->lcd->setCursor(0, 1);
    this->lcd->print(this->text[1]);
}

void DisplayText::print(const char *text)
{
    // Checking length of text
    if(strlen(text) > 32) DisplayText::Error("Text is too big");
    this->lcd->clear();
    this->lcd->setCursor(0, 0);
    this->lcd->print(text);
}

void DisplayText::print(const char *text, bool clear)
{
    if (clear) this->lcd->clear();

    this->lcd->setCursor(0, 0);
    this->lcd->print(text);
}

void DisplayText::Error(const char *text)
{
    this->lcd->clear();
    this->lcd->setCursor(0, 0);
    this->lcd->print("Error:");
    this->lcd->setCursor(0, 1);
    this->lcd->print(text);
}

/* ------------------ */

// void DisplayText::selectOption(char options){
//     this->optionSelectMode = true;
//     DisplayText::print("Select options:")
// }