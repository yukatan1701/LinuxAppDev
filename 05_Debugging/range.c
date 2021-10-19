#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Not enough arguments. Usage: \n");
    return -1;
  }
  int M = argc > 2 ? atoi(argv[1]) : 0;
  int N = argc > 2 ? atoi(argv[2]) : atoi(argv[1]);
  int S = argc > 3 ? atoi(argv[3]) : 1;
  for (int I = M; I < N; I += S) {
    printf("%d\n", I);
  }
  return 0;
}