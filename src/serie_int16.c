/*
 * Copyright (c) 2020 Murilo Ijanc' <msbd@m0x.ru>
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
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "capybara/serie_int16.h"
#include "capybara/utils.h"

#define SERIE ((struct serie_int16_impl *)s)
#define N(x) (sizeof(x) / sizeof(x[0]))

/* implementation */
struct serie_int16_impl {
	serie_int16_ops *ops;

	/* internal */
	char 	*name;
	int16_t *data;
	size_t 	size;
	size_t	capacity;
};

static const char 	*set_name(serie_int16_t *, const char *);
static char 	 	*get_name(serie_int16_t *);
static void 	 	 free_serie(serie_int16_t *);
static cap_error_t  	 resize(struct serie_int16_impl *);
static cap_error_t 	 add(serie_int16_t *, int16_t);
static size_t		 size(serie_int16_t *);
static int16_t		*get(serie_int16_t *, size_t);
static int		 set(serie_int16_t *, size_t, int16_t);
static int		 delete(serie_int16_t *, size_t);
static int16_t		*min(serie_int16_t *);
static int16_t		*max(serie_int16_t *);
static double	 	mean(serie_int16_t *);
static long double	 sum(serie_int16_t *);
static double	 	 variance(serie_int16_t *);
static double	 	 std_dev(serie_int16_t *);
static void		 sort(serie_int16_t *);
static int		 cmp(const void *, const void *);
static double	 	 median(serie_int16_t *);

static serie_int16_ops int16_ops = {
	set_name,
	get_name,
	free_serie,
	add,
	size,
	get,
	set,
	delete,
	min,
	max,
	mean,
	sum,
	variance,
	std_dev,
	sort,
	median,
};

static double
median(serie_int16_t *s)
{
	double median		= 0.0;
  	const size_t sz 	= size(s);
  	const size_t lhs 	= (sz - 1) / 2 ;
  	const size_t rhs 	= sz / 2 ;

	if (sz == 0)
		return 0.0;

	sort(s);

	if (lhs == rhs)
		median = (double)*get(s, lhs);
	else
		median = (double)((*get(s, lhs) + *get(s, rhs)) / 2.0);

	return median;
}

static void
sort(serie_int16_t *s)
{
	const size_t sz = size(s);
	const size_t szint = sizeof(int16_t);

	qsort(SERIE->data, sz, szint, cmp);
}

static int
cmp(const void *a, const void *b)
{
	const int16_t *ia = (const int16_t *)a;
	const int16_t *ib = (const int16_t *)b;

	return *ia - *ib;
}

static double
std_dev(serie_int16_t *s)
{
	const double vr		= variance(s);
	const double s_dev	= sqrt(vr);

	return s_dev;
}

static double
variance(serie_int16_t *s)
{
	size_t 			i;
	double 	variance 	= 0;
	const size_t sz 	= size(s);
	int16_t 		*x;
	long double delta	= 0;
	const double mn	= mean(s);

	if (sz == 0)
		return (0);

	for (i = 0; i < sz; i++) {
		x = get(s, i);
		delta = (long double)*x - mn;
		variance += (delta * delta - variance) / (i + 1);
	}

	return variance;
}

static long double
sum(serie_int16_t *s)
{
	size_t 		i;
	long double 	sum = 0;
	const size_t 	sz = size(s);
	int16_t 	*x;

	if (sz == 0)
		return (0);

	for (i = 0; i < sz; i++) {
		x = get(s, i);
		sum += (long double)*x;
	}

	return sum;
}

static double
mean(serie_int16_t *s)
{
	size_t 		i;
	double 	mean = 0;
	const size_t 	sz = size(s);
	int16_t 	*x;

	if (sz == 0)
		return (0);

	for (i = 0; i < sz; i++) {
		x = get(s, i);
		mean += ((double)*x - mean) / (i + 1);
	}

	return mean;
}

static int16_t *
max(serie_int16_t *s)
{
	size_t 		i;
	int16_t 	*max;
	int16_t		*x;
	const size_t  	sz = size(s);

	if (sz == 0)
		return (0);

	max = get(s, 0);

	for (i = 0; i < sz; i++) {
		x = get(s, i);
		if (*x > *max)
			max = x;
	}

	return max;
}

static int16_t *
min(serie_int16_t *s)
{
	size_t 		i;
	int16_t 	*min;
	int16_t		*x;
	const size_t  	sz = size(s);

	if (sz == 0)
		return (0);

	min = get(s, 0);

	for (i = 0; i < sz; i++) {
		x = get(s, i);
		if (*x < *min)
			min = x;
	}

	return min;
}

static int
delete(serie_int16_t *s, size_t index)
{
	memmove(&SERIE->data[index], &SERIE->data[index+1],
	    SERIE->size - index - 1);
	SERIE->size--;
	return (0);
}

static int
set(serie_int16_t *s, size_t index, int16_t v)
{
	SERIE->data[index] = v;
	return (0);
}

static int16_t *
get(serie_int16_t *s, size_t index)
{
	return &SERIE->data[index];
}

static size_t
size(serie_int16_t *s)
{
	return SERIE->size;
}

static cap_error_t
resize(struct serie_int16_impl *s)
{
	int16_t *data;
	size_t nsize; /* new size */

	nsize = SERIE->size * 2;

	/* first time size = 0 */
	if (nsize == 0)
		nsize = 4;

	/* TODO: check xrealloc return */
	data = xrealloc(SERIE->data, nsize + sizeof(int16_t));

	SERIE->data = data;
	SERIE->capacity = nsize;

	return (CAPY_ERROR_OK);
}

static cap_error_t
add(serie_int16_t *s, int16_t v)
{
	cap_error_t err;

	if (SERIE->size == SERIE->capacity)
		if ((err = resize(SERIE)) != CAPY_ERROR_OK) {
			free_serie(s);
			return err;
		}

	SERIE->data[SERIE->size++] = v;

	return (CAPY_ERROR_OK);
}

static void
free_serie(serie_int16_t *s)
{
	if (SERIE == NULL) return;
	if (SERIE->name != NULL)
		free(SERIE->name);
	if (SERIE->data != NULL)
		free(SERIE->data);
	free(SERIE);
}

static char *
get_name(serie_int16_t *s)
{
	return SERIE->name;
}

static const char *
set_name(serie_int16_t *s, const char *name)
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

serie_int16_t *
serie_int16_new(void)
{
	struct serie_int16_impl *s;

	s = xcalloc(1, sizeof(struct serie_int16_impl));

	s->ops = &int16_ops;

	return (serie_int16_t *)s;
}