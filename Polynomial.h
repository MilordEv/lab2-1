#ifndef __POLYNOMIAL__
#define __POLYNOMIAL__

#include <stdio.h>

struct RingInfo;

struct RingInfo* create(	
	size_t size,
	void* zero,
	void* one,
	//void* (*minus)(void*),
	void* (*sum)(void*, void*, void*),
	void* (*mult)(void*, void*, void*) );


struct Polynomial;

struct Polynomial* zero;
struct Polynomial* one;
struct Polynomial* fillingValues(struct RingInfo* ringInfo, int polynomialDegree, void* coefficients);

void* getCoefficient(struct Polynomial* polynom, int number);
int getDegree(struct Polynomial* polynom);

struct Polynomial* sumPolynom(struct Polynomial* polynom1, struct Polynomial* polynom2);

int freePolynomial(struct Polynomial* polynom);

#endif