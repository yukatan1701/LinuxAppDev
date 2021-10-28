GENERATES=move *~ *.orig from.txt to.txt PROTECT_from.txt

all: move.c
	cc move.c -Wall -Wextra -o move

preload: fake_unlink.c
	cc -shared -fPIC -Wall -Wextra -o fake_unlink.so fake_unlink.c -ldl

%.orig:
	echo "testfile" > $*
	cp $* $*.orig

test: move from.txt.orig test.sh fake_unlink.so
	./test.sh

clean:
	rm -rf $(GENERATES)