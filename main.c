/*
 * Copyright (c) 2019 Murilo Ijanc' <mbsd@m0x.ru>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct serie_int32 serie_int32_t;

/* serie_int32 operations */
typedef struct {
	const char 	*(*set_name)(serie_int32_t *, const char *);
	char 		*(*get_name)(serie_int32_t *);
} serie_int32_ops;

/* serie_int32 */
struct serie_int32 {
	serie_int32_ops *ops;
};

/* implementation */
struct serie_int32_impl {
	serie_int32_ops *ops;
	char *name;
};

serie_int32_t		 *serie_int32_new(void);
static const char 	 *set_name(serie_int32_t *, const char *);
static char 	 	 *get_name(serie_int32_t *);

static serie_int32_ops int32_ops = {
	set_name,
	get_name,
};

int
main(int argc, char *argv[])
{
	serie_int32_t *s1 = serie_int32_new();
	s1->ops->set_name(s1, "serie 1");

	printf("Serie name: %s\n", s1->ops->get_name(s1));

	free(s1);

	return (0);
}

static char *
get_name(serie_int32_t *s)
{
	return (struct serie_int32_impl *)s->name;
}

static const char *
set_name(serie_int32_t *s, const char *name)
{
	char *n;

	if (name == NULL) {
		(struct serie_int32_impl *)s->name = NULL;
		return NULL;
	}

	n = strdup(name);
	if (n == NULL)
		err(1, NULL);

	(struct serie_int32_impl *)s->name = n;
	return NULL;
}

serie_int32_t *
serie_int32_new(void)
{
	struct serie_int32_impl *s;

	if ((s = calloc(1, sizeof(struct serie_int32_impl))) == NULL)
		err(1, "failed alloc serie");

	s->ops = &int32_ops;

	return (serie_int32_t *)s;
}
