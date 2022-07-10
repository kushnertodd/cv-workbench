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
  bounds.o \
  data_source_descriptor.o \
  errors.o \
  experiment.o \
  experiment_step.o \
  experiment_step_data_source_descriptor.o \
  file_utils.o \
  filesystem_data_source_descriptor.o \
  histogram.o \
  hough.o \
  hough_accum.o \
  image.o \
  image_header.o \
  internet_data_source_descriptor.o \
  kernel.o \
  line_segment.o \
  operator.o \
  operator_filter_edge_kirsch.o \
  operator_filter_edge_prewitt.o \
  operator_filter_edge_roberts.o \
  operator_filter_edge_sobel.o \
  operator_dispatcher.o \
  operator_transform_intensity_map.o \
  operator_utils.o \
  point.o \
  polar_line.o \
  variance_stats.o \
  wb_json_utils.o \
  wb_utils.o 

PROGRAMS = \
  djpeginfo \
  gen-trig \
  image-create \
  image-dump \
  image-hist \
  image-hough \
  image-info \
  image-stats \
  image-test \
  parse_experiment_json \
  tokens 
  # json_parser_example \

%.o: %.cpp %.hpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# for C files, cannot compile here like this
#%.o: %.c %.h
#	$(CC) $< -o $@ $(CCFLAGS)

all: $(PROGRAMS)

djpeginfo: djpeginfo.o
	$(CC) $< -o $@ $(CCFLAGS)  $(LDFLAGS_JPEG)

gen-trig: gen-trig.o 
	$(CXX) $< -o $@ 

image-create: image-create.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

image-dump: image-dump.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

image-hist: image-hist.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

image-hough: image-hough.o $(SRCOBJS)
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
berkeley_db_data_source_descriptor.o: image.hpp bounds.hpp image_header.hpp
berkeley_db_data_source_descriptor.o: point.hpp
berkeley_db_data_source_descriptor.o: berkeley_db_data_source_descriptor.hpp
berkeley_db_data_source_descriptor.o: histogram.hpp hough.hpp hough_accum.hpp
berkeley_db_data_source_descriptor.o: file_utils.hpp wb_utils.hpp
berkeley_db_data_source_descriptor.o: polar_line.hpp variance_stats.hpp
bounds.o: bounds.hpp
data_source_descriptor.o: wb_utils.hpp data_source_descriptor.hpp wb_defs.hpp
data_source_descriptor.o: image.hpp bounds.hpp errors.hpp image_header.hpp
data_source_descriptor.o: point.hpp
errors.o: errors.hpp
experiment.o: experiment.hpp wb_defs.hpp errors.hpp image.hpp bounds.hpp
experiment.o: image_header.hpp point.hpp histogram.hpp hough.hpp
experiment.o: hough_accum.hpp file_utils.hpp wb_utils.hpp
experiment.o: data_source_descriptor.hpp polar_line.hpp variance_stats.hpp
experiment.o: experiment_step.hpp wb_json_utils.hpp
experiment_step.o: wb_json_utils.hpp errors.hpp data_source_descriptor.hpp
experiment_step.o: wb_defs.hpp image.hpp bounds.hpp image_header.hpp
experiment_step.o: point.hpp experiment_step.hpp histogram.hpp
experiment_step.o: hough.hpp hough_accum.hpp file_utils.hpp wb_utils.hpp
experiment_step.o: polar_line.hpp variance_stats.hpp
experiment_step.o: berkeley_db_data_source_descriptor.hpp
experiment_step.o: experiment_step_data_source_descriptor.hpp
experiment_step.o: filesystem_data_source_descriptor.hpp
experiment_step.o: internet_data_source_descriptor.hpp operator.hpp
experiment_step.o: operator_dispatcher.hpp
experiment_step_data_source_descriptor.o: wb_json_utils.hpp errors.hpp
experiment_step_data_source_descriptor.o: data_source_descriptor.hpp
experiment_step_data_source_descriptor.o: wb_defs.hpp image.hpp bounds.hpp
experiment_step_data_source_descriptor.o: image_header.hpp point.hpp
experiment_step_data_source_descriptor.o: experiment_step_data_source_descriptor.hpp
experiment_step_data_source_descriptor.o: histogram.hpp hough.hpp
experiment_step_data_source_descriptor.o: hough_accum.hpp file_utils.hpp
experiment_step_data_source_descriptor.o: wb_utils.hpp polar_line.hpp
experiment_step_data_source_descriptor.o: variance_stats.hpp
filesystem_data_source_descriptor.o: wb_json_utils.hpp errors.hpp
filesystem_data_source_descriptor.o: wb_utils.hpp data_source_descriptor.hpp
filesystem_data_source_descriptor.o: wb_defs.hpp image.hpp bounds.hpp
filesystem_data_source_descriptor.o: image_header.hpp point.hpp
filesystem_data_source_descriptor.o: filesystem_data_source_descriptor.hpp
filesystem_data_source_descriptor.o: histogram.hpp hough.hpp hough_accum.hpp
filesystem_data_source_descriptor.o: file_utils.hpp polar_line.hpp
filesystem_data_source_descriptor.o: variance_stats.hpp
file_utils.o: file_utils.hpp
histogram.o: Histogram.hpp
hough_accum.o: image.hpp bounds.hpp errors.hpp image_header.hpp wb_defs.hpp
hough_accum.o: point.hpp polar_line.hpp hough_accum.hpp file_utils.hpp
hough_accum.o: wb_utils.hpp data_source_descriptor.hpp variance_stats.hpp
hough.o: errors.hpp file_utils.hpp wb_utils.hpp data_source_descriptor.hpp
hough.o: wb_defs.hpp image.hpp bounds.hpp image_header.hpp point.hpp
hough.o: hough_accum.hpp polar_line.hpp variance_stats.hpp hough.hpp
hough_trig_alt.o: hough_trig_alt.hpp
image.o: /usr/include/jpeglib.h /usr/include/jmorecfg.h image.hpp bounds.hpp
image.o: errors.hpp image_header.hpp wb_defs.hpp point.hpp wb_utils.hpp
image.o: data_source_descriptor.hpp
image-create.o: errors.hpp image.hpp bounds.hpp image_header.hpp wb_defs.hpp
image-create.o: point.hpp wb_utils.hpp data_source_descriptor.hpp
image-create.o: file_utils.hpp hough_accum.hpp polar_line.hpp
image-create.o: variance_stats.hpp
image-dump.o: hough_accum.hpp errors.hpp file_utils.hpp wb_utils.hpp
image-dump.o: data_source_descriptor.hpp wb_defs.hpp image.hpp bounds.hpp
image-dump.o: image_header.hpp point.hpp polar_line.hpp
image-dump.o: variance_stats.hpp
image_header.o: file_utils.hpp wb_utils.hpp data_source_descriptor.hpp
image_header.o: wb_defs.hpp image.hpp bounds.hpp errors.hpp image_header.hpp
image_header.o: point.hpp
image-hist.o: variance_stats.hpp bounds.hpp hough_accum.hpp errors.hpp
image-hist.o: file_utils.hpp wb_utils.hpp data_source_descriptor.hpp
image-hist.o: wb_defs.hpp image.hpp image_header.hpp point.hpp
image-hist.o: polar_line.hpp
image-hough.o: errors.hpp hough.hpp hough_accum.hpp file_utils.hpp
image-hough.o: wb_utils.hpp data_source_descriptor.hpp wb_defs.hpp image.hpp
image-hough.o: bounds.hpp image_header.hpp point.hpp polar_line.hpp
image-hough.o: variance_stats.hpp
image-info.o: hough_accum.hpp errors.hpp file_utils.hpp wb_utils.hpp
image-info.o: data_source_descriptor.hpp wb_defs.hpp image.hpp bounds.hpp
image-info.o: image_header.hpp point.hpp polar_line.hpp
image-info.o: variance_stats.hpp
point.o: hough_accum.hpp errors.hpp file_utils.hpp wb_utils.hpp
point.o: data_source_descriptor.hpp wb_defs.hpp image.hpp bounds.hpp
point.o: image_header.hpp point.hpp polar_line.hpp
point.o: variance_stats.hpp
image_point_list.o: image_point_list.hpp point.hpp
image-stats.o: variance_stats.hpp bounds.hpp hough_accum.hpp errors.hpp
image-stats.o: file_utils.hpp wb_utils.hpp data_source_descriptor.hpp
image-stats.o: wb_defs.hpp image.hpp image_header.hpp point.hpp
image-stats.o: polar_line.hpp
image-test.o: errors.hpp image.hpp bounds.hpp image_header.hpp wb_defs.hpp
image-test.o: point.hpp hough_accum.hpp file_utils.hpp wb_utils.hpp
image-test.o: data_source_descriptor.hpp polar_line.hpp variance_stats.hpp
internet_data_source_descriptor.o: wb_json_utils.hpp errors.hpp
internet_data_source_descriptor.o: data_source_descriptor.hpp wb_defs.hpp
internet_data_source_descriptor.o: image.hpp bounds.hpp image_header.hpp
internet_data_source_descriptor.o: point.hpp
internet_data_source_descriptor.o: internet_data_source_descriptor.hpp
internet_data_source_descriptor.o: histogram.hpp hough.hpp hough_accum.hpp
internet_data_source_descriptor.o: file_utils.hpp wb_utils.hpp polar_line.hpp
internet_data_source_descriptor.o: variance_stats.hpp
kernel.o: wb_utils.hpp data_source_descriptor.hpp wb_defs.hpp image.hpp
kernel.o: bounds.hpp errors.hpp image_header.hpp point.hpp kernel.hpp
operator.o: operator.hpp wb_defs.hpp data_source_descriptor.hpp image.hpp
operator.o: bounds.hpp errors.hpp image_header.hpp point.hpp
operator_dispatcher.o: operator_filter_edge_kirsch.hpp wb_defs.hpp
operator_dispatcher.o: operator.hpp data_source_descriptor.hpp image.hpp
operator_dispatcher.o: bounds.hpp errors.hpp image_header.hpp point.hpp
operator_dispatcher.o: operator_filter_edge_prewitt.hpp
operator_dispatcher.o: operator_filter_edge_roberts.hpp
operator_dispatcher.o: operator_filter_edge_sobel.hpp
operator_dispatcher.o: operator_transform_intensity_map.hpp
operator_dispatcher.o: operator_dispatcher.hpp
operator_filter_edge_kirsch.o: kernel.hpp image.hpp bounds.hpp errors.hpp
operator_filter_edge_kirsch.o: image_header.hpp wb_defs.hpp point.hpp
operator_filter_edge_kirsch.o: operator_utils.hpp
operator_filter_edge_kirsch.o: operator_filter_edge_kirsch.hpp operator.hpp
operator_filter_edge_kirsch.o: data_source_descriptor.hpp
operator_filter_edge_prewitt.o: kernel.hpp image.hpp bounds.hpp errors.hpp
operator_filter_edge_prewitt.o: image_header.hpp wb_defs.hpp point.hpp
operator_filter_edge_prewitt.o: operator_utils.hpp
operator_filter_edge_prewitt.o: operator_filter_edge_prewitt.hpp operator.hpp
operator_filter_edge_prewitt.o: data_source_descriptor.hpp
operator_filter_edge_roberts.o: kernel.hpp image.hpp bounds.hpp errors.hpp
operator_filter_edge_roberts.o: image_header.hpp wb_defs.hpp point.hpp
operator_filter_edge_roberts.o: operator_utils.hpp
operator_filter_edge_roberts.o: operator_filter_edge_roberts.hpp operator.hpp
operator_filter_edge_roberts.o: data_source_descriptor.hpp
operator_filter_edge_sobel.o: kernel.hpp image.hpp bounds.hpp errors.hpp
operator_filter_edge_sobel.o: image_header.hpp wb_defs.hpp point.hpp
operator_filter_edge_sobel.o: operator_utils.hpp
operator_filter_edge_sobel.o: operator_filter_edge_sobel.hpp operator.hpp
operator_filter_edge_sobel.o: data_source_descriptor.hpp
operator_transform_intensity_map.o: operator_transform_intensity_map.hpp
operator_transform_intensity_map.o: operator.hpp wb_defs.hpp
operator_transform_intensity_map.o: data_source_descriptor.hpp image.hpp
operator_transform_intensity_map.o: bounds.hpp errors.hpp image_header.hpp
operator_transform_intensity_map.o: point.hpp operator_utils.hpp
operator_transform_intensity_map.o: wb_utils.hpp
operator_utils.o: errors.hpp wb_defs.hpp wb_utils.hpp
operator_utils.o: data_source_descriptor.hpp image.hpp bounds.hpp
operator_utils.o: image_header.hpp point.hpp operator_utils.hpp
parse_experiment_json.o: file_utils.hpp image.hpp bounds.hpp errors.hpp
parse_experiment_json.o: image_header.hpp wb_defs.hpp point.hpp
parse_experiment_json.o: experiment.hpp histogram.hpp hough.hpp
parse_experiment_json.o: hough_accum.hpp wb_utils.hpp
parse_experiment_json.o: data_source_descriptor.hpp polar_line.hpp
parse_experiment_json.o: variance_stats.hpp experiment_step.hpp
parse_experiment_json.o: wb_json_utils.hpp
polar_line.o: hough_accum.hpp errors.hpp file_utils.hpp wb_utils.hpp
polar_line.o: data_source_descriptor.hpp wb_defs.hpp image.hpp bounds.hpp
polar_line.o: image_header.hpp point.hpp polar_line.hpp
polar_line.o: variance_stats.hpp
tokens.o: file_utils.hpp
variance_stats.o: variance_stats.hpp bounds.hpp
wb_json_utils.o: wb_json_utils.hpp errors.hpp
wb_utils.o: wb_defs.hpp wb_utils.hpp data_source_descriptor.hpp image.hpp
wb_utils.o: bounds.hpp errors.hpp image_header.hpp point.hpp
