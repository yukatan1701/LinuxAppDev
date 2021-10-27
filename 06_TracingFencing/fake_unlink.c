#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

typedef int (*real_unlink_t)(const char *);

int real_unlink(const char *__filename) {
  return ((real_unlink_t) dlsym(RTLD_NEXT, "unlink"))(__filename);
}

int unlink(const char *__filename) {
  if (strstr(__filename, "PROTECT") == NULL) {
    return real_unlink(__filename);
  }
	return 0;
}