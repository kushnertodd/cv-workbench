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
