#include <Calculator.h>
#include <Arduino.h>

// Calculator::FractionMultiplierIndexResult Calculator::findMultiplierAndDivisor(const char *input)
// {
//     Calculator::FractionMultiplierIndexResult result;
//     size_t inputSize = strlen(input);
//     String inputString = String(input);
//     int index[32];
//     while(inputString.indexOf('*') != -1){
//         index[result.counterM] = inputString.indexOf('*');

//         inputString[index[result.counterM]] = '@';
//         result.counterM++;
//     }

// }

// char *Calculator::multiplingAndDividing(char *input, Calculator::FractionMultiplierIndexResult indexes)
// {
//     size_t inputSize = strlen(input);
//     char *result = (char *)malloc(inputSize * sizeof(char));
//     short resultIndex = 0;
//     for (int i = 0; i < inputSize; i++)
//     {
//         int leftNumber = 0;
//         int rightNumber = 0;
//         for (int j = 0; j < indexes.counterM; j++)
//         {
//             Serial.println("Index: " + String(i));
//             if (i == indexes.multiplier[j].leftIndex)
//             {
//                 Serial.println("Index of multiplier: " + indexes.multiplier[j].leftIndex);
//                 for (int k = indexes.multiplier[j].leftIndex; k < indexes.multiplier[j].index; k++)
//                 {
//                     Serial.println("Left number processing: " + String(input[k]));
//                     leftNumber = (leftNumber * 10) + input[k];
//                 }
//                 for (int k = indexes.multiplier[j].index + 1; k <= indexes.multiplier[j].rightIndex; k++)
//                 {
//                     Serial.println("Right number processing: " + String(input[k]));
//                     rightNumber = (rightNumber * 10) + input[k];
//                 }
//                 i = indexes.multiplier[j].rightIndex;
//             }
//         }
//         {
//             if (leftNumber > 0 && rightNumber > 0)
//             {
//                 Serial.println("Left number: " + String(leftNumber));
//                 Serial.println("Right number: " + String(rightNumber));
//             }
//             else if (leftNumber > 0)
//             {
//                 Serial.println("Left number: " + String(leftNumber));
//             }
//             else if (rightNumber > 0)
//             {
//                 Serial.println("Right number: " + String(rightNumber));
//             }
//         }
//         result += leftNumber * rightNumber;
//     }
//     return result;
// }

String Calculator::multiplingAndDividing(String input)
{
    Serial.print("\n/----------------'*&/'---------------\\\n");
    String inputString = input;
    Serial.println("String: " + inputString);
    while (inputString.indexOf('*') != -1 || inputString.indexOf('/') != -1)
    {
        unsigned int index = (inputString.indexOf('*') == -1 ? inputString.indexOf('/') : inputString.indexOf('*')), indexL = -127, indexR = -127;

        Serial.print("Left side iteration: ");
        for (size_t i = index - 1; i >= 0; i--)
        {
            Serial.print(inputString[i]);
            if (inputString[i] == '+' || inputString[i] == '-' || inputString[i] == '*' || inputString[i] == '/')
            {
                indexL = i;
                Serial.print(">operator ");
                break;
            }
            else if (i == 0)
            {
                indexL = i;
                Serial.print(">end\n");
                break;
            }
        }
        Serial.print("Right side iteration: ");
        for (size_t i = index + 1; i < inputString.length(); i++)
        {
            Serial.print(inputString[i]);
            if (inputString[i] == '+' || inputString[i] == '-' || inputString[i] == '*' || inputString[i] == '/')
            {
                indexR = i - 1;
                Serial.print(">operator ");
                break;
            }
            else if (i == inputString.length() - 1)
            {
                indexR = i;
                Serial.print(">end\n");
                break;
            }
            Serial.print(">nothing ");
        }
        const String leftSide = inputString.substring(indexL, index);
        const String rightSide = inputString.substring(index + 1, indexR + 1);
        const String expression = inputString.substring(indexL, indexR + 1);
        int leftNumber = leftSide.toInt();
        int rightNumber = rightSide.toInt();
        int result = 0;
        if (inputString[index] == '*')
        {
            result = leftNumber * rightNumber;
        }
        else if (inputString[index] == '/')
        {
            result = leftNumber / rightNumber;
        }
        Serial.println("\nIndexes (L | * | R): " + String(indexL) + " | " + String(index) + " | " + String(indexR));
        // Serial.println("Left side: '" + leftSide + "' | Right side: '" + rightSide + "'");
        Serial.println("Left number: " + String(leftNumber) + " | Right number: " + String(rightNumber));
        Serial.println("Result: " + String(result));
        inputString.replace(expression, String(result));
        Serial.println("New String: " + inputString);
    }
    Serial.print("\n\\----------------'*&/'---------------/\n");
    return inputString;
}

String Calculator::addingAndSubtracting(String input)
{
    Serial.print("\n/----------------'+&-'---------------\\\n");
    String inputString = input;
    Serial.println("String: " + inputString);
    while (inputString.indexOf('+') != -1 || inputString.indexOf('-') != -1)
    {
        unsigned int index = (inputString.indexOf('+') == -1 ? inputString.indexOf('-') : inputString.indexOf('+')), indexL = -127, indexR = -127;

        Serial.print("Left side iteration: ");
        for (size_t i = index - 1; i >= 0; i--)
        {
            Serial.print(inputString[i]);
            if (inputString[i] == '+' || inputString[i] == '-' || inputString[i] == '*' || inputString[i] == '/')
            {
                indexL = i;
                Serial.print(">operator ");
                break;
            }
            else if (i == 0)
            {
                indexL = i;
                Serial.print(">end\n");
                break;
            }
        }
        Serial.print("Right side iteration: ");
        for (size_t i = index + 1; i < inputString.length(); i++)
        {
            Serial.print(inputString[i]);
            if (inputString[i] == '+' || inputString[i] == '-' || inputString[i] == '*' || inputString[i] == '/')
            {
                indexR = i - 1;
                Serial.print(">operator ");
                break;
            }
            else if (i == inputString.length() - 1)
            {
                indexR = i;
                Serial.print(">end\n");
                break;
            }
            Serial.print(">nothing ");
        }
        const String leftSide = inputString.substring(indexL, index);
        const String rightSide = inputString.substring(index + 1, indexR + 1);
        const String expression = inputString.substring(indexL, indexR + 1);
        int leftNumber = leftSide.toInt();
        int rightNumber = rightSide.toInt();
        int result = 0;
        if (inputString[index] == '+')
        {
            result = leftNumber + rightNumber;
        }
        else if (inputString[index] == '-')
        {
            result = leftNumber - rightNumber;
        }
        Serial.println("\nIndexes (L | * | R): " + String(indexL) + " | " + String(index) + " | " + String(indexR));
        // Serial.println("Left side: '" + leftSide + "' | Right side: '" + rightSide + "'");
        Serial.println("Left number: " + String(leftNumber) + " | Right number: " + String(rightNumber));
        Serial.println("Result: " + String(result));
        inputString.replace(expression, String(result));
        Serial.println("New String: " + inputString);
    }
    Serial.print("\n\\----------------'+&-'---------------/\n");
    return inputString;
}

String Calculator::calculate(String input)
{
    String result = input;
    result = multiplingAndDividing(result);
    result = addingAndSubtracting(result);
    return result;
}

char *Calculator::Utils::convertStrToCharPtr(String input)
{
    char *result = (char *)malloc(input.length() * sizeof(char));
    for (size_t i = 0; i < input.length(); i++)
    {
        result[i] = input[i];
    }
    return result;
}