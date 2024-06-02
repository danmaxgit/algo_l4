#include "stdio.h"
#include "time.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// БцццББ
//gf2
//A - 65, Z - 90, 0 - 48, 9 - 57
int hash(char *key) // min 0, max 1463
{
    int h = (int)key[1] + (int)key[2] + (int)key[3] +
            (int)key[4] +(int)key[5] + (int)key[6];
    h -= 274;
    h *= 19;
    return h;
}

bool validate_input(char *input) {
    if (strlen(input) != 6) {
        return false;
    }
    if ((input[0] >= 'A' && input[0] <= 'Z') && (input[1] >= '0' && input[1] <= '9') && \
    (input[2] >= '0' && input[2] <= '9') && (input[3] >= '0' && input[3] <= '9') && \
    (input[4] >= 'A' && input[4] <= 'Z') && (input[5] >= 'A' && input[5] <= 'Z')) {
        return true;
    }
    return false;
}

int main(int argc, char** argv){
    srand(time(NULL));
    char buff[100];
    //do {
    //    scanf("%s", buff);
    //} while (!validate_input(buff));
    char temp;
    int* map = (int*)malloc(sizeof(int) * 1464);
    for (int i = 0; i < 1464; i++) {
        map[i] = 0;
    }
    for (int i = 0; i < 10000; ++i) {
        for (int j = 0; j < 6; ++j) {
            switch (j) {
                case 0:
                case 4:
                case 5:
                    temp = (char) ((rand() % (90 - 65)) + 65);
                    break;
                case 1:
                case 2:
                case 3:
                    temp = (char) ((rand() % (48 - 57)) + 48);
                    break;
            }
            buff[j] = temp;
        }
        buff[7] = '\0';
        // printf("%s\n", buff);
        int h = hash(buff);
        map[h]++;
    }
    FILE *f = fopen("/home/danmax/code/saod/l4/data.csv", "w");
    for (int i = 0; i < 1464; i++) {
        fprintf(f, "%d,%d\n", i, map[i]);
    }

    fclose(f);
    free(map);
    return 0;   
}