#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "."

int main(int argc, char *argv[]) {
  char *dir = dirname(realpath(argv[0], NULL));
  setlocale (LC_ALL, "");
  bindtextdomain ("guesser", LOCALE_PATH);
  textdomain ("guesser");
  int lower = 0, upper = 101;
  printf(_("Imagine a number from %d to %d!\n"), lower + 1, upper - 1);
  const char yes[] = _("yes");
  const char no[] = _("no");
  size_t max_ans_len = sizeof(yes) > sizeof(no) ? sizeof(yes) : sizeof(no);
  while (lower < upper-1) {
    int middle = (lower + upper) / 2;
    printf(_("Is your number greater than %d? (%s/%s)\n"), middle, yes, no);
    char *line = NULL;
    int ans = 0;
    while (1) {
      int read = getline(&line, &max_ans_len, stdin);
      if (read == -1) {
        perror(_("Failed to read line"));
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
        printf(_("Invalid answer, try again!\n"));
      }
    }
    if (ans == 0) {
      upper = middle;
    } else {
      lower = middle;
    }
  }
  printf(_("Your number is %d!\n"), upper);
  return 0;
}