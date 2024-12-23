#ifndef DICIONARIO_H_
#define DICIONARIO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAMANHO_MAX_PALAVRA 100 /* utilizado na main para contruir a string*/
#define TAMANHO_DICIONARIO 36
#define POSI_DIGITOS 48
#define POSI_ALPHA 97
#define TAMANHO_ALPHA 26
#endif


typedef struct pares{
    int freq;
    char pal1[TAMANHO_MAX_PALAVRA];
    char pal2[TAMANHO_MAX_PALAVRA];
}PARES;

typedef struct lista{
    PARES* elem;
    struct lista* next;
}LISTA;

int get_key(char pal);
LISTA* creates_nelem(char* pal1, char* pal2);
void find_n_insert_key(LISTA** hastable, char* pal1, char* pal2, int key);
void print_list(LISTA** hashtable);