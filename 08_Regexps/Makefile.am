CFLAGS = -Wall -Wextra -g
GENERATES=*.m4 *.cache *~ compile config.* configure depcomp install-sh	Makefile.in missing rhasher *.o stamp-h1 .deps *.log *.trs test-driver Makefile

bin_PROGRAMS=esub

esub_SOURCES=esub.c

#TESTS=test.sh

#test.sh:
#	echo 'echo -n 'MD5 "meow"' | ./rhasher | tr -d '\n''
#	chmod +x $@

clean-all:
	rm -rf ${GENERATES}
