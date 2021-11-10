#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <rhash.h>
#include <ctype.h>
#include "config.h"
#ifdef HAVE_READLINE_READLINE_H
#include <readline/readline.h>
#endif

enum HASH_ALG {
  Unknown,
  MD5_Hex,
  MD5_64,
  SHA1_Hex,
  SHA1_64,
  TTH_Hex,
  TTH_64
};

typedef enum HASH_ALG hash_alg_t;

struct command {
  hash_alg_t alg;
  char *data;
  int is_filename;
  char is_valid;
};

typedef struct command command_t;

hash_alg_t strtoalg(const char *str, size_t n) {
  if (strncmp(str, "MD5", n) == 0)
    return MD5_Hex;
  if (strncmp(str, "md5", n) == 0)
    return MD5_64;
  if (strncmp(str, "SHA1", n) == 0)
    return SHA1_Hex;
  if (strncmp(str, "sha1", n) == 0)
    return SHA1_64;
  if (strncmp(str, "TTH", n) == 0)
    return TTH_Hex;
  if (strncmp(str, "tth", n) == 0)
    return TTH_64;
  return Unknown;
}

command_t read_command(const char *line) {
  command_t cmd;
  cmd.alg = Unknown;
  cmd.data = NULL;
  cmd.is_filename = 0;
  cmd.is_valid = 0;
  if (!line)
    return cmd;
  size_t len = strlen(line);
  if (len == 0 || (len == 1 && line[0] == '\n'))
    return cmd;
  char *cmd_name = malloc(1 * sizeof(char));
  cmd_name[0] = '\0';
  size_t cmd_name_size = 1;
  size_t i = 0;
  while (i < len && isspace(line[i]))
    ++i;
  for ( ; i < len; ++i) {
    if (isspace(line[i]))
      break;
    ++cmd_name_size;
    cmd_name = realloc(cmd_name, cmd_name_size);
    cmd_name[cmd_name_size-2] = line[i];
    cmd_name[cmd_name_size-1] = '\0';
  }
  char *data_name = malloc(1 * sizeof(char));
  data_name[0] = '\0';
  while (i < len && isspace(line[i]))
    ++i;
  size_t data_name_size = 1;
  int is_quote = 0/*, quote_state = 0*/;
  for ( ; i < len; ++i) {
    if (isspace(line[i]) && !is_quote)
      break;
    if (line[i] == '"' && is_quote) {
      //quote_state = 2;
      break;
    }
    if (line[i] == '"' && !is_quote) {
      is_quote = 1;
      //quote_state = 1;
      continue;
    }
    ++data_name_size;
    data_name = realloc(data_name, data_name_size);
    data_name[data_name_size-2] = line[i];
    data_name[data_name_size-1] = '\0';
  }
  hash_alg_t alg_type = strtoalg(cmd_name, strlen(cmd_name));
  if (alg_type == Unknown)
    return cmd;
  free(cmd_name);
  cmd.alg = alg_type;
  cmd.data = data_name;
  cmd.is_filename = !is_quote;
  cmd.is_valid = 1;
  return cmd;
}

int hash(command_t cmd, unsigned char *digest, char *output) {
  hash_alg_t alg = cmd.alg;
  int res = -1;
  if (alg == MD5_64 || alg == MD5_Hex) {
    res = (cmd.is_filename) ?
        rhash_file(RHASH_MD5, cmd.data, digest) :
        rhash_msg(RHASH_MD5, cmd.data, strlen(cmd.data), digest);
    rhash_print_bytes(output, digest, rhash_get_digest_size(RHASH_MD5),
        ((alg == MD5_Hex ? RHPR_HEX : RHPR_BASE64)));
  } else if (alg == SHA1_64 || alg == SHA1_Hex) {
    res = (cmd.is_filename) ?
        rhash_file(RHASH_SHA1, cmd.data, digest) :
        rhash_msg(RHASH_SHA1, cmd.data, strlen(cmd.data), digest);
    rhash_print_bytes(output, digest, rhash_get_digest_size(RHASH_SHA1),
        ((alg == SHA1_Hex ? RHPR_HEX : RHPR_BASE64)));
  } else if (alg == TTH_64 || alg == TTH_Hex) {
    res = (cmd.is_filename) ?
        rhash_file(RHASH_TTH, cmd.data, digest) :
        rhash_msg(RHASH_TTH, cmd.data, strlen(cmd.data), digest);
    rhash_print_bytes(output, digest, rhash_get_digest_size(RHASH_TTH),
        ((alg == SHA1_Hex ? RHPR_HEX : RHPR_BASE64)));
  }
  return res;
}

int main() {
  rhash_library_init();
  unsigned char digest[64];
  char output[130];
  while (1) {
    //printf("> ");
    char *line = NULL;
    errno = 0;
    int result = 0;
    #ifdef HAVE_READLINE_READLINE_H
    line = readline("(readline) > ");
    if (!line) {
      printf("\n");
      break;
    }
    #else
    size_t N = 0;
    printf("> ");
    result = getline(&line, &N, stdin);
    #endif
    if ((result < 0 && errno != 0) || !line) {
      perror("Failed to read line");
      if (line)
        free(line);
      continue;
    }
    if (result < 0) {
      if (line)
        free(line);
      printf("\n");
      break;
    }
    if (strlen(line) == 1 && line[0] == '\n')
      continue;
    command_t cmd = read_command(line);
    if (!cmd.is_valid) {
      fprintf(stderr, "Failed to recognize the command.\n");
      free(line);
      continue;
    }
    //printf("[cmd: %s][string: `%s`]\n", cmd.cmd_name, cmd.data);
    free(line);
    int hash_res = hash(cmd, digest, output);
    if (hash_res != 0) {
      fprintf(stderr, "Failed to get hash.\n");
    } else {
      printf("%s\n", output);
    }
  }
  return 0;
}