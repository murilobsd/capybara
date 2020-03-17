#include <string.h>

#include "unity.h"
#include "capybara/error.h"

void
setUp(void) {}

void
tearDown(void) {}

capybara_error_t
func_return_no_error(void)
{
	return CAPY_ERROR_OK;
}

void
test_error_ok(void)
{
	TEST_ASSERT_EQUAL(CAPY_ERROR_OK, func_return_no_error());
}

int
main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_error_ok);
	return UNITY_END();
}
