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

struct Fraction
{
    short index;        // index of the operator
    uint8_t leftIndex;  // index to the left till the operator can influence
    uint8_t rightIndex; // index to the right till the operator can influence
};

struct Multiplier
{
    uint8_t index;      // index of the operator
    uint8_t leftIndex;  // index to the left till the operator can influence
    uint8_t rightIndex; // index to the right till the operator can influence
};

struct FractionMultiplier
{
    uint8_t counterM; // counter for multiplier
    uint8_t counterD; // counter for divisor
    uint8_t counterO; // counter for order
    Fraction fractions[16];
    Multiplier multiplier[16];
    uint8_t order[16]; // 0 = fraction, 1 = multiplier
};

FractionMultiplier findMultiplierAndDivisor(char *input)
{
    FractionMultiplier result;
    Serial.println("Size: " + String(strlen(input)));
    Serial.println("Input: " + String(input));
    for (int i = 0; i < 32; i++)
    {
        switch (input[i])
        {
        case '*':
            result.multiplier[result.counterM].index = i;
            for (int j = i - 1; j >= 0; j--)
            {
                if (input[j] == '+' || input[j] == '-')
                {
                    result.multiplier[result.counterM].leftIndex = j;
                }
                else if (input[j] == '\0')
                {
                    result.multiplier[result.counterM].leftIndex = '\0';
                }
                else if (input[j] == '*' || input[j] == '/')
                {
                    break;
                }
            }
            for (int j = i + 1; j < strlen(input); j++)
            {
                if (input[j] == '+' || input[j] == '-')
                {
                    result.multiplier[result.counterM].rightIndex = j;
                }
                else if (input[j] == '\0')
                {
                    result.multiplier[result.counterM].rightIndex = '\0';
                }
                else if (input[j] == '*' || input[j] == '/')
                {
                    break;
                }
            }
            result.counterM++;
            result.order[result.counterO++] = 1;
            Serial.println("Multiplier: " + String(result.multiplier[result.counterM - 1].leftIndex) + " " + String(result.multiplier[result.counterM - 1].index) + " " + String(result.multiplier[result.counterM - 1].rightIndex));
            break;

        case '/':
            result.fractions[result.counterD].index = i;
            for (int j = i - 1; j >= 0; j--)
            {
                if (input[j] == '+' || input[j] == '-')
                {
                    result.fractions[result.counterD].leftIndex = j;
                }
                else if (input[j] == '\0')
                {
                    result.fractions[result.counterD].leftIndex = '\0';
                }
                else if (input[j] == '*' || input[j] == '/')
                {
                    break;
                }
            }
            for (int j = i + 1; j < strlen(input); j++)
            {
                if (input[j] == '+' || input[j] == '-')
                {
                    result.fractions[result.counterD].rightIndex = j;
                }
                else if (input[j] == '\0')
                {
                    result.fractions[result.counterD].rightIndex = '\0';
                }
                else if (input[j] == '*' || input[j] == '/')
                {
                    break;
                }
            }
            result.counterD++;
            result.order[result.counterO++] = 0;
            Serial.println("Fraction: " + String(result.fractions[result.counterD - 1].leftIndex) + " " + String(result.fractions[result.counterD - 1].index) + " " + String(result.fractions[result.counterD - 1].rightIndex));
            break;

        default:
            break;
        }
    }
}

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
                findMultiplierAndDivisor(display.getText());
                display.clear();

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