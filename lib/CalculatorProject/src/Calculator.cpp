#include <Calculator.h>

Calculator::FractionMultiplierIndexResult Calculator::findMultiplierAndDivisor(char *input)
{
    Calculator::FractionMultiplierIndexResult result;
    size_t inputSize = strlen(input);
    Serial.println("Input: '" + String(input) + "'");
    for (size_t i = 0; i < inputSize; i++)
    {
        switch (input[i])
        {
        case '*':
            result.multiplier[result.counterM].index = i;
            for (size_t j = i - 1; j >= 0; j--)
            {
                if (input[j] == '+' || input[j] == '-' || input[j] == '*' || input[j] == '/')
                {
                    result.multiplier[result.counterM].leftIndex = j + 1;
                    break;
                }
                else if (j == 0)
                {
                    result.multiplier[result.counterM].leftIndex = 0;
                    break;
                }
            }
            for (size_t j = i + 1; j < strlen(input); j++)
            {
                if (input[j] == '+' || input[j] == '-' || input[j] == '*' || input[j] == '/')
                {
                    result.multiplier[result.counterM].rightIndex = j - 1;
                    break;
                }
                else if (j == inputSize - 1)
                {
                    result.multiplier[result.counterM].rightIndex = 255;
                    break;
                }
            }
            result.counterM++;
            result.order[result.counterO++] = 1;
            Serial.println("Multiplier: " + String(result.multiplier[result.counterM - 1].leftIndex) + " " + String(result.multiplier[result.counterM - 1].index) + " " + String(result.multiplier[result.counterM - 1].rightIndex));
            break;

        case '/':
            result.fractions[result.counterD].index = i;
            for (size_t j = i - 1; j >= 0; j--)
            {
                if (input[j] == '+' || input[j] == '-' || input[j] == '*' || input[j] == '/')
                {
                    result.fractions[result.counterD].leftIndex = j + 1;
                    break;
                }
                else if (input[j] == '\0')
                {
                    result.fractions[result.counterD].leftIndex = 0;
                    break;
                }
            }
            for (size_t j = i + 1; j < strlen(input); j++)
            {
                if (input[j] == '+' || input[j] == '-' || input[j] == '*' || input[j] == '/')
                {
                    result.fractions[result.counterD].rightIndex = j - 1;
                    break;
                }
                else if (input[j] == '\0')
                {
                    result.fractions[result.counterD].rightIndex = 255;
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
    return result;
}

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

char* Calculator::multiplingAndDividing(char *input, Calculator::FractionMultiplierIndexResult indexes){


}