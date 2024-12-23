
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dicionario.h"

int main(int argc, char** argv){
    printf("%d\n", get_key(argv[1][0]));
    return 0;
}
