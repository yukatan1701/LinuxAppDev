set pagination off
set logging overwrite on
set logging file gdb2.out
set logging on

set $var = 1

break range.c:13 if ($var >= 28 & $var++ <= 35)
  command 1
  printf "@@@%d %d %d %d\n", M, N, S, I
  continue
end

run -100 100 3 > /dev/null

set logging off
quit