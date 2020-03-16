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

/*
 *   @file serie_int32.c
 *   @brief This source contains serie int32 functions.
 *
 *   @author Murilo Ijanc'
 *   @date 04/19/2018
 */

#include <err.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "capybara/serie_int32.h"
#include "capybara/utils.h"

#define SERIE ((struct serie_int32_impl *)s)

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
static const char 	 *set_name(serie_int32_t *, const char *);
static char 	 	 *get_name(serie_int32_t *);
static void 	 	 free_serie(serie_int32_t *);
static int 	 	 resize(struct serie_int32_impl *);
static int 	 	 add(serie_int32_t *, int32_t);
static size_t		 size(serie_int32_t *);
static int32_t		 *get(serie_int32_t *, size_t);
static int		 set(serie_int32_t *, size_t, int32_t);
static int		 delete(serie_int32_t *, size_t);


static serie_int32_ops int32_ops = {
	set_name,
	get_name,
	free_serie,
	add,
	size,
	get,
	set,
	delete,
};

static int
delete(serie_int32_t *s, size_t index)
{
	memmove(&SERIE->data[index], &SERIE->data[index+1],
	    SERIE->size - index - 1);
	SERIE->size--;
	return (0);
}

static int
set(serie_int32_t *s, size_t index, int32_t v)
{
	SERIE->data[index] = v;
	return (0);
}

static int32_t *
get(serie_int32_t *s, size_t index)
{
	return &SERIE->data[index];
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