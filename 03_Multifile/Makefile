GENERATES = prog prog-a prog-so README
TRASH = *.o *~ o.* *.o.pic *.a *.so *.test
PARAM1=param
PARAM3=lorem ipsum dolor
LDPATH=LD_LIBRARY_PATH=`pwd`

all:    README prog prog-a prog-so

README: prog
	./$< 2> $@

libs: liboutput_static.a liboutput.so

%.o.pic:	%.c
		cc $< -fPIC -c -o $@


test: run1 run2 run3
	for number in 1 2 3; do \
		cmp 1$$number.test 2$$number.test ; \
		cmp 2$$number.test 3$$number.test ; \
	done
	
run1: prog
	./$< > 11.test 2>11.test
	./$< $(PARAM1) > 12.test 2>12.test
	./$< $(PARAM3) > 13.test 2>13.test

run2: prog-a
	./$< > 210.test 2>210.test
	cat 210.test | sed "s/prog-a/prog/" > 21.test
	./$< $(PARAM1) > 22.test 2>22.test
	./$< $(PARAM3) > 23.test 2>23.test

run3: prog-so
	$(LDPATH) ./$< > 310.test 2>310.test
	cat 310.test | sed "s/prog-so/prog/" > 31.test
	$(LDPATH) ./$< $(PARAM1) > 32.test 2>32.test
	$(LDPATH) ./$< $(PARAM3) > 33.test 2>33.test

prog:   const.o fun.o prog.o

prog-a: prog.o liboutput_static.a
	cc $^ -o $@

prog-so: prog.o liboutput.so
	cc  -L. prog.o -loutput -o $@

%.a: fun.o const.o
	ar -rcs $@ const.o fun.o

%.so: fun.o.pic const.o.pic
	cc -shared $^ -o $@

fun.o:  outlib.h

clean:
	rm -f $(TRASH)

distclean:      clean
	rm -rf $(GENERATES)
