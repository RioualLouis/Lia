/*! \file Network.c

   Contains everything related to the neural network.
*/

#include "Network.h"

#include <stdio.h>
#include <stdlib.h>

#include "Activation.h"

/*!
   \brief A first network implementation.
 */
void network_test() {
  printf("Sigmoid(1) = %.2f\n", sigmoid(1)); /* 0.73 */

  printf("Sigmoid(0) = %.2f\n", sigmoid(0)); /* 0.5 */
}
