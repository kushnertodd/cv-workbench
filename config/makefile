CCFLAGS=-g
all: file_utils_cpp.o file_utils.o json.o parse_template read_file

file_utils.o: file_utils.c file_utils.h
	gcc -c $(CCFLAGS) file_utils.c

file_utils_cpp.o: file_utils_cpp.cpp file_utils_cpp.hpp
	g++ -c file_utils_cpp.cpp

json.o: json.cpp
	g++ -c json.cpp

parse_template: parse_template.c file_utils_cpp.o
	gcc -o parse_template $(CCFLAGS) parse_template.c file_utils_cpp.o -ljson-c

read_file: read_file.c file_utils.o
	gcc -o read_file $(CCFLAGS) read_file.c file_utils.o

clean:
	rm -f *.o parse_template read_file
