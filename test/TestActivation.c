#include "Activation.h"
#include "unity.h"

void setUp() {}     // Usage inconnue
void tearDown() {}  // Usage inconnue

void test_sigmoid_true(void) { TEST_ASSERT_EQUAL_FLOAT(0.5, sigmoid(0.)); }

int main(void) {
  // Fonction de déroulement des tests
  UNITY_BEGIN();  // Début des tests
  RUN_TEST(test_sigmoid_true);
  return UNITY_END();  // Fin des tests, retourne autre chose que 0 si les tests
                       // ne passent pas.
}
