#include <stdio.h>

#include "capybara/error.h"

const char *
capy_error_str(capybara_error_t err)
{
	const char *err_str = NULL;

	if (err >= sizeof(CAPY_ERROR_STRS))
		return NULL;
	err_str = CAPY_ERROR_STRS[err];

	return err_str;
}
