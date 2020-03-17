#include <string.h>

#include "unity.h"
#include "capybara/serie_int32.h"

void setUp (void) {}
void tearDown (void) {}

void
test_new_serie_int32(void)
{
  	serie_int32_t *s = serie_int32_new();

	TEST_ASSERT_NOT_NULL(s);

	s->ops->free_serie(s);
}

void
test_set_name_serie_int32(void)
{
  	serie_int32_t *s = serie_int32_new();
	s->ops->set_name(s, "serie");

	TEST_ASSERT_EQUAL_STRING("serie", s->ops->get_name(s));
	TEST_ASSERT_EQUAL_STRING_LEN("serie", s->ops->get_name(s),
	strlen("serie"));
	s->ops->free_serie(s);
}

int main() {
  	UNITY_BEGIN();
  	RUN_TEST(test_new_serie_int32);
  	RUN_TEST(test_set_name_serie_int32);
  	return UNITY_END();
}
