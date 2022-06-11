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
SRCOBJS :=  \
  berkeley_db_data_source_descriptor.o \
  data_source_descriptor.o \
  errors.o \
  filesystem_data_source_descriptor.o \
  histogram.o \
  hough.o \
  image.o \
  file_utils.o \
  wb_json_utils.o \
  wb_utils.o

PROGRAMS = \
  djpeginfo \
  json_parser_example \
  parse_experiment_json

%.o: %.cpp %.hpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# for C files, cannot compile here like this
#%.o: %.c %.h
#	$(CC) $< -o $@ $(CCFLAGS)

all: $(PROGRAMS)

djpeginfo: djpeginfo.o
	$(CC) $< -o $@ $(CCFLAGS)  $(LDFLAGS_JPEG)
json_parser_example: json_parser_example.o
	$(CC) $< -o $@ file_utils_C.o $(CCFLAGS) $(LDFLAGS_JSON)
parse_experiment_json: parse_experiment_json.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON)

objs:
	@echo $(OBJS)

clean:
	rm -f $(OBJS)

clobber: 
	rm -f $(OBJS) $(PROGRAMS)

depend:
	makedepend -- $(CXXFLAGS) -- $(SRCFILES)

# DO NOT DELETE

berkeley_db_data_source_descriptor.o: wb_json_utils.hpp errors.hpp
berkeley_db_data_source_descriptor.o: data_source_descriptor.hpp wb_enums.hpp
berkeley_db_data_source_descriptor.o: histogram.hpp hough.hpp image.hpp
berkeley_db_data_source_descriptor.o: berkeley_db_data_source_descriptor.hpp
data_source_descriptor.o: Data_source_descriptor.hpp wb_enums.hpp
data_source_descriptor.o: histogram.hpp hough.hpp image.hpp
errors.o: errors.hpp
file_utils.o: file_utils.hpp
histogram.o: Histogram.hpp
hough.o: Hough.hpp
image.o: Image.hpp
parse_experiment_json.o: file_utils.hpp wb_utils.hpp wb_json_utils.hpp
parse_experiment_json.o: errors.hpp wb_enums.hpp image.hpp histogram.hpp
parse_experiment_json.o: hough.hpp data_source_descriptor.hpp
parse_experiment_json.o: berkeley_db_data_source_descriptor.hpp
wb_json_utils.o: wb_json_utils.hpp errors.hpp
wb_utils.o: wb_utils.hpp
