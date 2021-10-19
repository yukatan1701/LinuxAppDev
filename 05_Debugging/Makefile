GENERATES=range gdb*.out *.txt

all:
	gcc range.c -g -O0 -Wall -Wextra -o range

gdb%.out: script%.gdb range
	gdb -q -batch -x $< --args ./range > /dev/null

test: gdb1.out gdb2.out
	cat gdb1.out | grep "@@@" | tr -d '@' > gdb11.out
	cmp gdb11.out gdb1.sample
	cat gdb2.out | grep "@@@" | tr -d '@' > gdb21.out
	cmp gdb21.out gdb2.sample

clean:
	rm -rf $(GENERATES)