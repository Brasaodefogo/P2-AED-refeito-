#include "dicionario.h"

int main(int argc, char** argv){
    int seq = 0, dim = 0, obj_count = 0, i;
    int lenght_argv1 = 0;
    char pal1[TAMANHO_MAX_PALAVRA] = "\0", pal2[TAMANHO_MAX_PALAVRA] = "\0";
    char* ficheiro = NULL;
    FILE* fr = NULL, *fw = NULL;
    LISTA **hashtable = (LISTA**) calloc(TAMANHO_DICIONARIO, sizeof(LISTA*));
    if (hashtable== (LISTA**) NULL){exit(1);}
   
     /* abertura de ficheiros*/
    lenght_argv1 = (strlen(argv[1])+1); /* obtém o tamanho do ficheiro de entrada*/
    ficheiro = (char*) malloc (lenght_argv1); /* aloca memória para a string que contém o nome do ficheiro*/
    if (ficheiro == (char*) NULL){exit(1);}
    strncpy(ficheiro, argv[1], (lenght_argv1-4)); /* copiar para 'ficheiro' caracteres ate ao "."*/
    strcat(ficheiro, "sol"); /* adiciona ao fim da string "sol"*/

    fr = fopen(argv[1], "r");
    if (fr== (FILE*) NULL){exit(1);}

    fw = fopen(ficheiro, "w"); 
    if (fw == (FILE*) NULL){exit(1);}

    /* leitura de ficheiros*/
    fscanf(fr, "%d %d\n", &seq, &dim ); /* lê os primeiros dados e faz com que a próxima interacão comece a ler logo o ficheiro*/
    while(fscanf(fr, "%s", pal2) != -1){
        for(i=0;pal2[i]!='\0';i++){
            pal2[i] = tolower(pal2[i]); /* converte maiúsculas para minúsculas*/
        }
        if (pal1[0] == '\0') { /* início*/
            strncpy(pal1, pal2, strlen(pal2)); /* copia a palavra lida para o campo respetivo*/
            continue; /* avança para a próxima leitura*/
        }
        
        find_n_insert_key(hashtable, pal1, pal2, get_key(pal1[0]), &obj_count);
        strncpy(pal1, "", strlen(pal1)); /* limpa a string que contém a primeira palavra*/
        strncpy(pal1, pal2, strlen(pal2)); /* copia a palavra 2 para a palavra 1, para analisar o próximo para no ciclo seguinte*/
    }
    LISTA** flatted_hash = (LISTA**) malloc((sizeof(LISTA*))*obj_count); /* array de ponteiros*/
    if (flatted_hash == (LISTA**) NULL){ exit(1);}
    flatten(hashtable, flatted_hash, obj_count);
    mergeSort(flatted_hash, 0, obj_count-1); 
    print_seq(fw, flatted_hash, obj_count, seq);
    
    free(hashtable);
    free(flatted_hash);
    free(ficheiro);
    fclose(fr);
    fclose(fw);
    return 0;
}