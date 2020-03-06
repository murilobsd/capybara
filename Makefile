CC=		cc
CFLAGS=		
DEPS=		capybara.h
OBJS=		object.o

$(OBJS): $(DEPS)

capybara: $(OBJS)
	$(CC) -o $@ main.c  object.o

$(OBJS): $(DEPS)

.PHONY: clean

clean:
	rm -f $(OBJS) main.o *~ *.core
