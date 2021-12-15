bin_PROGRAMS=guesser
guesser_SOURCES=table.c guesser.c
AM_CFLAGS = -D'LOCALE_PATH="$(localedir)"' -g

pkgdata_DATA = guesser.man

%.man: %
	$(HELP2MAN) -N --output=$@ --name='@PACKAGE_NAME@' ./$<