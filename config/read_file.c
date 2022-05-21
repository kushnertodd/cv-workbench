#include <stdio.h>
#include <stdlib.h>
#include "file_utils.h"

int main() {
  char *filename = "foo.txt";
  long bufsize;
  char* source = read_file(filename, &bufsize);
  printf("1 bufsize %ld\n", bufsize);
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
