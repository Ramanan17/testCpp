//MODIFICATIONS HAVE NO EFFECT
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "signMag.h"

//gcc -Wall -Werror main.c signMag.c signMag_mult.o

SignMag_t* arrayMax(SignMag_t* array, size_t size, bool (*func)(SignMag_t*, SignMag_t*, SignMag_t**))
{
    SignMag_t* result = array;
    for (size_t i=1; i<size; ++i) {
        (*func)(result, array+i, &result);
    }
    return result;
}

int main(void)
{
    //1.Reads in an array of sign magnitude values. Reading terminates when either
    //the an invalid number is entered (such as the word "quit") or to a maximum
    //of 100 values.
    int maxValues = 100;
    SignMag_t input[maxValues];
    int arraySize = 0;
    for (size_t i = 0; i < maxValues; i++)
    {
        /* code */
        SignMag_t inputValue = signMag_read();
        input[i] = inputValue;
        arraySize++;
    }
    
    // //2.Print out the array of values, one per line, using your signMag_print()
    // //function.
    for (size_t i = 0; i < arraySize; i++)
    {
        /* code */
        signMag_print(input[i]);
    }
    

    //3.Compute the accumulated sum of the values in the array and print this using
    //your signMag_print() function
    SignMag_t accSum = signMag_accumulate(input, arraySize);
    signMag_print(accSum);

    //4.Compute the square of the accumulated sum in the array
    //(using signMag_multiply()) and print this using your signMag_print() function.
    signMag_print(signMag_multiply(accSum,accSum));

    //5.Find the maximum sign magnitude value in the array using your arrayMax()
    //function together with signMag_max() and print this using your signMag_print() function.
    SignMag_t* maximumValue = arrayMax(input,arraySize,signMag_max);
    signMag_print(*maximumValue);

}
