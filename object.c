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

#include <stdio.h>
#include <err.h>
#include <stdlib.h>

#include "capybara.h"

static void obj_set_size(Object *);
static void obj_set_value(Object *, void *);

static void
obj_set_value(Object *o, void *v)
{
	switch (o->type) {
		case CHAR:
			o->char_data = (char *)v;
			break;
		case DOUBLE:
			o->double_data = (double *)v;
			break;
		case FLOAT:
			o->float_data = (float *)v;
			break;
		case INT:
			o->int_data = (int *)v;
			break;
		default:
			err(1, "failed calculate size, invalid type");
	}
}

Object *
new_obj(enum obj_type t, void *v)
{
	Object *o;

	o = (Object *)malloc(sizeof(Object));

	if (o == NULL)
		err(1, "failed alloc object");

	o->type = t;
	obj_set_size(o); // bytes
	obj_set_value(o, v);

	return o;
}

static void
obj_set_size(Object *o)
{
	switch (o->type) {
		case CHAR:
			o->size = sizeof(char);
			break;
		case DOUBLE:
			o->size = sizeof(double);
			break;
		case FLOAT:
			o->size = sizeof(float);
			break;
		case INT:
			o->size = sizeof(int);
			break;
		default:
			err(1, "failed calculate size, invalid type");
	}
}

void
obj_free(Object *o)
{
	if (o == NULL) return;
	free(o);
}
