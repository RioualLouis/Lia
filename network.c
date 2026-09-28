#include <stdio.h>

#include "activation.h"

void network_test() {
    printf("Sigmoid(1) = %.2f\n", sigmoid(1)); /* 0.73 */

    printf("Sigmoid(0) = %.2f\n", sigmoid(0)); /* 0.5 */
}
