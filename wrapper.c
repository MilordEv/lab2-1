#include <malloc.h>
#include "Polynomial.h"

struct RingInfo* ringInfoInt = NULL;

void* sumInt(void* dig1, void* dig2, void* res) {

    int* digInt1 = (int*) dig1;
    int* digInt2 = (int*) dig2;
    int* resInt = (int*) res;
    *resInt = *digInt1 + *digInt2;
}

void* multInt(void* dig1, void* dig2, void* res) {

    int* digInt1 = (int*) dig1;
    int* digInt2 = (int*) dig2;
    int* resInt = (int*) res;
    *resInt = *digInt1 * *digInt2;
}

void* minusInt(void* dig) {
    int* digInt = (int*) dig;
    *digInt = *digInt * -1;
}

struct RingInfo* creareRingInfoInt() {
    if(!ringInfoInt) {
        int* elements = malloc(2 * sizeof(int));
        elements[0] = 0;
        elements[1] = 1;
        ringInfoInt = create(sizeof(int), elements,  elements + 1, &minusInt, &sumInt, &multInt);
    }
    return ringInfoInt;
}

struct RingInfo* ringInfoDouble = NULL;

void* sumDouble(void* dig1, void* dig2, void* res) {

    double* digInt1 = (double*) dig1;
    double* digInt2 = (double*) dig2;
    double* resInt = (double*) res;
    *resInt = *digInt1 + *digInt2;
}

void* multDouble(void* dig1, void* dig2, void* res) {

    double* digInt1 = (double*) dig1;
    double* digInt2 = (double*) dig2;
    double* resInt = (double*) res;
    *resInt = *digInt1 * *digInt2;
}

void* minusDouble(void* dig) {
    double* digInt = (double*) dig;
    *digInt = *digInt * -1;
}

struct RingInfo* creareRingInfoDouble() {
    if(!ringInfoDouble) {
        double* elements = malloc(2 * sizeof(double));
        elements[0] = 0;
        elements[1] = 1;
        ringInfoDouble = create(sizeof(double), elements,  elements + 1, &minusDouble, &sumDouble, &multDouble);
    }
    return ringInfoDouble;
}