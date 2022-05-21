#include <stdio.h>
#include <stdlib.h>

long file_size(FILE *fp) {
  long numbytes;

  // Get the number of bytes
  fseek(fp, 0L, SEEK_END);
  numbytes = ftell(fp);
  printf("3 bufsize %ld\n", numbytes);

  // reset the file position indicator to the beginning of the file
  fseek(fp, 0L, SEEK_SET);
  return numbytes;
}

/*
 * reads all characters in filename and returns length in file_bytes
 * if failure
 *   returns NULL
 * else
 *    returns pointer to buffer with characters
 *    be sure to free()
 */
char *read_file(char *filename, long *file_bytes) {

  FILE *fp = fopen(filename, "r");
  if (fp == NULL)
    return NULL;

  // Get the size of the file.
  long bufsize = file_size(fp);
  printf("2 bufsize %ld\n", bufsize);
  if (bufsize == -1)
    return NULL;

  // Allocate our buffer to that size.
  char *buf = malloc(sizeof(char) * (bufsize + 1));

  // Read the entire file into memory.
  size_t newLen = fread(buf, sizeof(char), bufsize, fp);
  if ( ferror( fp ) != 0 ) {
    return NULL;
  } else {
    buf[newLen++] = '\0'; // Just to be safe.
  }
  fclose(fp);
  *file_bytes = bufsize;
  return buf;
}
