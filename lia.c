#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "colors.h"
#include "vector.h"
#include "network.h"

void display_banner() {
    printf("Lia V.0.0.0\n\n");

    printf("%sWelcome to %sLia\n", BOLD, RED);
    printf("%sA neural network built in C\n\n", DEFAULT);

    printf("Available options:\n");
    printf("-h : Displays help.\n");
}



int lia_main(int argc, char *argv[]) {

    srand(time(NULL));          /* Initialiser la génération de nombres aléatoires */

    display_banner();

    /* TESTING */
    printf("\n%s --- TESTING ---%s\n", BOLD, DEFAULT);

    network_test();

    return 0;
}
