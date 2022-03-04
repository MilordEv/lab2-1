#include "Polynomial.h"
#include <malloc.h>

struct Polynomial {
    struct RingInfo* ringInfo;
    int polynomialDegree;
    void* coefficients;
};