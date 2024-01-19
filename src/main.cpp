#include <Arduino.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // I2C address 0x3F for a 16 chars and 2 line display
#include <DisplayText.h>
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
DisplayText display(&lcd);

uint8_t number1 = 0;
uint8_t number2 = 0;
bool secondNumber = false;
char lastOperation;

void setup()
{
    lcd.init();
    lcd.backlight();
    lcd.blink();
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);

    display.print("Enter numbers:");
    delay(2000);
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
            display.selectOption("+-*/");
            
            break;

        case '#':
            break;
        
        default:
            display.addChar(key);
            if (!secondNumber) number1 = number1 * 10 + (key - '0');
            else number2 = number2 * 10 + (key - '0');
            break;
        }
    }
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
}