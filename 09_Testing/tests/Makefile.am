TESTS = test_init_free test_grow_trunc test_pop
check_PROGRAMS = test_init_free test_grow_trunc test_pop

AM_CFLAGS = -I$(top_builddir)/src @CHECK_CFLAGS@
LDADD = $(top_builddir)/src/libgrowbuf.la @CHECK_LIBS@

GENERATES = Makefile Makefile.in test_grow_trunc test_grow_trunc.log \
	test_grow_trunc.o test_grow_trunc.trs test_init_free test_init_free.log \
	test_init_free.o test_init_free.trs test_pop test_pop.log test_pop.o \
	test_pop.trs test-suite.log .deps .libs

clean:
	rm -rf $(GENERATES)