#include <err.h>
#include <stdlib.h>
#include <string.h>

#include "capybara/utils.h"

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

char *
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

