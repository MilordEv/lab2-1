#include "myReadline.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

char *get_str()
{

    char buf[81] = {0};
    char *res = NULL;
    int Len = 0;
    int n = 0;

    do {
        n = scanf("%80[^\n]", buf);


        if (n < 0) {
            if (!res) {
                return NULL;
            }
        }
        else if (n > 0) {
            int chunk_len = strlen(buf);
            int str_len = Len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + Len, buf, chunk_len);
            Len = str_len;
        }
        else {
            scanf("%*c");
        }
    } while (n > 0);

    if (Len > 0) {
        res[Len] = '\0';
    }
    else {
        res = calloc(1, sizeof(char));
    }

    return res;
}