#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int lower = 0, upper = 101;
  printf("Guess a number from %d to %d!\n", lower + 1, upper - 1);
  while (lower < upper-1) {
    int middle = (lower + upper) / 2;
    const char yes[] = "yes";
    const char no[] = "no";
    size_t max_ans_len = sizeof(yes) > sizeof(no) ? sizeof(yes) : sizeof(no);
    printf("Is your number greater than %d? (%s/%s)\n", middle, yes, no);
    char *line = NULL;
    int ans = 0;
    while (1) {
      int read = getline(&line, &max_ans_len, stdin);
      if (read == -1) {
        perror("Failed to read line");
        exit(1);
      }
      line[strlen(line) - 1] = 0;
      if (strcmp(yes, line) == 0) {
        ans = 1;
        break;
      } else if (strcmp(no, line) == 0) {
        ans = 0;
        break;
      } else {
        printf("Invalid answer, try again!\n");
      }
    }
    if (ans == 0) {
      upper = middle;
    } else {
      lower = middle;
    }
  }
  printf("Your number is %d!\n", upper);
  return 0;
}