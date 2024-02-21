#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers\analyse_lexical.h"
#include "headers\analyse_syntaxique.h"
#include "headers\analyse_semantique.h"

int main(){
    char filename[20];
    printf("Choose a file :\n1)test1\n2)test2\n3)test3\nWrite the name of the file : ");
    scanf("%s", filename);

    char filepath[30] = "test\\";
    strcat(filepath, filename);
    strcat(filepath, ".p");

    opn_file(filepath);
    lexical();
    syntaxique();
	semantique();
    fclose(file);
    return 0;
}