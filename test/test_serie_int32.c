#include <string.h>
#include <stdio.h>

#include "unity.h"
#include "capybara/serie_int32.h"

void
setUp(void) {}

void
tearDown(void) {}

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

	TEST_ASSERT_NULL(s->ops->get_name(s));

	s->ops->set_name(s, "serie");

	TEST_ASSERT_NOT_NULL(s->ops->get_name(s));

	s->ops->free_serie(s);
}

void
test_get_name_serie_int32(void)
{
  	serie_int32_t *s = serie_int32_new();
	s->ops->set_name(s, "serie");

	TEST_ASSERT_EQUAL_STRING("serie", s->ops->get_name(s));
	TEST_ASSERT_EQUAL_STRING_LEN("serie", s->ops->get_name(s),
	strlen("serie"));
	s->ops->free_serie(s);
}

void
test_add_serie_int32(void)
{
  	serie_int32_t *s = serie_int32_new();

	s->ops->add(s, 1);

	TEST_ASSERT_EQUAL(1, s->ops->size(s));

	s->ops->free_serie(s);
}

void
test_get_serie_int32(void)
{
  	serie_int32_t *s = serie_int32_new();
	int32_t *num;

	s->ops->add(s, 1);
	num = s->ops->get(s, 0);
	TEST_ASSERT_EQUAL_INT32(1, *num);

	s->ops->free_serie(s);
}

void
test_set_serie_int32(void)
{
  	serie_int32_t *s = serie_int32_new();
	int32_t *num;

	s->ops->add(s, 1);
	s->ops->set(s, 0, 2);
	num = s->ops->get(s, 0);

	TEST_ASSERT_EQUAL(1, s->ops->size(s));
	TEST_ASSERT_EQUAL_INT32(2, *num);

	s->ops->free_serie(s);
}

void
test_delete_serie_int32(void)
{
  	serie_int32_t *s = serie_int32_new();
	int32_t *num;

	s->ops->add(s, 1);
	s->ops->delete(s, 0);
	TEST_ASSERT_EQUAL(0, s->ops->size(s));

	s->ops->free_serie(s);
}

void
test_min_serie_int32(void)
{
  	serie_int32_t *s = serie_int32_new();
	int32_t *min;

	s->ops->add(s, 5);
	s->ops->add(s, 2);
	s->ops->add(s, 1);
	s->ops->add(s, 4);

	min = s->ops->min(s);

	TEST_ASSERT_EQUAL_INT32(1, *min);

	s->ops->free_serie(s);
}

void
test_max_serie_int32(void)
{
  	serie_int32_t *s = serie_int32_new();
	int32_t *max;

	s->ops->add(s, 5);
	s->ops->add(s, 2);
	s->ops->add(s, 1);
	s->ops->add(s, 4);

	max = s->ops->max(s);

	TEST_ASSERT_EQUAL_INT32(5, *max);

	s->ops->free_serie(s);
}

void
test_mean_serie_int32(void)
{
  	serie_int32_t *s = serie_int32_new();
	long double mean = 0;

	s->ops->add(s, 5);
	s->ops->add(s, 2);
	s->ops->add(s, 1);
	s->ops->add(s, 4);

	mean = s->ops->mean(s);

	TEST_ASSERT_EQUAL_DOUBLE(3.0, mean);

	s->ops->free_serie(s);
}

int
main(void)
{
  	UNITY_BEGIN();

  	RUN_TEST(test_new_serie_int32);
  	RUN_TEST(test_set_name_serie_int32);
  	RUN_TEST(test_get_name_serie_int32);
  	RUN_TEST(test_add_serie_int32);
  	RUN_TEST(test_get_serie_int32);
  	RUN_TEST(test_set_serie_int32);
  	RUN_TEST(test_delete_serie_int32);
	RUN_TEST(test_min_serie_int32);
	RUN_TEST(test_max_serie_int32);
	RUN_TEST(test_mean_serie_int32);

  	return UNITY_END();
}
