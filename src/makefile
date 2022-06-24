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
  file_utils.o \
  filesystem_data_source_descriptor.o \
  histogram.o \
  hough.o \
  image.o \
  image_header.o \
  internet_data_source_descriptor.o \
  kernel.o \
  operator.o \
  operator_filter_edge_kirsch.o \
  operator_filter_edge_prewitt.o \
  operator_filter_edge_roberts.o \
  operator_filter_edge_sobel.o \
  operator_producer.o \
  operator_transform_intensity_map.o \
  operator_utils.o \
  variance_stats.o \
  wb_json_utils.o \
  wb_utils.o 

PROGRAMS = \
  djpeginfo \
  image-create \
  image-dump \
  image-info \
  image-stats \
  image-test \
  parse_experiment_json
  # json_parser_example \

%.o: %.cpp %.hpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# for C files, cannot compile here like this
#%.o: %.c %.h
#	$(CC) $< -o $@ $(CCFLAGS)

all: $(PROGRAMS)

djpeginfo: djpeginfo.o
	$(CC) $< -o $@ $(CCFLAGS)  $(LDFLAGS_JPEG)

image-create: image-create.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

image-dump: image-dump.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

image-info: image-info.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

image-stats: image-stats.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

image-test: image-test.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

#json_parser_example: json_parser_example.o
#	$(CC) $< -o $@ file_utils_C.o $(CCFLAGS) $(LDFLAGS_JSON)

parse_experiment_json: parse_experiment_json.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

tokens: tokens.o file_utils.o
	$(CXX) tokens.cpp -o tokens file_utils.o

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
berkeley_db_data_source_descriptor.o: data_source_descriptor.hpp wb_defs.hpp
berkeley_db_data_source_descriptor.o: histogram.hpp hough.hpp image.hpp
berkeley_db_data_source_descriptor.o: image_header.hpp
berkeley_db_data_source_descriptor.o: berkeley_db_data_source_descriptor.hpp
data_source_descriptor.o: wb_utils.hpp data_source_descriptor.hpp wb_defs.hpp
data_source_descriptor.o: histogram.hpp hough.hpp image.hpp errors.hpp
data_source_descriptor.o: image_header.hpp
errors.o: errors.hpp
experiment.o: experiment.hpp wb_defs.hpp errors.hpp image.hpp
experiment.o: image_header.hpp histogram.hpp hough.hpp experiment_step.hpp
experiment.o: data_source_descriptor.hpp wb_json_utils.hpp
experiment_step.o: wb_json_utils.hpp errors.hpp data_source_descriptor.hpp
experiment_step.o: wb_defs.hpp histogram.hpp hough.hpp image.hpp
experiment_step.o: image_header.hpp experiment_step.hpp
experiment_step.o: berkeley_db_data_source_descriptor.hpp
experiment_step.o: experiment_step_data_source_descriptor.hpp
experiment_step.o: filesystem_data_source_descriptor.hpp
experiment_step.o: internet_data_source_descriptor.hpp operator.hpp
experiment_step.o: operator_producer.hpp wb_utils.hpp
experiment_step_data_source_descriptor.o: wb_json_utils.hpp errors.hpp
experiment_step_data_source_descriptor.o: data_source_descriptor.hpp
experiment_step_data_source_descriptor.o: wb_defs.hpp histogram.hpp hough.hpp
experiment_step_data_source_descriptor.o: image.hpp image_header.hpp
experiment_step_data_source_descriptor.o: experiment_step_data_source_descriptor.hpp
filesystem_data_source_descriptor.o: wb_json_utils.hpp errors.hpp
filesystem_data_source_descriptor.o: wb_utils.hpp data_source_descriptor.hpp
filesystem_data_source_descriptor.o: wb_defs.hpp histogram.hpp hough.hpp
filesystem_data_source_descriptor.o: image.hpp image_header.hpp
filesystem_data_source_descriptor.o: filesystem_data_source_descriptor.hpp
file_utils.o: file_utils.hpp
histogram.o: Histogram.hpp
hough.o: Hough.hpp
image.o: /usr/include/jpeglib.h /usr/include/jmorecfg.h image.hpp errors.hpp
image.o: image_header.hpp wb_defs.hpp wb_utils.hpp data_source_descriptor.hpp
image.o: histogram.hpp hough.hpp
image-create.o: errors.hpp image.hpp image_header.hpp wb_defs.hpp
image-create.o: wb_utils.hpp data_source_descriptor.hpp histogram.hpp
image-create.o: hough.hpp file_utils.hpp
image_header.o: wb_utils.hpp data_source_descriptor.hpp wb_defs.hpp
image_header.o: histogram.hpp hough.hpp image.hpp errors.hpp image_header.hpp
image-test.o: errors.hpp image.hpp image_header.hpp wb_defs.hpp
internet_data_source_descriptor.o: wb_json_utils.hpp errors.hpp
internet_data_source_descriptor.o: data_source_descriptor.hpp wb_defs.hpp
internet_data_source_descriptor.o: histogram.hpp hough.hpp image.hpp
internet_data_source_descriptor.o: image_header.hpp
internet_data_source_descriptor.o: internet_data_source_descriptor.hpp
kernel.o: wb_utils.hpp data_source_descriptor.hpp wb_defs.hpp histogram.hpp
kernel.o: hough.hpp image.hpp errors.hpp image_header.hpp kernel.hpp
operator.o: operator.hpp wb_defs.hpp data_source_descriptor.hpp histogram.hpp
operator.o: hough.hpp image.hpp errors.hpp image_header.hpp
operator_filter_edge_prewitt.o: wb_defs.hpp operator_filter_edge_prewitt.hpp
operator_filter_edge_prewitt.o: operator.hpp data_source_descriptor.hpp
operator_filter_edge_prewitt.o: histogram.hpp hough.hpp image.hpp errors.hpp
operator_filter_edge_prewitt.o: image_header.hpp
operator_filter_edge_sobel.o: kernel.hpp image.hpp errors.hpp
operator_filter_edge_sobel.o: image_header.hpp wb_defs.hpp operator_utils.hpp
operator_filter_edge_sobel.o: operator_filter_edge_sobel.hpp operator.hpp
operator_filter_edge_sobel.o: data_source_descriptor.hpp histogram.hpp
operator_filter_edge_sobel.o: hough.hpp
operator_producer.o: operator_filter_edge_prewitt.hpp operator.hpp
operator_producer.o: wb_defs.hpp data_source_descriptor.hpp histogram.hpp
operator_producer.o: hough.hpp image.hpp errors.hpp image_header.hpp
operator_producer.o: operator_filter_edge_sobel.hpp
operator_producer.o: operator_transform_intensity_map.hpp
operator_producer.o: operator_producer.hpp
operator_transform_intensity_map.o: operator_transform_intensity_map.hpp
operator_transform_intensity_map.o: operator.hpp wb_defs.hpp
operator_transform_intensity_map.o: data_source_descriptor.hpp histogram.hpp
operator_transform_intensity_map.o: hough.hpp image.hpp errors.hpp
operator_transform_intensity_map.o: image_header.hpp operator_utils.hpp
operator_transform_intensity_map.o: wb_utils.hpp
operator_utils.o: errors.hpp wb_defs.hpp wb_utils.hpp
operator_utils.o: data_source_descriptor.hpp histogram.hpp hough.hpp
operator_utils.o: image.hpp image_header.hpp operator_utils.hpp
parse_experiment_json.o: file_utils.hpp image.hpp errors.hpp image_header.hpp
parse_experiment_json.o: wb_defs.hpp experiment.hpp histogram.hpp hough.hpp
parse_experiment_json.o: experiment_step.hpp data_source_descriptor.hpp
parse_experiment_json.o: wb_json_utils.hpp
tokens.o: file_utils.hpp
wb_json_utils.o: wb_json_utils.hpp errors.hpp
wb_utils.o: image.hpp errors.hpp image_header.hpp wb_defs.hpp wb_utils.hpp
wb_utils.o: data_source_descriptor.hpp histogram.hpp hough.hpp
