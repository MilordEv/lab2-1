#include <malloc.h>
#include "Polynomial.h"


struct RingInfo {
    size_t size;
	void* zero;
	void* one;
	//void* (*minus)(void*);
	void* (*sum)(void*, void*, void*);
	//void* (*mult)(void*, void*);
};

struct RingInfo* create(	
    size_t size,
    void* zero,
    void* one,
    //void* (*minus)(void*),
    void* (*sum)(void*, void*, void*)
    /*void* (*mult)(void*, void*) */)
{
	struct RingInfo* ringInfo = malloc(sizeof(struct RingInfo));
	ringInfo->size = size;
	ringInfo->zero = zero;
	ringInfo->one = one;
	//ringInfo->minus = minus;
	ringInfo->sum = sum;
	//ringInfo->mult = mult;

	return ringInfo;	
}




struct Polynomial {
    struct RingInfo* ringInfo;
    int polynomialDegree;
    void* coefficients;
};

struct Polynomial* fillingValues(struct RingInfo* ringInfo, int polynomialDegree, void* coefficients) {

    struct Polynomial* polynom = malloc(sizeof(struct Polynomial));
    polynom->ringInfo = ringInfo;
    polynom->polynomialDegree = polynomialDegree;
    polynom->coefficients = coefficients;

    return polynom;
}


void* getCoefficient(struct Polynomial* polynom, int number) {
    return (polynom->coefficients + polynom->ringInfo->size * number);
}

int getDegree(struct Polynomial* polynom) {
    return polynom->polynomialDegree;
}

struct Polynomial* sumPolynom(struct Polynomial* polynom1, struct Polynomial* polynom2) {

    struct Polynomial* resultPolynom = malloc(sizeof(struct Polynomial));

    if (polynom1->polynomialDegree >= polynom2->polynomialDegree) {

        resultPolynom->polynomialDegree = polynom1->polynomialDegree;
        resultPolynom->ringInfo = polynom1->ringInfo;
        resultPolynom->coefficients = malloc(resultPolynom->ringInfo->size * resultPolynom->polynomialDegree);

        for (int i = 0; i <= polynom2->polynomialDegree; i++) {
            resultPolynom->ringInfo->sum(polynom1->coefficients + i * resultPolynom->ringInfo->size, polynom2->coefficients + i * resultPolynom->ringInfo->size, resultPolynom->coefficients + i * resultPolynom->ringInfo->size);
        }

        for (int i = polynom2->polynomialDegree + 1; i <= polynom1->polynomialDegree; i++) {
            resultPolynom->ringInfo->sum(resultPolynom->ringInfo->zero, polynom1->coefficients + i * resultPolynom->ringInfo->size, resultPolynom->coefficients + i * resultPolynom->ringInfo->size);
        }

    }

    if (polynom1->polynomialDegree < polynom2->polynomialDegree) {

        resultPolynom->polynomialDegree = polynom2->polynomialDegree;
        resultPolynom->ringInfo = polynom2->ringInfo;
        resultPolynom->coefficients = malloc(resultPolynom->ringInfo->size * resultPolynom->polynomialDegree);


        for (int i = 0; i <= polynom1->polynomialDegree; i++) {
            resultPolynom->ringInfo->sum(polynom1->coefficients + i * resultPolynom->ringInfo->size, polynom2->coefficients + i * resultPolynom->ringInfo->size, resultPolynom->coefficients + i * resultPolynom->ringInfo->size);
        }

        for (int i = polynom1->polynomialDegree + 1; i <= polynom2->polynomialDegree; i++) {
            resultPolynom->ringInfo->sum(resultPolynom->ringInfo->zero, polynom2->coefficients + i * resultPolynom->ringInfo->size, resultPolynom->coefficients + i * resultPolynom->ringInfo->size);
        }

    }

    return resultPolynom;
}

int freePolynomial(struct Polynomial* polynom) {

    if (!(polynom->coefficients)) {
        free(polynom->coefficients);
    }
    if (!polynom) {
        free(polynom);
    }

    return 0;
}