#ifndef __POLYNOMIAL__
#define __POLYNOMIAL__

struct Polynomial;

struct Polynomial* zero;
struct Polynomial* one;
struct Polynomial* fillingValues;

void* getCoefficients(struct Polynomial* polynom);
int getDegree(struct Polynomial* polynom);

#endif