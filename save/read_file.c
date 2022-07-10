#include <stdio.h>
#include <stdlib.h>
#include "file_utils_C.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("usage: %s filename\n", argv[0]);
    exit(0);
  }
  char *filename = argv[1];
  long bufsize;
  char* source = read_file(filename, &bufsize);
  if (source == NULL) {
    printf("invalid file pointer for '%s'\n", filename);
  } else {
    printf("file '%s' has %ld bytes\n", filename, bufsize);
    free(source); // Don't forget to call free() later!
  }
}
