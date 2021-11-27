#include "tests.h"

int main() {
  int count_pass = 0;
  int count_fail = 0;
  float *a = 0;
  buf_push(a, 1.1);
  buf_push(a, 1.2);
  buf_push(a, 1.3);
  buf_push(a, 1.4);
  TEST("size 4", buf_size(a) == 4);
  TEST("pop 3", buf_pop(a) == (float)1.4f);
  buf_trunc(a, 3);
  TEST("size 3", buf_size(a) == 3);
  TEST("pop 2", buf_pop(a) == (float)1.3f);
  TEST("pop 1", buf_pop(a) == (float)1.2f);
  TEST("pop 0", buf_pop(a) == (float)1.1f);
  TEST("size 0 (pop)", buf_size(a) == 0);
  buf_free(a);
  return count_fail != 0;
}