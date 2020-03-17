#include <string.h>

#include "unity.h"
#include "capybara/error.h"

void
setUp(void) {}

void
tearDown(void) {}

cap_error_t
func_return_error_ok(void)
{
	return CAPY_ERROR_OK;
}

cap_error_t
func_return_error_nomem(void)
{
	return CAPY_ERROR_NOMEM;
}

void
test_error_ok(void)
{
	TEST_ASSERT_EQUAL(CAPY_ERROR_OK, func_return_error_ok());
}

void
test_error_nomem(void)
{
	TEST_ASSERT_EQUAL(CAPY_ERROR_NOMEM, func_return_error_nomem());
}

void
test_error_ok_str(void)
{
	cap_error_t err;

	err = func_return_error_ok();

	TEST_ASSERT_EQUAL_STRING("CAPY_ERROR_OK", capy_error_str(err));
	TEST_ASSERT_EQUAL_STRING_LEN("CAPY_ERROR_OK", capy_error_str(err),
		strlen("CAPY_ERROR_OK"));
}

void
test_error_nomem_str(void)
{
	cap_error_t err;

	err = func_return_error_nomem();

	TEST_ASSERT_EQUAL_STRING("CAPY_ERROR_NOMEM", capy_error_str(err));
	TEST_ASSERT_EQUAL_STRING_LEN("CAPY_ERROR_NOMEM", capy_error_str(err),
		strlen("CAPY_ERROR_NOMEM"));
}

int
main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_error_ok);
	RUN_TEST(test_error_nomem);
	RUN_TEST(test_error_ok_str);

	return UNITY_END();
}
