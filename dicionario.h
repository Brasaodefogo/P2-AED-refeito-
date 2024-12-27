#ifndef DICIONARIO_H_
#define DICIONARIO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAMANHO_MAX_PALAVRA 100 /* utilizado para definir limite da string*/
#define TAMANHO_DICIONARIO 36 /* alfabeto + algarismos*/
#define POSI_DIGITOS 48 /* posição código ASCII do  '0'*/
#define POSI_ALPHA 97 /* posição código ASCII do 'a'*/
#define TAMANHO_ALPHA 26 /* usado para colocar os algarismos a partir da posilão 26*/
#endif

/* estrutura combinação*/
typedef struct pares{
    int freq;
    char pal1[TAMANHO_MAX_PALAVRA];
    char pal2[TAMANHO_MAX_PALAVRA];
}PARES;
/* nós da lista*/
typedef struct lista{
    PARES* elem;
    struct lista* next;
}LISTA;

/* recebe a primeira letra da palavra/algarismo e retorna a chave de acesso à hashtable*/
int get_key(char pal);
/* cria nó e preenche e retorna nó*/
LISTA* creates_nelem(char* pal1, char* pal2);
/* pesquisa a combinação na hashtable na posição da 'key' e toma a decisão se incrementa a freq ou adiciona à hash*/
void find_n_insert_key(LISTA** hastable, char* pal1, char* pal2, int key, int* obj_count);
/* transforma hashtable em array*/
void flatten (LISTA** hashtable, LISTA** flatted, int obj_count);
/* algoritmo de ordenação*/
void merge(LISTA** array, int left, int mid, int right) ;
void mergeSort(LISTA** array, int left, int right) ;
void print_seq(FILE* fw, LISTA** hashtable, int obj_count, int seq);