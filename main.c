#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "myReadline.h"
#include "Polynomial.h"

struct RingInfo* ringInfoInt = NULL;


int inputPolynomial(struct Polynomial** polynom, int* intOrFloat);
void* sumInt(void* dig1, void* dig2, void* res);
int mySum(struct Polynomial** polynom, int intOrFloat);
int outputPolynomial(struct Polynomial* polynom, int intOrFloat);

struct RingInfo* creareRingInfoInt() {
    if(!ringInfoInt) {
        int* elements = malloc(2 * sizeof(int));
        elements[0] = 0;
        elements[1] = 1;
        ringInfoInt = create(sizeof(int), elements,  elements + 1, &sumInt);
    }
    return ringInfoInt;
}


int main() {

    struct Polynomial* polynom = NULL;
    int intOrFloat = 0;

    while(1) {
 
        printf("\n");
 
        for(int i = 0; i < 40; i++) {
            printf("=");
        }
        printf("\nEnter:\n");
 
        printf("1 to enter polynomial\n");
        printf("2 for summation of polynomials\n");
        //printf("3 to output data\n");
        printf("7 to displaying a polynomial\n");
        printf("0 to exit the program\n");
 
 
        for(int i = 0; i < 40; i++) {
            printf("-");
        }
        printf("\nEnter the action number:");

        int number = -1;
 
        char *inputText = NULL;
        inputText = get_str();
 
        if (strlen(inputText) == 1 && (inputText[0] > 47) && (inputText[0] < 58)) {
 
            number = atoi(inputText);
 
        } else {
            number = -1;
        }
 
        free(inputText);
 
        switch(number) {
            case 1:
                inputPolynomial(&polynom, &intOrFloat);
                break;

            case 2:
                mySum(&polynom, intOrFloat);
                break;

            case 3:
                break;

            case 7:
                outputPolynomial(polynom, intOrFloat);
                break;

            case 0:

                printf("\nExiting the program\n");
                for(int i = 0; i < 20; i++) {
                    printf("x");
                    if (i != 19) {
                        printf("-");
                    }
                }
                printf("\n\n");
                return 0;

            default:
                printf("You have entered an invalid value\n");
                break;
        }
    }
}

void* sumInt(void* dig1, void* dig2, void* res) {

    int* digInt1 = (int*) dig1;
    printf("\n\n%d\n\n", *digInt1);
    int* digInt2 = (int*) dig2;
    int* resInt = (int*) res;
    *resInt = *digInt1 + *digInt2;
}

int inputPolynomial(struct Polynomial** polynom, int* intOrFloat) {

    printf("\nEnter:\n");
 
    printf("1 to enter a polynomial with integer coefficients\n");
    printf("2 to enter a polynomial with real coefficients\n");


    for(int i = 0; i < 40; i++) {
        printf("-");
    }
    printf("\nEnter the action number:");

    *intOrFloat = 0;
    char *inputText = NULL;

    while (*intOrFloat == 0) {

        inputText = get_str();

        if (strlen(inputText) == 1 && ((inputText[0] == 49) || (inputText[0] == 50))) {

            *intOrFloat = atoi(inputText);

        }

    }

    free(inputText);

    if (*intOrFloat == 1) {

        printf("\n");
        printf("Enter the coefficients, in order to stop typing, enter only 'Enter' without the other characters:\n");

        int* coefficients = malloc(0);
        int polynomialDegree = 0;

        char* inputText = NULL;

        do {
    
            printf("coefficient for x^%d: ", polynomialDegree);
            inputText = get_str(); 

            if (atoi(inputText) || inputText[0] == '0') {

                polynomialDegree++;
                coefficients = realloc(coefficients, polynomialDegree * sizeof(int));
                coefficients[polynomialDegree - 1] = atoi(inputText);
            }


        } while (inputText[0] != '\0');

        //int zero = 0;   
        //int one = 1;

        //struct RingInfo* ringInfoInt = create(sizeof(int), (void*) &zero, (void*) &one, &sumInt);


        *polynom = fillingValues(creareRingInfoInt(), polynomialDegree - 1, coefficients);

        
    }

    return 0;

}

int mySum(struct Polynomial** polynom, int intOrFloat) {

    struct Polynomial* polynom1 = *polynom;
    struct Polynomial* polynom2 = NULL;
    int intOrFloat2 = 0;
    inputPolynomial(&polynom2, &intOrFloat2);

    if(intOrFloat != intOrFloat2) {
        printf("the coefficients must be of the same data type\n");
        freePolynomial(polynom2);

        return -1;
    }

    *polynom = sumPolynom(polynom1, polynom2);
    freePolynomial(polynom1);
    freePolynomial(polynom2);


    return 0;
}

int outputPolynomial(struct Polynomial* polynom, int intOrFloat) {  

    printf("P(x) = ");

    if (intOrFloat == 1) {
        
        for (int i = 0; i <= getDegree(polynom); i++) {
            int* coefficient = (int*) getCoefficient(polynom, i);

            if (!(*coefficient)) {
                continue;
            }

            if (i > 0 && (*coefficient) > 0) {
                printf("+");
            }

            if ((*coefficient) == 1) {
                printf(" x^%d ", i);
            } else if ((*coefficient) == -1) {
                printf(" -x^%d ", i);
            } else {
                printf(" %dx^%d ", *coefficient, i);
            }
        }

    } 

    return 0;

}