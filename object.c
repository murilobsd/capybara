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

Object *
new_obj(enum obj_type t, const size_t num)
{
	Object *o;

	o = (Object *)malloc(sizeof(Object));

	if (o == NULL)
		err(1, "failed alloc object");

	o->type = t;
	o->size = num;
	switch (t) {
		case CHAR:
			o->char_data = (char *)malloc(sizeof(char) * num);
			break;
		case DOUBLE:
			o->double_data = (double *)malloc(sizeof(double) * num);
			break;
		case FLOAT:
			o->float_data = (float *)malloc(sizeof(float) * num);
			break;
		case INT:
			o->int_data = (int *)malloc(sizeof(int) * num);
			break;
		default:
			o->double_data = (double *)malloc(sizeof(double) * num);
			break;
	}
	return o;
}

void
obj_free(Object *o)
{
	if (o == NULL) return;

	switch (o->type) {
		case CHAR:
			free(o->char_data);
			break;
		case DOUBLE:
			free(o->double_data);
			break;
		case FLOAT:
			free(o->float_data);
			break;
		case INT:
			free(o->int_data);
			break;
		default:
			free(o->double_data);
			break;
	}
	free(o);
}
