CCFLAGS=-g
CC=gcc
CPP=g++
LIBFLAGS=-ljson-c
PROGRAMS=
OBJECTS=file_utils.o json.o json-parameters.o operator_template.o parse_template.o

# $(CPP) $(CCFLAGS) -o $@ $< -ljson-c

all: $(OBJECTS)

#%: %.cpp %.hpp
#	$(CPP) $(CCFLAGS) -o $@ $< $(LIBFLAGS)
	
file_utils.o: file_utils.cpp file_utils.hpp
	g++ -c file_utils.cpp

json.o: json.cpp json.hpp
	g++ -c json.cpp

operator_template.o: operator_template.cpp operator_template.hpp
	g++ -c operator_template.cpp

parse_template: parse_template.c file_utils.o
	gcc -o parse_template $(CCFLAGS) parse_template.c file_utils.o -ljson-c

clean:
	rm -f *.o $(PROGRAMS)
	
CCFLAGS=-g

PROGRAMS=

%: %.c
	gcc -g -o $@ $< -ljson-c
%: %.cpp
	g++ -g -o $@ $< -ljson-c
	
all: file_utils_cpp.o file_utils.o json.o parse_template read_file

#file_utils.o: save/file_utils.c save/file_utils.h
#	gcc -c $(CCFLAGS) file_utils.c

file_utils.o: file_utils.cpp file_utils.hpp
	g++ -c file_utils_cpp.cpp

json.o: json.cpp
	g++ -c json.cpp

#parse_template: save/parse_template.c file_utils_cpp.o
#	gcc -o parse_template $(CCFLAGS) parse_template.c file_utils_cpp.o -ljson-c

#read_file: save/read_file.c file_utils.o
#	gcc -o read_file $(CCFLAGS) read_file.c file_utils.o

clean:
	rm -f *.o parse_template read_file

