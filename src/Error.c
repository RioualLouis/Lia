/*! \file Error.c

   Contains everything related to error handling and error messages.
*/

#include <stdio.h>
#include <stdlib.h>

#include "include/colors.h"
#include "include/error.h"

    /*!
       \brief Displays an error message and stops the program.

       \param file Name of the file where the error happened.
       \param line Line where the error happened.
       \param causes Explanation of the error.

       To use during development.
     */
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

    /*!
       \brief Displays an error message to the user.

       \param type Type of the error.
       \param function Name of the function that caused the error.
       \param explanation Explanation of the error.

       Unlike fatal_error(), the program does not stop.
     */
void erreur(enum errors type, char* function, char* explanation) {
    /* À utiliser pour communiquer avec l'utilisateur. */
    printf("%s", RED);

    printf("Execution error [%s] : %s\n", taberror[type], explanation);
    printf("Guilty Fonction : « %s »", function);

    printf("%s", DEFAULT);
}
