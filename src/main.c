#include "stdio.h"
#include "time.h"
#include <complex.h>
#include <stdbool.h>
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




typedef struct Node{
    char value[7];
    int num;
    struct Node* next;
} Node;

typedef struct HashMap {
    Node* data;
    int (*hash)(char*);
    int size;
} HashMap;

HashMap* init_hash(int len, int (*h)(char*)){
    HashMap* m = (HashMap*)malloc(sizeof(HashMap));
    m->data = (Node*)malloc(sizeof(Node)*len);
    for (int i = 0; i < len; ++i) {
        m->data[i].next = NULL;
    }
    m->hash = h;
    m->size = len;
    return m;
}
void free_hash(HashMap *m){
    Node* data[10000];
    int size = 0;
    for (int i = 0; i < m->size; i++) {
        if (m->data[i].next) {
            Node* t = m->data[i].next;
            data[size] = t;
            size++;
            while (t->next) {
                t = t->next;
                data[size] = t;
                size++;
            }
            for (int i = 0; i < size; i++) {
                free(data[i]);
            }
        }
        size = 0;
    }
    free(m->data);
    free(m);
}
void append_hash(HashMap *m, char *v){
    if (m->data[m->hash(v)].num == 0) {
        for (int i = 0; i < 7; i++) {
            m->data[m->hash(v)].value[i] = v[i];
        }
        m->data[m->hash(v)].num++;
    }
    else {
        Node* t = &m->data[m->hash(v)];
        m->data[m->hash(v)].num++;
        while (t->next) {
            t = t->next;
        }
        t->next = (Node *)malloc(sizeof(Node));
         for (int i = 0; i < 7; i++) {
            t->next->value[i] = v[i];
        }
    }   
}


int main(int argc, char** argv){
    srand(time(NULL));
    char buff[100];
    //do {
    //    scanf("%s", buff);
    //} while (!validate_input(buff));
    char temp;

    HashMap *map = init_hash(1464, hash);

    for (int i = 0; i < 4; ++i) {
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
        append_hash(map, buff);
    }
    FILE *f = fopen("/home/danmax/code/saod/l4/data.csv", "w");
    for (int i = 0; i < 1464; i++) {
         fprintf(f, "%d,%d\n", i, map->data[i].num);
        }
    free_hash(map);
    return 0;   
}