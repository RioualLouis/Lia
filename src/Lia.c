/*! \file Lia.c

   Contains the main logic of Lia (banner, options, tests).
*/

#include "Lia.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Colors.h"
#include "Matrix.h"
#include "Network.h"

/*!
   \brief Displays the version, the welcome message.
 */
static void display_banner() {
  printf("Lia V.0.0.0\n\n");

  printf("%sWelcome to %sLia\n", BOLD, RED);
  printf("%sA neural network built in C\n\n", DEFAULT);
}

/*!
  \brief Displays correct usage and help access.
*/
static void display_no_args() {
  printf("Usage : %slia [-OPTIONS]\n", BOLD);
  printf("%sUse option -h to display help.\n", DEFAULT);
}

/*!
   \brief Main function of Lia, called by main().

   \param argc Number of command line arguments.
   \param argv Array of command line arguments.

   \return 0 if the program ends normally.

   Displays different views according to the arguments input with the fonction in command line.
 */
int lia_main(int argc, char *argv[]) {
  srand(time(NULL)); /* Initialiser la génération de nombres aléatoires */

  display_banner();

  switch (argc) {
  case 1 :
      display_no_args();
      break;
  case 2 :
      if (strcmp(argv[1], "-h") == 0) printf("Help Required T-T\n");
      break;
  default :
      printf("Placeholder\n");
      break;
  }

  return 0;
}
