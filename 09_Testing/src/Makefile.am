CFLAGS = -std=c99 -Wall -Wextra -O3 -g3
GENERATES = *.la *.lo *~ Makefile.in Makefile .deps .libs

lib_LTLIBRARIES = libgrowbuf.la

libgrowbuf.c: buf.h

clean:
	rm -rf $(GENERATES)
