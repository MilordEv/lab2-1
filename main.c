#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "myReadline.h"

int main() {

    while(1) {
 
        printf("\n");
 
        for(int i = 0; i < 40; i++) {
            printf("=");
        }
        printf("\nEnter:\n");
 
        printf("1 to enter polynomial\n");
        //printf("2 to process the data\n");
        //printf("3 to output data\n");
        printf("0 to exit the program\n");
 
 
        for(int i = 0; i < 40; i++) {
            printf("-");
        }
        printf("\nEnter the action number:");

        int number = -1;
 
        char *numberText = NULL;
        numberText = get_str();
 
        if (strlen(numberText) == 1 && (numberText[0] > 47) && (numberText[0] < 58)) {
 
            number = atoi(numberText);
 
        } else {
            number = -1;
        }
 
        free(numberText);
 
        switch(number) {
            case 1:
                break;

            case 2:
                break;

            case 3:
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
