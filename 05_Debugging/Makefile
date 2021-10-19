GENERATES=range gdb*.out *.txt *.tmp

all: build
	
build:
	gcc range.c -g -O0 -Wall -Wextra -o range

gdb%.out: build
	gdb -q -batch -x script$*.gdb --args ./range > /dev/null

test_%: gdb%.out
	cat $< | grep "@@@" | tr -d '@' > $<.tmp
	cmp $<.tmp test$*.sample

test: test_1 test_2

clean:
	rm -rf $(GENERATES)