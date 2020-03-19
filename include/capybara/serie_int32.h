#include "capybara/error.h"

typedef struct serie_int32 serie_int32_t;

/* serie_int32 operations */
typedef struct {
	const char 	*(*set_name)(serie_int32_t *, const char *);
	char 		*(*get_name)(serie_int32_t *);
	void		(*free_serie)(serie_int32_t *);
	cap_error_t	(*add)(serie_int32_t *, int32_t);
	size_t		(*size)(serie_int32_t *);
	int32_t		*(*get)(serie_int32_t *, size_t);
	int		(*set)(serie_int32_t *, size_t, int32_t);
	int		(*delete)(serie_int32_t *, size_t);
	int32_t		*(*min)(serie_int32_t *);
	int32_t		*(*max)(serie_int32_t *);
	double		(*mean)(serie_int32_t *);
	long double	(*sum)(serie_int32_t *);
	double		(*variance)(serie_int32_t *);
	double		(*std_dev)(serie_int32_t *);
} serie_int32_ops;

/* serie_int32 */
struct serie_int32 {
	serie_int32_ops *ops;
};

extern serie_int32_t		 *serie_int32_new(void);
