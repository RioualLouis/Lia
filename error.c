#include <stdio.h>
#include <stdlib.h>

#include "colors.h"
#include "error.h"

void fatal_error(char* file, int line, char* causes) {
    /* À utiliser pour le développement */
    fprintf(stderr, "%s", RED);
    fprintf(stderr,"\n   /!\\ Fatal Error /!\\");
    fprintf(stderr,"%s", DEFAULT);
    fprintf(stderr,"   %s line %d\n\n", file, line);
    fprintf(stderr,"%s\n", causes);
    exit(1);
}

char* taberror[] = {
    "TYPE",
    "ARITY",
    "NAME",
    "DIVISION_BY_ZERO",
    "SYNTAXE",
    "RUNTIME"
};

void erreur(enum errors type, char* function, char* explanation) {
    /* À utiliser pour communiquer avec l'utilisateur. */
    printf("%s", RED);

    printf("Execution error [%s] : %s\n", taberror[type], explanation);
    printf("Guilty Fonction : « %s »", function);

    printf("%s", DEFAULT);
}
