#include <assert.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DX 3

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

size_t get_num_len(size_t n) {
  size_t res = 0;
  do
    ++res;
  while ((n /= 10));
  return res;
}

void draw(char **lines, size_t n, const char *filename) {
  initscr();
  noecho();
  cbreak();
  const char title_file[] = "File: ";
  const char title_size[] = ", size: ";
  const size_t n_length = 20;
  size_t total_max_length = sizeof(title_file) + strlen(filename) +
                            sizeof(title_file) + n_length + 2;
  char *title = calloc(total_max_length, sizeof(char));
  snprintf(title, total_max_length, "%s%s%s%lu", title_file, filename,
           title_size, n);
  printw(title);
  refresh();
  size_t box_width = COLS - 2*DX, box_height = LINES - 2*DX;
  WINDOW *win = newwin(box_height, box_width, DX, DX);
  keypad(stdscr, TRUE);
  keypad(win, TRUE);
  curs_set(0);
  scrollok(win, TRUE);
  size_t text_height = box_height-2;
  int di = 0;
  int c = 0;
  size_t num_len = get_num_len(n);
  do {
    if (c == ' ' || c == KEY_DOWN) {
      if (di + text_height < n)
        ++di;
    } else if (c == KEY_UP) {
      if (di > 0)
        --di;
    }
    wclear(win);
    for (size_t i = 0; i < text_height; ++i) {
      if (i + di > n - 1)
        break;
      mvwprintw(win, i + 1, 1, "%*lu: %s\n", num_len + 1, i + di + 1,
                lines[i + di]);
      box(win, 0, 0);
    }
    wrefresh(win);
  } while ((c = getch()) != 27);
  endwin();
  free(title);
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
  fclose(file);
  draw(lines, n, filename);
  free_lines(lines, n);
  return 0;
}