#include <assert.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

void read_lines(char ***dest_lines, size_t *dest_n, FILE *file) {
  assert(file && "File must be opened!");
  assert(dest_lines && "Destination lines must be specified!");
  assert(dest_n && "Destination number must be specified!");
  char **lines = NULL;
  int ch, new_line = 1;
  size_t line_n = 0, char_n = 1;
  while (1) {
    ch = fgetc(file);
    if (ch == EOF)
      break;
    if (new_line) {
      ++line_n;
      lines = realloc(lines, sizeof(char *) * line_n);
      new_line = 0;
    }
    if (ch == '\n') {
      lines[line_n - 1] = realloc(lines[line_n - 1], sizeof(char) * char_n);
      lines[line_n - 1][char_n - 1] = '\0';
      new_line = 1;
      char_n = 1;
    } else {
      ++char_n;
      char **cur_line = &lines[line_n - 1];
      *cur_line = realloc(*cur_line, sizeof(char) * char_n);
      (*cur_line)[char_n-2] = ch;
      (*cur_line)[char_n-1] = '\0';
    }
  };
  *dest_lines = lines;
  *dest_n = line_n;
}

void free_lines(char **lines, size_t n) {
  if (!lines || n < 1)
    return;
  for (size_t i = 0; i < n; ++i) {
    free(lines[i]);
  }
  free(lines);
}



int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Not enough arguments.\n");
    return -1;
  }
  const char *filename = argv[1];
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("Failed to open file");
    return -1;
  }
  size_t n;
  char **lines;
  read_lines(&lines, &n, file);
  for (size_t i = 0; i < n; ++i) {
    printf("%s\n", lines[i]);
  }
  free_lines(lines, n);
  fclose(file);
  return 0;
}