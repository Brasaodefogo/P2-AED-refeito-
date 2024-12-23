#include "dicionario.h"

int get_key(char pal){
    if (isdigit(pal)) return ((pal - '0') % POSI_DIGITOS + TAMANHO_ALPHA);
    else return ((pal - 'a') % POSI_ALPHA);
}

LISTA* creates_nelem(char* pal1, char* pal2){
    /* Aloca memoria para vetor de estruturas do tipo PARES*/
    LISTA* nelem = (LISTA*) malloc(sizeof(LISTA));
    nelem->elem = (PARES*) malloc(sizeof(PARES));
    /* Verifica se a alocaçao de memoria foi bem sucedida*/
    if (nelem == NULL) {
        fprintf(stderr, "Erro na alocação de memória\n");
        exit(1);
    }
    /* insere os dados*/
    (nelem)->elem->freq = 1;
    strncpy((nelem)->elem->pal1, pal1, strlen(pal1));
    strncpy((nelem)->elem->pal2, pal2, strlen(pal2));
    (nelem)->next = NULL;
    return nelem;
}

void find_n_insert_key(LISTA** hashtable, char* pal1, char* pal2, int key){ /*recebe já com a posição*/
    LISTA* temp = hashtable[key];
    
    /* se a lista não estiver vazi faz while*/
    while (temp != NULL) {
        if (!strcmp(temp->elem->pal2, pal2) && !strcmp(temp->elem->pal1, pal1)){
            temp->elem->freq += 1;
            return;
        }
        if (temp->next == NULL) {
            temp->next = creates_nelem(pal1, pal2); 
            return;
        }
        temp = temp->next;
    }
    /* se a lista estiver vazia */
    hashtable[key] = creates_nelem(pal1, pal2);
}

void print_list(LISTA** hashtable){
    LISTA* temp;
    int i;
    for (i = 0 ; i < TAMANHO_DICIONARIO; i++){
        printf("|||||%d|||||\n", i);
        temp = hashtable[i];
        for (; temp != NULL; temp = temp->next) printf("%d - %s %s\n", temp->elem->freq, temp->elem->pal1 , temp->elem->pal2);
    }
}

