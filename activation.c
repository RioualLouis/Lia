#include <stdio.h>
#include <math.h>

#include "activation.h"

double sigmoid(double x) {
    double power;
    double expo;

    power = -1 * x;
    expo = exp(power);

    return 1 / (1 + expo);
}
