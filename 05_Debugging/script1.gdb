set pagination off
set logging overwrite on
set logging file gdb1.out
set logging on

break range.c:13 if I % 5 == 0
  command 1
  printf "@@@%d %d %d %d\n", M, N, S, I
  continue
end

run 1 12 > /dev/null

set logging off
quit