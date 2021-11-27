#include "tests.h"

int main() {
  int count_pass = 0;
  int count_fail = 0;
  long *ai = 0;
  buf_grow(ai, 1000);
  TEST("grow 1000", buf_capacity(ai) == 1000);
  TEST("size 0 (grow)", buf_size(ai) == 0);
  buf_trunc(ai, 100);
  TEST("trunc 100", buf_capacity(ai) == 100);
  buf_free(ai);
  return !(count_fail == 0);
}