#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "signMag.h"
typedef unsigned int uint;

SignMag_t signMag_init(bool isNegative, uint16_t magnitude)
{
    SignMag_t sign;
    sign.isNegative = isNegative;
    sign.magnitude = magnitude;
    return sign;
}

void signMag_print(SignMag_t value)
{
    if (value.isNegative == true) {
        printf("%s%hu\n","-", value.magnitude);
    } else {
        printf("%hu\n",value.magnitude);
    }
}

SignMag_t signMag_read(void)
{
    // Create a SignMag_t type
    SignMag_t num;
    char number[65535];
    size_t i = 0;

    while (number[i-1] != '\n' && number[i-1] != EOF && number[i-1] != ' ') {
        if (isalpha(number[i-1])) {
            break;
        }
        number[i++] = getchar();
    }

    // Check if the first character is representing sign or not
    if (number[0] == '-') {
        num.isNegative = true;
    } else if (number[0] == '+' || isdigit(number[0])) {
        num.isNegative = false;
    } else {
        // If the value is not legitimate return -0 (isNegative = true and magnitude = 0)
        num.isNegative = true;
        num.magnitude = 0;
    }

    // Convert the string array into integers
    if (num.isNegative == false) {
        uint tmp = atoi(number);
        num.magnitude = (tmp >= 65535) ? 65535 : tmp;
    } else {
        uint tmp = atoi(number+1);
        num.magnitude = (tmp >= 65535) ? 65535 : tmp;
    }
    return num;
}

SignMag_t signMag_sum(SignMag_t sm1, SignMag_t sm2)
{
    uint sum;
    bool isNegative;
    if (sm1.isNegative == true && sm2.isNegative == true) {
        sum = (sm1.magnitude + sm2.magnitude);
        isNegative = true;
    } else if (sm1.isNegative == false && sm2.isNegative == false) {
        sum = sm1.magnitude + sm2.magnitude;
        isNegative = false;
    } else if (sm1.isNegative == false && sm2.isNegative == true) {
        if (sm1.magnitude >= sm2.magnitude) {
            sum = sm1.magnitude - sm2.magnitude;
            isNegative = false;
        } else {
            sum = sm2.magnitude - sm1.magnitude;
            isNegative = true;
        }
    } else {
        if (sm1.magnitude <= sm2.magnitude) {
            sum = sm2.magnitude - sm1.magnitude;
            isNegative = false;
        } else {
            sum = sm1.magnitude - sm2.magnitude;
            isNegative = true;
        }
    }

    sum = ((sum >= 65535) ? 65535 : sum);
    SignMag_t value;
    value.isNegative = isNegative;
    value.magnitude = sum;
    return value;
}

SignMag_t signMag_accumulate(const SignMag_t* array, size_t arraySize)
{
    SignMag_t result = array[0];
    size_t i;
    for (i=1; i<arraySize; i++) {
        result = signMag_sum(result, array[i]);
    }
    return result;
}

bool signMag_max(SignMag_t* num1, SignMag_t* num2, SignMag_t** max)
{

    if (num1->isNegative == true && num2->isNegative == true) {
        if (num1->magnitude > num2->magnitude) {
            *max = num2;
        } else {
            *max = num1;
        }
    } else if (num1->isNegative == false && num2->isNegative == false) {
        if (num1->magnitude > num2->magnitude) {
            *max = num1;
        } else {
            *max = num2;
        }
    } else if (num1->isNegative == false && num2->isNegative == true) {
        *max = num1;
    } else {
        *max = num2;
    }

    // magnitude is a 16-bit value
    // maximum 16-bit unsigned value is 2^16 - 1 = 65535
    return num1->magnitude == 65535 || num2->magnitude == 65535;
}
