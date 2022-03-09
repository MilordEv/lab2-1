#ifndef __WRAPPER__
#define __WRAPPER__

#include "Polynomial.h"

struct RingInfo* ringInfoInt;

void* sumInt(void* dig1, void* dig2, void* res);
void* multInt(void* dig1, void* dig2, void* res);
void* minusInt(void* dig);

struct RingInfo* creareRingInfoInt();

struct RingInfo* ringInfoFDouble;

void* sumDouble(void* dig1, void* dig2, void* res);
void* multDouble(void* dig1, void* dig2, void* res);
void* minusDouble(void* dig);

struct RingInfo* creareRingInfoDouble();

#endif