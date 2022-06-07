CXX=g++
CC=gcc
CCFLAGS=-g -Wall -I/usr/local/include
CXXFLAGS=-g
LDFLAGS_OPENCV = \
    -L /usr/local/lib \
    -lopencv_calib3d \
    -lopencv_core \
    -lopencv_features2d \
    -lopencv_highgui \
    -lopencv_imgcodecs \
    -lopencv_imgproc \
    -lopencv_ml \
    -lopencv_objdetect \
    -lopencv_stitching \
    -lopencv_video \
    -lopencv_videoio 
LDFLAGS_JSON = -ljson-c
LDFLAGS_JPEG = -ljpeg

SRCFILES := $(wildcard *.cpp) 
OBJS := $(patsubst %.cpp,%.o,$(SRCFILES))
PROGRAMS = \
  djpeginfo \
  json-parameters \
  json_parser_example \
  json-test \
  parse_template_C \
  parse_template \
  read_file

%.o: %.cpp %.hpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# for C files, cannot compile here like this
#%.o: %.c %.h
#	$(CC) $< -o $@ $(CCFLAGS)

all: $(PROGRAMS)

djpeginfo: djpeginfo.c
	$(CC) $< -o $@ $(CCFLAGS)  $(LDFLAGS_JPEG)
json-parameters: json-parameters.o
	$(CXX) $< -o $@ $(CXXFLAGS)  $(LDFLAGS_JSON)
json_parser_example: json_parser_example.c
	$(CC) $< -o $@ file_utils_C.c $(CCFLAGS) $(LDFLAGS_JSON)
json_parser_example_cpp: json_parser_example_cpp.cpp
	$(CXX) $< -o $@ file_utils.o $(CXXFLAGS) $(LDFLAGS_JSON)
json-test: json-test.c
	 $(CC) $< -o $@ $(CCFLAGS) $(LDFLAGS_JSON)
parse_template_C: parse_template_C.c file_utils_C.h
	$(CC) $< -o $@ $(CCFLAGS)  $(LDFLAGS_JSON)
parse_template: parse_template.o file_utilskk.hpp file_utils.o
	$(CXX) $< -o $@ $(CXXFLAGS) file_utils.o $(LDFLAGS_JSON)
read_file: read_file.c file_utils_C.h
	$(CC) $< -o $@ $(CCFLAGS)

clean:
	rm -f $(OBJS) 

clobber: 
	rm -f $(OBJS) $(PROGRAMS)

depend:
	makedepend -- $(CXXFLAGS) -- $(SRCFILES)

# DO NOT DELETE
