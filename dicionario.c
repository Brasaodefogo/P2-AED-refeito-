#include "dicionario.h"

int get_key(char pal){
    /* 0-25  alfatbeto | 26-35 algarismos*/
    if (isdigit(pal)) return ((pal - '0') % POSI_DIGITOS + TAMANHO_ALPHA);
    else return ((pal - 'a') % POSI_ALPHA);
}

LISTA* creates_nelem(char* pal1, char* pal2){
    /* Aloca memoria para vetor de estruturas do tipo PARES*/
    LISTA* nelem = (LISTA*) malloc(sizeof(LISTA));
    nelem->elem = (PARES*) malloc(sizeof(PARES));
    /* Verifica se a alocaçao de memoria foi bem sucedida*/
    if (nelem == NULL) {exit(1);}
    /* insere os dados*/
    nelem->elem->freq = 1;
    strncpy(nelem->elem->pal1, pal1, strlen(pal1));
    strncpy(nelem->elem->pal2, pal2, strlen(pal2));
    nelem->next = NULL;
    return nelem;
}

void find_n_insert_key(LISTA** hashtable, char* pal1, char* pal2, int key, int* obj_count){ /*recebe já com a posição*/
    LISTA* temp = hashtable[key];
    /* vai à posição 'key' da hash e verifica se a combinação já existe no dicionário*/
    /* caso não exista, que significa percorrer a lista toda daquela 'key', adiciona no final*/
    while (temp != NULL) {
        if (!strcmp(temp->elem->pal2, pal2) && !strcmp(temp->elem->pal1, pal1)){ /* existe combinação?*/
            temp->elem->freq += 1; /* se sim, incrementa frequência e termina função*/
            return;
        }
        if (temp->next == NULL) { /* não existe combinação*/
            temp->next = creates_nelem(pal1, pal2); /* adiciona nó à lista no final*/
            *obj_count+=1; /* incrementa número de nós criados*/
            return;
        }
        temp = temp->next;
    }
    /* se a lista na posição 'key' estiver vazia, ou seja, temp == NULL vai adicionar nó*/
    hashtable[key] = creates_nelem(pal1, pal2);
    *obj_count+=1; /* incrementa número de nós criados*/
}

void flatten (LISTA** hashtable, LISTA** flatted, int obj_count){
    int i, j = 0;
    LISTA* temp = NULL;
    /* transforma hashtable num array corrido de ponteiros*/
    for(i = 0; i<TAMANHO_DICIONARIO; i++){
        if(hashtable[i] != NULL) {
            flatted[j++] = hashtable[i]; /* obtém a cabeça de cada hash e guarda*/
            temp = hashtable[i]->next; /* usado para percorrer a hash*/
            while(temp != NULL) { /* copia todos os nós para o array*/
                flatted[j++] = temp;
                temp = temp->next;
            }
        }
    }
}

void print_seq(FILE* fw, LISTA** flatted_hash, int obj_count, int seq){
    LISTA* temp = NULL;
    int i;
    for (i = 0 ; i < obj_count ; i++){
        temp = flatted_hash[i];
        if (i<seq) fprintf(fw, "%d - %d %s %s\n", (i+1), temp->elem->freq, temp->elem->pal1 , temp->elem->pal2);
        free(temp->elem);
        free(temp);
    }
}
/* Function to merge two subarrays of LISTA**/
void merge(LISTA** array, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int i, j, k;
    /* Temporary arrays*/
    LISTA** leftArr = (LISTA**)malloc(n1 * sizeof(LISTA*));
    LISTA** rightArr = (LISTA**)malloc(n2 * sizeof(LISTA*));

    /* Copy data to temporary arrays*/
    for (i = 0; i < n1; i++)
        leftArr[i] = array[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = array[mid + 1 + j];

    /* Merge the temporary arrays back into array[left..right]*/
    i = 0; j = 0; k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i]->elem->freq >= rightArr[j]->elem->freq) { /* Descending order*/
            array[k] = leftArr[i];
            i++;
        } else {
            array[k] = rightArr[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of leftArr[], if any*/
    while (i < n1) {
        array[k] = leftArr[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of rightArr[], if any*/
    while (j < n2) {
        array[k] = rightArr[j];
        j++;
        k++;
    }

    /* Free temporary arrays*/
    free(leftArr);
    free(rightArr);
}

/* Merge sort function*/
void mergeSort(LISTA** array, int left, int right) {
    int mid;
    if (left < right) {
        mid = left + (right - left) / 2;

        /* Sort first and second halves*/
        mergeSort(array, left, mid);
        mergeSort(array, mid + 1, right);

        /* Merge the sorted halves*/
        merge(array, left, mid, right);
    }
}

