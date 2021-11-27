CFLAGS = -std=c99 -Wall -Wextra -pedantic
if COND_GCOV
CFLAGS  += -O0 -g -fprofile-arcs -ftest-coverage
else
CFLAGS  += -O3 -g3
endif
GENERATES = *.la *.lo *~ Makefile.in Makefile .deps .libs

lib_LTLIBRARIES = libgrowbuf.la

libgrowbuf.c: buf.h

clean:
	rm -rf $(GENERATES)

gcov:
	gcov -o .libs libgrowbuf -t -k -b | egrep -v '[[:digit:]]:[ /][*]'
