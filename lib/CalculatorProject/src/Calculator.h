#ifndef Calculator_h
#define Calculator_h
#pragma once
#include <Arduino.h>

namespace Calculator
{
    struct Fraction
    {
        uint8_t index = 0;        // index of the operator
        uint8_t leftIndex = 0;  // index to the left till the operator can influence
        uint8_t rightIndex = 0; // index to the right till the operator can influence
    };

    struct Multiplier
    {
        uint8_t index = 0;      // index of the operator
        uint8_t leftIndex = 0;  // index to the left till the operator can influence
        uint8_t rightIndex = 0; // index to the right till the operator can influence
    };

    struct FractionMultiplierIndexResult
    {
        uint8_t counterM; // counter for multiplier
        uint8_t counterD; // counter for divisor
        uint8_t counterO; // counter for order
        Fraction fractions[16];
        Multiplier multiplier[16];
        uint8_t order[16]; // 0 = fraction, 1 = multiplier
    };

    FractionMultiplierIndexResult findMultiplierAndDivisor(char* input);
    char* multiplingAndDividing(char* input, FractionMultiplierIndexResult indexes);
    char* addingAndSubtracting(char* input);
}

#endif // Calculator_h