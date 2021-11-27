SUBDIRS =src tests
GENERATES = *~ aclocal.m4 autom4te.cache compile config.guess config.* \
	configure depcomp install-sh libtool ltmain.sh Makefile Makefile.in \
	missing stamp-h1 .deps .libs test-driver

clean:
	rm -rf $(GENERATES)

gcov:	check
	$(MAKE) $(MAKEFLAGS) -C src gcov