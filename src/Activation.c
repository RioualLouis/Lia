/*! \file Activation.c

   Contains the activation functions of the network.
*/

#include <stdio.h>
#include <math.h>

#include "include/activation.h"

    /*!
       \brief Computes the sigmoid of a value.

       \param x Input value.

       \return The result of 1 / (1 + exp(-x)), between 0 and 1.
     */
double sigmoid(double x) {
    double power;
    double expo;

    power = -1 * x;
    expo = exp(power);

    return 1 / (1 + expo);
}
