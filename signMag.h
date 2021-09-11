#ifndef SIGNMAG_H
#define SIGNMAG_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    bool isNegative;
    uint16_t magnitude;
} SignMag_t;

SignMag_t signMag_init(bool isNegative, uint16_t magnitude);
void signMag_print(SignMag_t value);
SignMag_t signMag_read(void);
SignMag_t signMag_sum(SignMag_t sm1, SignMag_t sm2);
SignMag_t signMag_accumulate(const SignMag_t* array, size_t arraySize);
SignMag_t signMag_multiply(SignMag_t num1, SignMag_t num2);
bool signMag_max(SignMag_t* num1, SignMag_t* num2, SignMag_t** max);

#endif
