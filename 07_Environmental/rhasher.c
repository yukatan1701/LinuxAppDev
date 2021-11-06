#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// return NULL if EOF
char *read_line() {
  char *line = malloc(1 * sizeof(char));
  line[0] = '\0';
  int ch = 0;
  size_t len = 1;
  int has_eof = 0;
  while ((ch = getchar()) != '\n') {
    if (ch == EOF) {
      has_eof = 1;
      break;
    }
    ++len;
    line = realloc(line, len);
    line[len - 2] = (char) ch;
    line[len - 1] = '\0';
  }
  if (has_eof) {
    free(line);
    return NULL;
  }
  return line;
}

int main() {
  while (1) {
    char *line = read_line();
    if (!line)
      break;
    char *alg_name = strtok(line, " ");
    if (!alg_name) {
      free(line);
      continue;
    }
    char *data = strtok(NULL, " ");
    if (!data) {
      free(line);
      continue;
    }
    printf("[%s][%s]\n", alg_name, data);
    free(line);
  }
  return 0;
}