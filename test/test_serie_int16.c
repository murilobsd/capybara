#include <string.h>
#include <stdio.h>

#include "unity.h"
#include "capybara/serie_int16.h"

void
setUp(void) {}

void
tearDown(void) {}

void
test_new_serie_int16(void)
{
  	serie_int16_t *s = serie_int16_new();

	TEST_ASSERT_NOT_NULL(s);

	s->ops->free_serie(s);
}

void
test_set_name_serie_int16(void)
{
  	serie_int16_t *s = serie_int16_new();

	TEST_ASSERT_NULL(s->ops->get_name(s));

	s->ops->set_name(s, "serie");

	TEST_ASSERT_NOT_NULL(s->ops->get_name(s));

	s->ops->free_serie(s);
}

void
test_get_name_serie_int16(void)
{
  	serie_int16_t *s = serie_int16_new();
	s->ops->set_name(s, "serie");

	TEST_ASSERT_EQUAL_STRING("serie", s->ops->get_name(s));
	TEST_ASSERT_EQUAL_STRING_LEN("serie", s->ops->get_name(s),
	    strlen("serie"));
	s->ops->free_serie(s);
}

void
test_add_serie_int16(void)
{
  	serie_int16_t *s = serie_int16_new();

	s->ops->add(s, 1);

	TEST_ASSERT_EQUAL(1, s->ops->size(s));

	s->ops->free_serie(s);
}

void
test_get_serie_int16(void)
{
  	serie_int16_t *s = serie_int16_new();
	int16_t *num;

	s->ops->add(s, 1);
	num = s->ops->get(s, 0);
	TEST_ASSERT_EQUAL_INT16(1, *num);

	s->ops->free_serie(s);
}

void
test_set_serie_int16(void)
{
  	serie_int16_t *s = serie_int16_new();
	int16_t *num;

	s->ops->add(s, 1);
	s->ops->set(s, 0, 2);
	num = s->ops->get(s, 0);

	TEST_ASSERT_EQUAL(1, s->ops->size(s));
	TEST_ASSERT_EQUAL_INT16(2, *num);

	s->ops->free_serie(s);
}

void
test_delete_serie_int16(void)
{
  	serie_int16_t *s = serie_int16_new();
	int16_t *num;

	s->ops->add(s, 1);
	s->ops->delete(s, 0);
	TEST_ASSERT_EQUAL(0, s->ops->size(s));

	s->ops->free_serie(s);
}

void
test_min_serie_int16(void)
{
  	serie_int16_t *s = serie_int16_new();
	int16_t *min;

	s->ops->add(s, 5);
	s->ops->add(s, 2);
	s->ops->add(s, 1);
	s->ops->add(s, 4);

	min = s->ops->min(s);

	TEST_ASSERT_EQUAL_INT16(1, *min);

	s->ops->free_serie(s);
}

void
test_max_serie_int16(void)
{
  	serie_int16_t *s = serie_int16_new();
	int16_t *max;

	s->ops->add(s, 5);
	s->ops->add(s, 2);
	s->ops->add(s, 1);
	s->ops->add(s, 4);

	max = s->ops->max(s);

	TEST_ASSERT_EQUAL_INT16(5, *max);

	s->ops->free_serie(s);
}

void
test_mean_serie_int16(void)
{
  	serie_int16_t *s = serie_int16_new();
	long double mean = 0;

	s->ops->add(s, 5);
	s->ops->add(s, 2);
	s->ops->add(s, 1);
	s->ops->add(s, 4);

	mean = s->ops->mean(s);

	TEST_ASSERT_EQUAL_DOUBLE(3.0, mean);

	s->ops->free_serie(s);
}

void
test_sum_serie_int16(void)
{
  	serie_int16_t *s = serie_int16_new();
	long double sum = 0;

	s->ops->add(s, 5);
	s->ops->add(s, 2);
	s->ops->add(s, 1);
	s->ops->add(s, 4);

	sum = s->ops->sum(s);

	TEST_ASSERT_EQUAL_DOUBLE(12.0, sum);

	s->ops->free_serie(s);
}

void
test_variance_serie_int16(void)
{
  	serie_int16_t *s = serie_int16_new();
	double variance = 0;

	s->ops->add(s, 5);
	s->ops->add(s, 2);
	s->ops->add(s, 1);
	s->ops->add(s, 4);

	variance = s->ops->variance(s);

	TEST_ASSERT_EQUAL_DOUBLE(2.5, variance);

	s->ops->free_serie(s);
}

void
test_sd_dev_serie_int16(void)
{
  	serie_int16_t *s = serie_int16_new();
	double std_dev = 0;

	s->ops->add(s, 5);
	s->ops->add(s, 2);
	s->ops->add(s, 1);
	s->ops->add(s, 4);

	std_dev = s->ops->std_dev(s);

	TEST_ASSERT_EQUAL_DOUBLE(1.581, std_dev);

	s->ops->free_serie(s);
}

void
test_sort_serie_int16(void)
{
  	serie_int16_t *s = serie_int16_new();

	s->ops->add(s, 5);
	s->ops->add(s, 2);
	s->ops->add(s, 1);
	s->ops->add(s, 4);

	s->ops->sort(s);

	TEST_ASSERT_EQUAL(1, *s->ops->get(s, 0));
	TEST_ASSERT_EQUAL(5, *s->ops->get(s, 3));

	s->ops->free_serie(s);
}

void
test_median_serie_int16(void)
{
  	serie_int16_t *s = serie_int16_new();
	double median = 0;

	s->ops->add(s, 5);
	s->ops->add(s, 2);
	s->ops->add(s, 1);
	s->ops->add(s, 4);

	median = s->ops->median(s);

	TEST_ASSERT_EQUAL_DOUBLE(3.0, median);

	s->ops->free_serie(s);
}




int
main(void)
{
  	UNITY_BEGIN();

  	RUN_TEST(test_new_serie_int16);
  	RUN_TEST(test_set_name_serie_int16);
  	RUN_TEST(test_get_name_serie_int16);
  	RUN_TEST(test_add_serie_int16);
  	RUN_TEST(test_get_serie_int16);
  	RUN_TEST(test_set_serie_int16);
  	RUN_TEST(test_delete_serie_int16);
	RUN_TEST(test_min_serie_int16);
	RUN_TEST(test_max_serie_int16);
	RUN_TEST(test_mean_serie_int16);
	RUN_TEST(test_sum_serie_int16);
	RUN_TEST(test_variance_serie_int16);
	RUN_TEST(test_sd_dev_serie_int16);
	RUN_TEST(test_sort_serie_int16);
	RUN_TEST(test_median_serie_int16);

  	return UNITY_END();
}