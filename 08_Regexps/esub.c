#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdio.h>
#include <ctype.h>

#define ERRBUF_SIZE 128
#define NMATCH 128

void usage() {
  printf("Not enough arguments.\n"
         "Usage: ./esub <regexp> <substitution> <string>\n");
}

void error(int errcode, regex_t *regex, char *errbuf, size_t n) {
  regerror(errcode, regex, errbuf, n);
  printf("Failed to compile the regular expression: %s\n", errbuf);
}

char parse_char(const char *str, size_t n) {
  if (n == 0)
    return 0;
  if (n == 1)
    return str[0];
  char a = str[0], b = str[1];
  if (a != '\\')
    return a;
  switch (b)
  {
  case 'a':
    return '\a';
  case 'b':
    return '\b';
  case 'e':
    return '\e';
  case 'f':
    return '\f';
  case 'n':
    return '\n';
  case 'r':
    return '\r';
  case 't':
    return '\t';
  case 'v':
    return '\v';
  default:
    return b;
  }
}

char *process_substitution(char *substit, char *string, regmatch_t *matches, int nm) {
  regmatch_t zero_match = matches[0];
  if (zero_match.rm_eo == -1 || zero_match.rm_so == -1) {
    return NULL;
  }
  char *dest = calloc(1, sizeof(char));
  char *slash = NULL;
  char *subst_pos = substit;
  while ((slash = strstr(subst_pos, "\\")) != NULL) {
    strncat(dest, subst_pos, slash - subst_pos);
    if (isdigit(slash[1])) {
      int N = 0;
      char *num = &slash[1];
      while (num && isdigit(*num)) {
        N = N * 10 + (*num - '0');
        ++num;
      }
      if (N >= nm) {
        printf("Invalid match number: %d.\n", N);
        free(dest);
        return NULL;
      }
      regmatch_t match = matches[N];
      strncat(dest, string + match.rm_so, match.rm_eo - match.rm_so);
      subst_pos = num;
    } else if (slash[1] == '\\') {
      strcat(dest, "\\");
      subst_pos = slash + 2;
    } else {
      char ch = parse_char(slash, 2);
      strncat(dest, &ch, 1);
      subst_pos = slash + 2;
    }
  }
  if (subst_pos != NULL)
    strcat(dest, subst_pos);
  char *result = calloc(1, sizeof(char));
  strncpy(result, string, zero_match.rm_so);
  strcat(result, dest);
  strcat(result, string + zero_match.rm_eo);
  free(dest);
  return result;
}

int main(int argc, char **argv) {
  if (argc < 4) {
    usage();
    return -1;
  }
  char *regexp_str = argv[1];
  char *substit = argv[2];
  char *string = argv[3];
  regex_t regex;
  char errbuf[ERRBUF_SIZE];
  int comp_err = regcomp(&regex, regexp_str, REG_EXTENDED);
  if (comp_err != 0) {
    error(comp_err, &regex, errbuf, ERRBUF_SIZE);
    return -1;
  }
  regmatch_t matches[NMATCH];
  int exec_err = regexec(&regex, string, NMATCH, matches, 0);
  if (exec_err != 0) {
    error(exec_err, &regex, errbuf, ERRBUF_SIZE);
    return -1;
  }
  // TODO: get pocket max idx
  int max_idx = -1;
  for ( ; max_idx < NMATCH && matches[max_idx].rm_so != -1; ++max_idx)
    ;
  if (max_idx == -1)
    return 0;
  char *res = process_substitution(substit, string, matches, max_idx);
  if (!res)
    return -1;
  
  printf("%s\n", res);
  free(res);
  regfree(&regex);
  return 0;
}