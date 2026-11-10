/*! \file Activation.c

   Contains the activation functions of the network.
*/

#include "Activation.h"

#include <math.h>

/*!
   \brief Computes the sigmoid of a value.

   \param x Input value.

   \return The result of 1 / (1 + exp(-x)), between 0 and 1.
 */
double sigmoid(double x) { return 1 / (1 + exp(-1 * x)); }
