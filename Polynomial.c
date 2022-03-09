#include <malloc.h>
#include "Polynomial.h"


struct RingInfo {
    size_t size;
	void* zero;
	void* one;
	//void* (*minus)(void*);
	void* (*sum)(void*, void*, void*);
	void* (*mult)(void*, void*, void*);
};

struct RingInfo* create(	
    size_t size,
    void* zero,
    void* one,
    //void* (*minus)(void*),
    void* (*sum)(void*, void*, void*),
    void* (*mult)(void*, void*, void*) )
{
	struct RingInfo* ringInfo = malloc(sizeof(struct RingInfo));
	ringInfo->size = size;
	ringInfo->zero = zero;
	ringInfo->one = one;
	//ringInfo->minus = minus;
	ringInfo->sum = sum;
	ringInfo->mult = mult;

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

struct Polynomial* sumPolynomial(struct Polynomial* polynom1, struct Polynomial* polynom2) {

    struct Polynomial* resultPolynom = malloc(sizeof(struct Polynomial));

    if (polynom1->ringInfo->sum != polynom2->ringInfo->sum) {

        return NULL;
    }

    if (polynom1->polynomialDegree >= polynom2->polynomialDegree) {

        resultPolynom->polynomialDegree = polynom1->polynomialDegree;
        resultPolynom->ringInfo = polynom1->ringInfo;
        resultPolynom->coefficients = malloc(resultPolynom->ringInfo->size * (resultPolynom->polynomialDegree + 1));

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
        resultPolynom->coefficients = malloc(resultPolynom->ringInfo->size * (resultPolynom->polynomialDegree + 1));


        for (int i = 0; i <= polynom1->polynomialDegree; i++) {
            resultPolynom->ringInfo->sum(polynom1->coefficients + i * resultPolynom->ringInfo->size, polynom2->coefficients + i * resultPolynom->ringInfo->size, resultPolynom->coefficients + i * resultPolynom->ringInfo->size);
        }

        for (int i = polynom1->polynomialDegree + 1; i <= polynom2->polynomialDegree; i++) {
            resultPolynom->ringInfo->sum(resultPolynom->ringInfo->zero, polynom2->coefficients + i * resultPolynom->ringInfo->size, resultPolynom->coefficients + i * resultPolynom->ringInfo->size);
        }

    }

    return resultPolynom;
}

struct Polynomial* multScalar(struct Polynomial* polynom, void* scalar) {

    for (int i = 0; i <= polynom->polynomialDegree; i++) {
        polynom->ringInfo->mult( polynom->coefficients + i * (polynom->ringInfo->size), scalar, polynom->coefficients + i * (polynom->ringInfo->size));
    }

    return polynom;
}

struct Polynomial* multPolynomial(struct Polynomial* polynom1, struct Polynomial* polynom2) {

    if (polynom1->ringInfo->mult != polynom2->ringInfo->mult) {
        return NULL;
    }

    struct Polynomial* resultPolynom = malloc(sizeof(struct Polynomial));
    resultPolynom->ringInfo = polynom1->ringInfo;
    resultPolynom->polynomialDegree = polynom1->polynomialDegree + polynom2->polynomialDegree;
    resultPolynom->coefficients = malloc(resultPolynom->ringInfo->size * (resultPolynom->polynomialDegree + 1));

    for (int i = 0; i <= resultPolynom->polynomialDegree; i++) {
        resultPolynom->ringInfo->sum(resultPolynom->ringInfo->zero, resultPolynom->ringInfo->zero, resultPolynom->coefficients + i * resultPolynom->ringInfo->size);
    }

    void* buf = malloc(sizeof(resultPolynom->ringInfo->size));

    for (int i = 0; i <= polynom1->polynomialDegree; i++) {
        for (int j = 0; j <= polynom2->polynomialDegree; j++) {

            resultPolynom->ringInfo->mult(polynom1->coefficients + i * polynom1->ringInfo->size, polynom2->coefficients + j * polynom2->ringInfo->size, buf);

            resultPolynom->ringInfo->sum(buf, resultPolynom->coefficients + (i + j) * resultPolynom->ringInfo->size, resultPolynom->coefficients + (i + j) * resultPolynom->ringInfo->size);
        }
    }

    free(buf);

    return resultPolynom;
}

void* computingValue(struct Polynomial* polynom, void* value) {
    void* result = malloc(sizeof(polynom->ringInfo->size));

    polynom->ringInfo->sum(polynom->ringInfo->zero, polynom->ringInfo->zero, result);

    void* buf1 = malloc(sizeof(polynom->ringInfo->size));
    void* buf2 = malloc(sizeof(polynom->ringInfo->size));

    polynom->ringInfo->sum(polynom->ringInfo->zero, polynom->ringInfo->one, buf1);

    for (int i = 0; i <= polynom->polynomialDegree; i++) {
        polynom->ringInfo->mult(buf1, polynom->coefficients + i * polynom->ringInfo->size, buf2);
        polynom->ringInfo->sum(buf2, result, result);
        polynom->ringInfo->mult(buf1, value, buf1);
    }

    free(buf1);
    free(buf2);

    return result;
}

struct Polynomial* compositionPolynomial(struct Polynomial* polynom1, struct Polynomial* polynom2) {

    if (polynom1->ringInfo->mult != polynom1->ringInfo->mult) {
        return NULL;
    }

    struct Polynomial* resultPolynom = malloc(sizeof(struct Polynomial));
    resultPolynom->ringInfo = polynom1->ringInfo;
    resultPolynom->polynomialDegree = polynom1->polynomialDegree * polynom2->polynomialDegree;
    resultPolynom->coefficients = malloc(resultPolynom->ringInfo->size * (resultPolynom->polynomialDegree + 1));

    for (int i = 0; i <= resultPolynom->polynomialDegree; i++) {
        resultPolynom->ringInfo->sum(resultPolynom->ringInfo->zero, resultPolynom->ringInfo->zero, resultPolynom->coefficients + i * resultPolynom->ringInfo->size);
    }

    struct Polynomial* bufPolynom1 = malloc(sizeof(struct Polynomial));
    struct Polynomial* bufPolynom2 = NULL;

    bufPolynom1->ringInfo = polynom1->ringInfo;
    bufPolynom1->polynomialDegree = 0;
    bufPolynom1->coefficients = malloc(sizeof(bufPolynom1->ringInfo->size));
    bufPolynom1->ringInfo->sum(bufPolynom1->ringInfo->zero, bufPolynom1->ringInfo->one, bufPolynom1->coefficients);

    for (int i = 0; i <= polynom2->polynomialDegree; i++) {

        struct Polynomial* bufCleaning = resultPolynom;
        resultPolynom = sumPolynomial(resultPolynom, multScalar(bufPolynom1, polynom2->coefficients + i * polynom2->ringInfo->size));
        freePolynomial(bufCleaning);

        bufPolynom2 = bufPolynom1;
        bufPolynom1 = multPolynomial(bufPolynom1, polynom1);
        if (i != 1) {
            free(bufPolynom2);
        }

    }

    if (!bufPolynom1) {
        freePolynomial(bufPolynom1);
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