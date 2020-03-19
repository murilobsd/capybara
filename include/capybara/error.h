typedef enum capybara_error_e {
	/* No error */
	CAPY_ERROR_OK = 0,

	/* Out of memomry */
	CAPY_ERROR_NOMEM
} cap_error_t;

extern const char	*capy_error_str(cap_error_t);
