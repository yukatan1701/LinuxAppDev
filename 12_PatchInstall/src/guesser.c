#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>
#include <argp.h>
#include "config.h"

#define _(STRING) gettext(STRING)

const char *argp_program_version = "guesser 1.0";
const char *argp_program_bug_address = "<bug-gnu-utils@gnu.org>";

static char *doc = NULL;

static struct argp_option options[] = {
  {"roman", 'r', 0, 0, NULL},
  { 0 }
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  int *roman = state->input;
  switch (key)
  {
  case 'r':
    *roman = 1;
    break;
  default:
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static struct argp argp = { options, parse_opt, 0, NULL };

extern const char *tableRoman[];

/** Convert decimal number @p n to roman.
 * 
 * @param n decimal number
 * @return number converted to roman
 */
const char *toRoman(int n) {
  if (n >= 0 && n <= 100)
    return tableRoman[n];
  return NULL;
}

/** Convert roman number @p roman to decimal.
 * 
 * @param roman roman number
 * @return number converted to decimal
 */
int toDecimal(const char *roman) {
  if (roman == NULL)
    return -1;
  for (size_t i = 0; i <= 100; i++) {
    if (strcmp(tableRoman[i], roman) == 0)
      return i;
  }
  return -1;
}

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "");
  bindtextdomain(PACKAGE, LOCALE_PATH);
  textdomain(PACKAGE);
  printf("%s\n", LOCALE_PATH);
  doc = _("Guesser -- a program that guesses the intended number.");
  options[0].doc = _("Use roman number system");
  argp.doc = doc;
  argp.argp_domain = PACKAGE;
  int is_roman = 0;
  argp_parse(&argp, argc, argv, 0, 0, &is_roman);
  char *dir = dirname(realpath(argv[0], NULL));
  int lower = 0, upper = 101;
  if (is_roman)
    printf(_("Imagine a number from %s to %s!\n"), toRoman(lower+1), toRoman(upper-1));
  else
    printf(_("Imagine a number from %d to %d!\n"), lower + 1, upper - 1);
  const char *yes = _("yes");
  const char *no = _("no");
  size_t max_ans_len = sizeof(yes) > sizeof(no) ? sizeof(yes) : sizeof(no);
  while (lower < upper-1) {
    int middle = (lower + upper) / 2;
    if (is_roman)
      printf(_("Is your number greater than %s? (%s/%s)\n"), toRoman(middle), yes, no);
    else
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
  if (is_roman)
    printf(_("Your number is %s!\n"), toRoman(upper));
  else
    printf(_("Your number is %d!\n"), upper);
  return 0;
}