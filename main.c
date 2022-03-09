#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "myReadline.h"
#include "Polynomial.h"
#include "wrapper.h"

int inputPolynomial(struct Polynomial** polynom, int* intOrDouble);
int mySum(struct Polynomial** polynom);
int myMultScalar(struct Polynomial** polynom);
int myMult(struct Polynomial** polynom);
int myComputoringValue(struct Polynomial* polynom, int intOrDouble);
int myCompositionPolynomial(struct Polynomial** polynom);
int outputPolynomial(struct Polynomial* polynom, int intOrDouble);


int main() {

    struct Polynomial* polynom = NULL;
    int intOrDouble = 0;

    while(1) {
 
        printf("\n");
 
        for(int i = 0; i < 40; i++) {
            printf("=");
        }
        printf("\nEnter:\n");
 
        printf("1 to enter polynomial\n");
        printf("2 for summation of polynomials\n");
        printf("3 for multiplication by scalar\n");
        printf("4 for multiplication of polynomials\n");
        printf("5 for computoring the value\n");
        printf("6 for composition of polynomials\n");
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
                inputPolynomial(&polynom, &intOrDouble);
                break;

            case 2:
                mySum(&polynom);
                break;

            case 3:
                myMultScalar(&polynom);
                break;

            case 4:
                myMult(&polynom);
                break;

            case 5:
                myComputoringValue(polynom, intOrDouble);
                break;

            case 6:
                myCompositionPolynomial(&polynom);
                break;

            case 7:
                outputPolynomial(polynom, intOrDouble);
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

                if (!polynom) {
                    freePolynomial(polynom);
                }

                if (intOrDouble == 1) {  
                    freeRinginfo(creareRingInfoInt());
                }

                if (intOrDouble == 2) {  
                    freeRinginfo(creareRingInfoDouble());
                }

                return 0;

            default:
                printf("You have entered an invalid value\n");
                break;
        }
    }
}


int inputPolynomial(struct Polynomial** polynom, int* intOrDouble) {

    if (*polynom) {
        freePolynomial(*polynom);
    }

    printf("\nEnter:\n");
 
    printf("1 to enter a polynomial with integer coefficients\n");
    printf("2 to enter a polynomial with real coefficients\n");


    for(int i = 0; i < 40; i++) {
        printf("-");
    }
    printf("\nEnter the action number:");

    *intOrDouble = 0;
    char *inputText = NULL;

    while (*intOrDouble == 0) {

        inputText = get_str();

        if (strlen(inputText) == 1 && ((inputText[0] == 49) || (inputText[0] == 50))) {

            *intOrDouble = atoi(inputText);

        }

    }

    free(inputText);

    if (*intOrDouble == 1) {

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

        free(inputText);

        *polynom = fillingValues(creareRingInfoInt(), polynomialDegree - 1, coefficients);

    } else if (*intOrDouble == 2) {

        printf("\n");
        printf("Enter the coefficients, in order to stop typing, enter only 'Enter' without the other characters:\n");

        double* coefficients = malloc(0);
        int polynomialDegree = 0;

        char* inputText = NULL;

        do {
    
            printf("coefficient for x^%d: ", polynomialDegree);
            inputText = get_str(); 

            if (atof(inputText) || inputText[0] == '0') {

                polynomialDegree++;
                coefficients = realloc(coefficients, polynomialDegree * sizeof(double));
                coefficients[polynomialDegree - 1] = atof(inputText);
            }

        } while (inputText[0] != '\0');

        free(inputText);

        *polynom = fillingValues(creareRingInfoDouble(), polynomialDegree - 1, coefficients);

    }

    return 0;

}

int mySum(struct Polynomial** polynom) {

    if (!polynom) {
       printf("First enter the polynomial");
       return -1;
    }

    struct Polynomial* polynom1 = *polynom;
    struct Polynomial* polynom2 = NULL;
    int intOrDouble2 = 0;
    inputPolynomial(&polynom2, &intOrDouble2);

    *polynom = sumPolynomial(polynom1, polynom2);

    if (!(*polynom)) {
        *polynom = polynom1;
        freePolynomial(polynom2);
    } else {
        freePolynomial(polynom1);
        freePolynomial(polynom2);
    }

    return 0;
}

int myMultScalar(struct Polynomial** polynom) {

    if (!polynom) {
       printf("First enter the polynomial");
       return -1;
    }
    
    char *inputText = NULL;

    do {

        printf("\nEnter the scalar:");

        inputText = get_str();

    } while (!(atoi(inputText) || (inputText[0] == '0' && strlen(inputText) == 1)));

    int scalar = atoi(inputText);
    free(inputText);

    *polynom = multScalar(*polynom, &scalar);

    return 0;
}

int myMult(struct Polynomial** polynom) {

    if (!polynom) {
       printf("First enter the polynomial");
       return -1;
    }

    struct Polynomial* polynom1 = *polynom;
    struct Polynomial* polynom2 = NULL;
    int intOrDouble2 = 0;
    inputPolynomial(&polynom2, &intOrDouble2);

    *polynom = multPolynomial(polynom1, polynom2);

    if (!(*polynom)) {
        *polynom = polynom1;
        freePolynomial(polynom2);
    } else {
        freePolynomial(polynom1);
        freePolynomial(polynom2);
    }

    return 0;
}

int myComputoringValue(struct Polynomial* polynom, int intOrDouble) {

    if (!polynom) {
        printf("First enter the polynomial");
        return -1;
    }
    
    char *inputText = NULL;

    if (intOrDouble == 1) {

        do {

            printf("\nEnter the value of x:");

            inputText = get_str();

        } while (!(atoi(inputText) || (inputText[0] == '0' && strlen(inputText) == 1)));

        int value = atoi(inputText);
        free(inputText);

        void* result = computingValue(polynom, &value);

        printf("The value of polynomial: %d\n", *((int*) result));

        free(result);
        
    } else if (intOrDouble == 2) {

        do {

            printf("\nEnter the value of x:");

            inputText = get_str();

        } while (!(atof(inputText) || (inputText[0] == '0' && strlen(inputText) == 1)));

        double value = atof(inputText);
        free(inputText);

        void* result = computingValue(polynom, &value);

        printf("The value of polynomial: %lf\n", *((double*) result));

        free(result);

    }

    return 0;
}

int myCompositionPolynomial(struct Polynomial** polynom) {

    if (!polynom) {
        printf("First enter the polynomial");
        return -1;
    }

    struct Polynomial* polynom1 = *polynom;
    struct Polynomial* polynom2 = NULL;
    int intOrDouble2 = 0;
    inputPolynomial(&polynom2, &intOrDouble2);

    *polynom = compositionPolynomial(polynom1, polynom2);

    if (!(*polynom)) {
        *polynom = polynom1;
        freePolynomial(polynom2);
    } else {
        freePolynomial(polynom1);
        freePolynomial(polynom2);
    }

    return 0;
}


int outputPolynomial(struct Polynomial* polynom, int intOrDouble) {  

    if (!polynom) {
       printf("First enter the polynomial");
       return -1;
    }

    printf("P(x) = ");

    int specialCase = 0;

    if (intOrDouble == 1) {
        
        for (int i = 0; i <= getDegree(polynom); i++) {
            int* coefficient = (int*) getCoefficient(polynom, i);

            if (!(*coefficient)) {
                continue;
            }

            if (i == 0) {
                specialCase = 1;
            }

            if (i == 1 && specialCase && (*coefficient) > 0) {
                printf("+");
            }

            if (i > 1 && (*coefficient) > 0) {
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

    } else if (intOrDouble == 2) {

        for (int i = 0; i <= getDegree(polynom); i++) {
            double* coefficient = (double*) getCoefficient(polynom, i);

            if (!(*coefficient)) {
                continue;
            }

            if (i == 0) {
                specialCase = 1;
            }

            if (i == 1 && specialCase && (*coefficient) > 0) {
                printf("+");
            }

            if (i > 1 && (*coefficient) > 0) {
                printf("+");
            }

            if ((*coefficient) == 1) {
                printf(" x^%d ", i);
            } else if ((*coefficient) == -1) {
                printf(" -x^%d ", i);
            } else {
                printf(" %lfx^%d ", *coefficient, i);
            }
        }

    }

    return 0;
}