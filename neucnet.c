#include <stdio.h>

#include "colors.h"

void display_banner() {
    printf("NeuCNet V.0.0.0\n\n");

    printf("%sWelcome to %sNeuCNet\n", BOLD, CYAN);
    printf("%sA neural network built in C\n\n", DEFAULT);

    printf("Available options:\n");
    printf("-h : Displays help.\n");
}

int neucnet_main(int argc, char *argv[]) {

    display_banner();

    return 0;
}
