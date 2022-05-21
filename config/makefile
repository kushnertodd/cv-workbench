CCFLAGS=-g
all: read_file parse_template
file_utils.o: file_utils.c
	gcc -c $(CCFLAGS) file_utils.c
read_file: read_file.c file_utils.o
	gcc -o read_file $(CCFLAGS) read_file.c file_utils.o
parse_template: parse_template.c file_utils.o
	gcc -o parse_template $(CCFLAGS) parse_template.c file_utils.o -ljson-c
