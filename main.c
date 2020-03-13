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
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define SERIE ((struct serie_int32_impl *)s)

typedef struct serie_int32 serie_int32_t;

/* serie_int32 operations */
typedef struct {
	const char 	*(*set_name)(serie_int32_t *, const char *);
	char 		*(*get_name)(serie_int32_t *);
	void		(*free_serie)(serie_int32_t *);
	int		(*add)(serie_int32_t *, int32_t);
	size_t		(*size)(serie_int32_t *);
} serie_int32_ops;

/* serie_int32 */
struct serie_int32 {
	serie_int32_ops *ops;
};

/* implementation */
struct serie_int32_impl {
	serie_int32_ops *ops;

	/* internal */
	char 	*name;
	int32_t *data;
	size_t 	size;
	size_t	capacity;
};

/* series functions */
serie_int32_t		 *serie_int32_new(void);
static const char 	 *set_name(serie_int32_t *, const char *);
static char 	 	 *get_name(serie_int32_t *);
static void 	 	 free_serie(serie_int32_t *);
static int 	 	 resize(struct serie_int32_impl *);
static int 	 	 add(serie_int32_t *, int32_t);
static size_t		 size(serie_int32_t *);

/* utils */
static char 		 *xstrdup(const char *);
static void		 *xcalloc(size_t , size_t);
static void		 *xrealloc(void *, size_t);

static serie_int32_ops int32_ops = {
	set_name,
	get_name,
	free_serie,
	add,
	size,
};

int
main(int argc, char *argv[])
{
	serie_int32_t *s1 = serie_int32_new();
	s1->ops->set_name(s1, "serie 1");

	printf("Serie name: %s\n", s1->ops->get_name(s1));

	printf("Serie Size: %lu\n", s1->ops->size(s1));

	s1->ops->add(s1, 1);
	printf("Add value 1 to serie\n");
	printf("Serie Size: %lu\n", s1->ops->size(s1));

	s1->ops->free_serie(s1);
	printf("Free serie\n");

	return (0);
}

static size_t
size(serie_int32_t *s)
{
	return SERIE->size;
}

static int
resize(struct serie_int32_impl *s)
{
	int32_t *data;
	size_t nsize; /* new size */

	nsize = SERIE->size * 2;

	// first time size = 0
	if (nsize == 0)
		nsize = 4;

	data = xrealloc(SERIE->data, nsize + sizeof(int32_t));

	SERIE->data = data;
	SERIE->capacity = nsize;

	return 0;
}

static int
add(serie_int32_t *s, int32_t v)
{
	if (SERIE->size == SERIE->capacity)
		resize(SERIE);

	SERIE->data[SERIE->size++] = v;

	return 0;
}

static void
free_serie(serie_int32_t *s)
{
	if (SERIE == NULL) return;
	if (SERIE->name != NULL)
		free(SERIE->name);
	if (SERIE->data != NULL)
		free(SERIE->data);
	free(SERIE);
}

static char *
get_name(serie_int32_t *s)
{
	return SERIE->name;
}

static const char *
set_name(serie_int32_t *s, const char *name)
{
	char *n;

	if (name == NULL) {
		SERIE->name = NULL;
		return NULL;
	}

	n = xstrdup(name);

	SERIE->name = n;
	return NULL;
}

serie_int32_t *
serie_int32_new(void)
{
	struct serie_int32_impl *s;

	s = xcalloc(1, sizeof(struct serie_int32_impl));

	s->ops = &int32_ops;

	return (serie_int32_t *)s;
}

void *
xcalloc(size_t nmemb, size_t size)
{
	void *p;

	if (size == 0 || nmemb == 0)
		errx(1, "xcalloc: zero size");

	if ((p = calloc(nmemb, size)) == NULL)
		err(1, NULL);

	return (p);
}

static char *
xstrdup(const char *s)
{
	char *ss;

	if ((ss = strdup(s)) == NULL)
		err(1, NULL);

	return (ss);
}

void *
xrealloc(void *ptr, size_t size)
{
	if ((ptr = realloc(ptr, size)) == NULL)
		err(1, NULL);

	return (ptr);
}
