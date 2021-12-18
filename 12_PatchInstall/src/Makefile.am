bin_PROGRAMS=guesser
guesser_SOURCES=table.c guesser.c
AM_CFLAGS = -D'LOCALE_PATH="$(localedir)"' -g

man1_MANS = guesser.1

%.1: %
	$(HELP2MAN) -N --output=$@ --name='@PACKAGE_NAME@' ./$<