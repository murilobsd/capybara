typedef enum capybara_error_e {
	// No error
	CAPY_ERROR_OK = 0,

	// Out of memomry
	CAPY_ERROR_NOMEM
} capybara_error_t;

const char *CAPY_ERROR_STRS[] = {
	"CAPY_ERROR_OK",
	"CAPY_ERROR_NOMEM",
};
