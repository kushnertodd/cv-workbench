#include <stdio.h>
#include <stdlib.h>
#include "file_utils.h"

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
    for (int i = 0; i < bufsize; i++) {
      int j = source[i];
      printf("%3d 0x%02x '%c'\n", i, j, j);
    }
    free(source); // Don't forget to call free() later!
  }
}
