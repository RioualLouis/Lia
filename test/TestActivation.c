#include "vendor/Unity/src/unity.h"
#include "../activation.h" // À changer, inclure le chemin dans la compilation, a priori avec -I puis le chemin vers les includes

void setUp() {} // Usage inconnue
void tearDown() {} // Usage inconnue

void test_sigmoid_true(void) {
    TEST_ASSERT_EQUAL_FLOAT(0.5, sigmoid(0.));
}

void test_sigmoid_false(void) {
    TEST_ASSERT_EQUAL_FLOAT(-1., sigmoid(0.));
}

int main(void) {
    // Fonction de déroulement des tests
    UNITY_BEGIN(); // Début des tests
    RUN_TEST(test_sigmoid_true);
    RUN_TEST(test_sigmoid_false);
    return UNITY_END(); // Fin des tests, retourne autre chose que 0 si les tests ne passent pas.
}
