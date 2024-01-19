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
DisplayText display(&lcd, &keypad);

// void findOperators(const char* input){
//     for (size_t i = 0; i < strlen(input); i++)
//     {
//         switch (input[i])
//         {
//         case '+':
//             break;
//         case '-':
//             break;
//         case '*':
//             break;
//         case '/':
//             break;
//         default:
//             break;
//         }
//     }

// }

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
            display.addChar(display.selectOption("+-*/"));
            
            break;

        case '#':
            switch (display.selectOption("dD="))
            {
            case 'd':
                display.removeChar();
                break;
            case 'D':
                display.clear();
                break;
            case '=':
                display.clear();
                int result;

            default:
                break;
            }
            break;
        
        default:
            display.addChar(key);
            break;
        }
    }
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
}