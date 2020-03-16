#include "unity.h"

#include "capybara/serie_int32.h"

void test_new_serie_int32(void) {
  	serie_int32_t *s = serie_int32_new();

	TEST_ASSERT_NOT_NULL(s);

	s->ops->free_serie(s);
}

void setUp (void) {}
void tearDown (void) {}

int main() {
  	UNITY_BEGIN();
  	RUN_TEST(test_new_serie_int32);
  	return UNITY_END();
}
