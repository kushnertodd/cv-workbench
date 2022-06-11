#include <stdio.h>
#include <stdlib.h>

long file_size(FILE *infile);
char *read_file(char *filename, long *file_bytes);
void write_file(char *filename, long file_bytes, char* buf);

