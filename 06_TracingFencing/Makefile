GENERATES=move *~ *.orig

all: move.c
	cc move.c -Wall -Wextra -o move

preload: fake_unlink.c
	cc -shared -fPIC -Wall -Wextra -o fake_unlink.so fake_unlink.c -ldl

%.orig:
	cp $* $*.orig

test: move from.txt.orig test.sh
	./test.sh

clean:
	rm -rf $(GENERATES)