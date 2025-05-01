#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED
#include"list.h"
#define SCALE 31


int compareEqual(number a, number b);
void decimalEqual(number *a, number *b);
void lengthEqual(number *a, number *b);
int zeroNumber(number a);
void copy(number *a, number *b);
number *add(number *a, number *b);
number *sub(number *a, number *b);
number *mult(number *a, number *b);
number *division(number *a, number *b);
number *factorial(number *a);
number *modulus(number *a, number *b);



#endif // FUNCTION_H_INCLUDED
