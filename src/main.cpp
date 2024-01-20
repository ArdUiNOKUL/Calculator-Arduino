#include <Arduino.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // I2C address 0x3F for a 16 chars and 2 line display
#include <DisplayText.h>
#include <Calculator.h>
const int ROW_NUM = 4;
const int COLUMN_NUM = 3;
char keys[ROW_NUM][COLUMN_NUM] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};
byte pin_rows[ROW_NUM] = {12, 11, 10, 9};
byte pin_column[COLUMN_NUM] = {7, 6, 5};
Keypad keypad = Keypad(makeKeymap(keys), (byte *)pin_rows, (byte *)pin_column, ROW_NUM, COLUMN_NUM);
LiquidCrystal_I2C lcd(0x3F, 16, 2);
DisplayText display(&lcd, &keypad);

void setup()
{
    lcd.init();
    lcd.backlight();
    lcd.blink();
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);

    display.print("Enter numbers:");
    delay(500);
    display.clear();
}
void loop()
{
    const char key = keypad.getKey();
    digitalWrite(LED_BUILTIN, HIGH);
    if (key)
    {
        switch (key)
        {
        case '*':
        {
            const char res = display.selectOption("+-*/");
            if(res != '\0') display.addChar(res);
            break;
        }
        case '#':{
            switch (display.selectOption("dD="))
            {
                case 'd':
                    display.removeChar();
                    break;
                case 'D':
                    display.clear();
                    break;
                case '=':
                {
                    Calculator::FractionMultiplierIndexResult firstOrderIndexes = Calculator::findMultiplierAndDivisor(display.formatTextData(display.getTextData()));
                    // for(int i = 0; i < firstOrderIndexes.counterM; i++){
                    //     Serial.println("Multiplier: " + String(firstOrderIndexes.multiplier[i].leftIndex) + " " + String(firstOrderIndexes.multiplier[i].index) + " " + String(firstOrderIndexes.multiplier[i].rightIndex));
                    // }
                    char* firstOrderResult = Calculator::multiplingAndDividing(display.formatTextData(display.getTextData()), firstOrderIndexes);
                    free(firstOrderResult);
                    display.clear();
                    break;
                }
                default:
                    break;
            }
            break;
        }

        default:
            display.addChar(key);
            break;
        }
    }
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
}