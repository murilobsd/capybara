#include <stdio.h>

#include "capybara/error.h"

static const char *CAPY_ERROR_STRS[] = {
	"CAPY_ERROR_OK",
	"CAPY_ERROR_NOMEM",
};


const char *
capy_error_str(cap_error_t err)
{
	const char *err_str = NULL;

	if (err >= sizeof(CAPY_ERROR_STRS))
		return NULL;
	err_str = CAPY_ERROR_STRS[err];

	return err_str;
}
