#include <stdio.h>
#include <stdlib.h>

/**
 * returns size of file in bytes
 * @param fp file pointer
 * @return long byte count
 */
long file_size(FILE *fp) {
  long numbytes;

  // Get the number of bytes
  fseek(fp, 0L, SEEK_END);
  numbytes = ftell(fp);

  // reset the file position indicator to the beginning of the file
  fseek(fp, 0L, SEEK_SET);
  return numbytes;
}

/**
 * reads all characters in filename and returns length in file_bytes
 * (m)allocates buffer and fills with file contents
 * be sure to free()
 * @return file contents or NULL on failure
 */
char *read_file(char *filename, long *file_bytes) {

  FILE *fp = fopen(filename, "r");
  if (fp == NULL)
    return NULL;

  // Get the size of the file.
  long bufsize = file_size(fp);
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

void write_file(char *filename, long file_bytes, char* buf) {
  FILE *fp;
  fp = fopen(filename, "w");
  if (fp != NULL) {
    fwrite(buf, 1, file_bytes, fp);
    fclose(fp);
  }
}
