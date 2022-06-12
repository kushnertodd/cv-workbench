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
  experiment.o \
  experiment_step.o \
  experiment_step_data_source_descriptor.o \
  filesystem_data_source_descriptor.o \
  histogram.o \
  hough.o \
  image.o \
  internet_data_source_descriptor.o \
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
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)
image_test: image_test.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

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
experiment.o: experiment.hpp
experiment_step.o: wb_json_utils.hpp errors.hpp data_source_descriptor.hpp
experiment_step.o: wb_enums.hpp histogram.hpp hough.hpp image.hpp
experiment_step.o: experiment_step.hpp berkeley_db_data_source_descriptor.hpp
experiment_step.o: experiment_step_data_source_descriptor.hpp
experiment_step.o: filesystem_data_source_descriptor.hpp
experiment_step.o: internet_data_source_descriptor.hpp
experiment_step_data_source_descriptor.o: wb_json_utils.hpp errors.hpp
experiment_step_data_source_descriptor.o: data_source_descriptor.hpp
experiment_step_data_source_descriptor.o: wb_enums.hpp histogram.hpp
experiment_step_data_source_descriptor.o: hough.hpp image.hpp
experiment_step_data_source_descriptor.o: experiment_step_data_source_descriptor.hpp
filesystem_data_source_descriptor.o: wb_json_utils.hpp errors.hpp
filesystem_data_source_descriptor.o: data_source_descriptor.hpp wb_enums.hpp
filesystem_data_source_descriptor.o: histogram.hpp hough.hpp image.hpp
filesystem_data_source_descriptor.o: filesystem_data_source_descriptor.hpp
file_utils.o: file_utils.hpp
histogram.o: Histogram.hpp
hough.o: Hough.hpp
image.o: Image.hpp
internet_data_source_descriptor.o: wb_json_utils.hpp errors.hpp
internet_data_source_descriptor.o: data_source_descriptor.hpp wb_enums.hpp
internet_data_source_descriptor.o: histogram.hpp hough.hpp image.hpp
internet_data_source_descriptor.o: internet_data_source_descriptor.hpp
parse_experiment_json.o: file_utils.hpp wb_utils.hpp wb_json_utils.hpp
parse_experiment_json.o: errors.hpp wb_enums.hpp image.hpp histogram.hpp
parse_experiment_json.o: hough.hpp data_source_descriptor.hpp
parse_experiment_json.o: berkeley_db_data_source_descriptor.hpp
parse_experiment_json.o: experiment_step.hpp
parse_experiment_json.o: filesystem_data_source_descriptor.hpp
parse_experiment_json.o: internet_data_source_descriptor.hpp
parse_experiment_json.o: experiment_step_data_source_descriptor.hpp
parse_experiment_json.o: experiment.hpp
wb_json_utils.o: wb_json_utils.hpp errors.hpp
wb_utils.o: wb_utils.hpp
