CXX=g++
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
  operator_hough_accumulator_create.o \
  operator_hough_draw_line.o \
  operator_transform_intensity_map.o \
  operator_utils.o \
  point.o \
  polar_line.o \
  variance_stats.o \
  wb_json_utils.o \
  wb_utils.o 

PROGRAMS = \
  image-create \
  image-dump \
  image-hist \
  image-hough \
  image-info \
  image-polar \
  image-stats \
  image-test \
  cv-workbench \ 

%.o: %.cpp %.hpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

all: $(PROGRAMS)

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

image-polar: image-polar.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

image-stats: image-stats.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

image-test: image-test.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

cv-workbench : cv-workbench .o $(SRCOBJS)
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
berkeley_db_data_source_descriptor.o: data_source_descriptor.hpp hough.hpp
berkeley_db_data_source_descriptor.o: hough_accum.hpp file_utils.hpp
berkeley_db_data_source_descriptor.o: image.hpp bounds.hpp histogram.hpp
berkeley_db_data_source_descriptor.o: variance_stats.hpp image_header.hpp
berkeley_db_data_source_descriptor.o: wb_defs.hpp line_segment.hpp point.hpp
berkeley_db_data_source_descriptor.o: wb_utils.hpp polar_line.hpp
berkeley_db_data_source_descriptor.o: berkeley_db_data_source_descriptor.hpp
bounds.o: bounds.hpp
cv-workbench.o: file_utils.hpp image.hpp bounds.hpp errors.hpp histogram.hpp
cv-workbench.o: variance_stats.hpp image_header.hpp wb_defs.hpp
cv-workbench.o: line_segment.hpp point.hpp experiment.hpp hough.hpp
cv-workbench.o: hough_accum.hpp wb_utils.hpp polar_line.hpp
cv-workbench.o: experiment_step.hpp data_source_descriptor.hpp
cv-workbench.o: wb_json_utils.hpp
data_source_descriptor.o: wb_utils.hpp errors.hpp wb_defs.hpp
data_source_descriptor.o: data_source_descriptor.hpp hough.hpp
data_source_descriptor.o: hough_accum.hpp file_utils.hpp image.hpp bounds.hpp
data_source_descriptor.o: histogram.hpp variance_stats.hpp image_header.hpp
data_source_descriptor.o: line_segment.hpp point.hpp polar_line.hpp
errors.o: errors.hpp
experiment.o: experiment.hpp wb_defs.hpp errors.hpp image.hpp bounds.hpp
experiment.o: histogram.hpp variance_stats.hpp image_header.hpp
experiment.o: line_segment.hpp point.hpp hough.hpp hough_accum.hpp
experiment.o: file_utils.hpp wb_utils.hpp polar_line.hpp experiment_step.hpp
experiment.o: data_source_descriptor.hpp wb_json_utils.hpp
experiment_step.o: wb_json_utils.hpp errors.hpp data_source_descriptor.hpp
experiment_step.o: hough.hpp hough_accum.hpp file_utils.hpp image.hpp
experiment_step.o: bounds.hpp histogram.hpp variance_stats.hpp
experiment_step.o: image_header.hpp wb_defs.hpp line_segment.hpp point.hpp
experiment_step.o: wb_utils.hpp polar_line.hpp experiment_step.hpp
experiment_step.o: berkeley_db_data_source_descriptor.hpp
experiment_step.o: experiment_step_data_source_descriptor.hpp
experiment_step.o: filesystem_data_source_descriptor.hpp
experiment_step.o: internet_data_source_descriptor.hpp operator.hpp
experiment_step.o: operator_dispatcher.hpp
experiment_step_data_source_descriptor.o: wb_json_utils.hpp errors.hpp
experiment_step_data_source_descriptor.o: data_source_descriptor.hpp
experiment_step_data_source_descriptor.o: hough.hpp hough_accum.hpp
experiment_step_data_source_descriptor.o: file_utils.hpp image.hpp bounds.hpp
experiment_step_data_source_descriptor.o: histogram.hpp variance_stats.hpp
experiment_step_data_source_descriptor.o: image_header.hpp wb_defs.hpp
experiment_step_data_source_descriptor.o: line_segment.hpp point.hpp
experiment_step_data_source_descriptor.o: wb_utils.hpp polar_line.hpp
experiment_step_data_source_descriptor.o: experiment_step_data_source_descriptor.hpp
filesystem_data_source_descriptor.o: wb_json_utils.hpp errors.hpp
filesystem_data_source_descriptor.o: wb_utils.hpp wb_defs.hpp
filesystem_data_source_descriptor.o: data_source_descriptor.hpp hough.hpp
filesystem_data_source_descriptor.o: hough_accum.hpp file_utils.hpp image.hpp
filesystem_data_source_descriptor.o: bounds.hpp histogram.hpp
filesystem_data_source_descriptor.o: variance_stats.hpp image_header.hpp
filesystem_data_source_descriptor.o: line_segment.hpp point.hpp
filesystem_data_source_descriptor.o: polar_line.hpp
filesystem_data_source_descriptor.o: filesystem_data_source_descriptor.hpp
file_utils.o: file_utils.hpp
histogram.o: errors.hpp file_utils.hpp wb_utils.hpp wb_defs.hpp histogram.hpp
histogram.o: variance_stats.hpp bounds.hpp
hough_accum.o: image.hpp bounds.hpp errors.hpp histogram.hpp
hough_accum.o: variance_stats.hpp image_header.hpp wb_defs.hpp
hough_accum.o: line_segment.hpp point.hpp polar_line.hpp hough_accum.hpp
hough_accum.o: file_utils.hpp wb_utils.hpp
hough.o: errors.hpp file_utils.hpp wb_utils.hpp wb_defs.hpp hough_accum.hpp
hough.o: image.hpp bounds.hpp histogram.hpp variance_stats.hpp
hough.o: image_header.hpp line_segment.hpp point.hpp polar_line.hpp hough.hpp
image.o: /usr/include/jpeglib.h /usr/include/jmorecfg.h image.hpp bounds.hpp
image.o: errors.hpp histogram.hpp variance_stats.hpp image_header.hpp
image.o: wb_defs.hpp line_segment.hpp point.hpp wb_utils.hpp
image-create.o: errors.hpp image.hpp bounds.hpp histogram.hpp
image-create.o: variance_stats.hpp image_header.hpp wb_defs.hpp
image-create.o: line_segment.hpp point.hpp wb_utils.hpp file_utils.hpp
image-create.o: hough_accum.hpp polar_line.hpp
image-dump.o: hough_accum.hpp errors.hpp file_utils.hpp image.hpp bounds.hpp
image-dump.o: histogram.hpp variance_stats.hpp image_header.hpp wb_defs.hpp
image-dump.o: line_segment.hpp point.hpp wb_utils.hpp polar_line.hpp
image_header.o: file_utils.hpp wb_utils.hpp errors.hpp wb_defs.hpp
image_header.o: image_header.hpp
image-hist.o: variance_stats.hpp errors.hpp bounds.hpp hough_accum.hpp
image-hist.o: file_utils.hpp image.hpp histogram.hpp image_header.hpp
image-hist.o: wb_defs.hpp line_segment.hpp point.hpp wb_utils.hpp
image-hist.o: polar_line.hpp
image-hough.o: errors.hpp histogram.hpp variance_stats.hpp bounds.hpp
image-hough.o: hough.hpp hough_accum.hpp file_utils.hpp image.hpp
image-hough.o: image_header.hpp wb_defs.hpp line_segment.hpp point.hpp
image-hough.o: wb_utils.hpp polar_line.hpp
image-info.o: hough_accum.hpp errors.hpp file_utils.hpp image.hpp bounds.hpp
image-info.o: histogram.hpp variance_stats.hpp image_header.hpp wb_defs.hpp
image-info.o: line_segment.hpp point.hpp wb_utils.hpp polar_line.hpp
image_point_list.o: image_point_list.hpp point.hpp
image-polar.o: errors.hpp histogram.hpp variance_stats.hpp bounds.hpp
image-polar.o: hough.hpp hough_accum.hpp file_utils.hpp image.hpp
image-polar.o: image_header.hpp wb_defs.hpp line_segment.hpp point.hpp
image-polar.o: wb_utils.hpp polar_line.hpp
image-stats.o: variance_stats.hpp errors.hpp bounds.hpp hough_accum.hpp
image-stats.o: file_utils.hpp image.hpp histogram.hpp image_header.hpp
image-stats.o: wb_defs.hpp line_segment.hpp point.hpp wb_utils.hpp
image-stats.o: polar_line.hpp
image-test.o: errors.hpp image.hpp bounds.hpp histogram.hpp
image-test.o: variance_stats.hpp image_header.hpp wb_defs.hpp
image-test.o: line_segment.hpp point.hpp hough_accum.hpp file_utils.hpp
image-test.o: wb_utils.hpp polar_line.hpp
internet_data_source_descriptor.o: wb_json_utils.hpp errors.hpp
internet_data_source_descriptor.o: data_source_descriptor.hpp hough.hpp
internet_data_source_descriptor.o: hough_accum.hpp file_utils.hpp image.hpp
internet_data_source_descriptor.o: bounds.hpp histogram.hpp
internet_data_source_descriptor.o: variance_stats.hpp image_header.hpp
internet_data_source_descriptor.o: wb_defs.hpp line_segment.hpp point.hpp
internet_data_source_descriptor.o: wb_utils.hpp polar_line.hpp
internet_data_source_descriptor.o: internet_data_source_descriptor.hpp
kernel.o: wb_utils.hpp errors.hpp wb_defs.hpp kernel.hpp image.hpp bounds.hpp
kernel.o: histogram.hpp variance_stats.hpp image_header.hpp line_segment.hpp
kernel.o: point.hpp
line_segment.o: line_segment.hpp point.hpp
operator_dispatcher.o: operator_filter_edge_kirsch.hpp wb_defs.hpp
operator_dispatcher.o: operator.hpp data_source_descriptor.hpp hough.hpp
operator_dispatcher.o: errors.hpp hough_accum.hpp file_utils.hpp image.hpp
operator_dispatcher.o: bounds.hpp histogram.hpp variance_stats.hpp
operator_dispatcher.o: image_header.hpp line_segment.hpp point.hpp
operator_dispatcher.o: wb_utils.hpp polar_line.hpp
operator_dispatcher.o: operator_filter_edge_prewitt.hpp
operator_dispatcher.o: operator_filter_edge_roberts.hpp
operator_dispatcher.o: operator_filter_edge_sobel.hpp
operator_dispatcher.o: operator_transform_intensity_map.hpp
operator_dispatcher.o: operator_hough_accumulator_create.hpp
operator_dispatcher.o: operator_hough_draw_line.hpp operator_dispatcher.hpp
operator_filter_edge_kirsch.o: kernel.hpp image.hpp bounds.hpp errors.hpp
operator_filter_edge_kirsch.o: histogram.hpp variance_stats.hpp
operator_filter_edge_kirsch.o: image_header.hpp wb_defs.hpp line_segment.hpp
operator_filter_edge_kirsch.o: point.hpp operator_utils.hpp
operator_filter_edge_kirsch.o: operator_filter_edge_kirsch.hpp operator.hpp
operator_filter_edge_kirsch.o: data_source_descriptor.hpp hough.hpp
operator_filter_edge_kirsch.o: hough_accum.hpp file_utils.hpp wb_utils.hpp
operator_filter_edge_kirsch.o: polar_line.hpp
operator_filter_edge_prewitt.o: kernel.hpp image.hpp bounds.hpp errors.hpp
operator_filter_edge_prewitt.o: histogram.hpp variance_stats.hpp
operator_filter_edge_prewitt.o: image_header.hpp wb_defs.hpp line_segment.hpp
operator_filter_edge_prewitt.o: point.hpp operator_utils.hpp
operator_filter_edge_prewitt.o: operator_filter_edge_prewitt.hpp operator.hpp
operator_filter_edge_prewitt.o: data_source_descriptor.hpp hough.hpp
operator_filter_edge_prewitt.o: hough_accum.hpp file_utils.hpp wb_utils.hpp
operator_filter_edge_prewitt.o: polar_line.hpp
operator_filter_edge_roberts.o: kernel.hpp image.hpp bounds.hpp errors.hpp
operator_filter_edge_roberts.o: histogram.hpp variance_stats.hpp
operator_filter_edge_roberts.o: image_header.hpp wb_defs.hpp line_segment.hpp
operator_filter_edge_roberts.o: point.hpp operator_utils.hpp
operator_filter_edge_roberts.o: operator_filter_edge_roberts.hpp operator.hpp
operator_filter_edge_roberts.o: data_source_descriptor.hpp hough.hpp
operator_filter_edge_roberts.o: hough_accum.hpp file_utils.hpp wb_utils.hpp
operator_filter_edge_roberts.o: polar_line.hpp
operator_filter_edge_sobel.o: kernel.hpp image.hpp bounds.hpp errors.hpp
operator_filter_edge_sobel.o: histogram.hpp variance_stats.hpp
operator_filter_edge_sobel.o: image_header.hpp wb_defs.hpp line_segment.hpp
operator_filter_edge_sobel.o: point.hpp operator_utils.hpp
operator_filter_edge_sobel.o: operator_filter_edge_sobel.hpp operator.hpp
operator_filter_edge_sobel.o: data_source_descriptor.hpp hough.hpp
operator_filter_edge_sobel.o: hough_accum.hpp file_utils.hpp wb_utils.hpp
operator_filter_edge_sobel.o: polar_line.hpp
operator_hough_accumulator_create.o: hough.hpp errors.hpp hough_accum.hpp
operator_hough_accumulator_create.o: file_utils.hpp image.hpp bounds.hpp
operator_hough_accumulator_create.o: histogram.hpp variance_stats.hpp
operator_hough_accumulator_create.o: image_header.hpp wb_defs.hpp
operator_hough_accumulator_create.o: line_segment.hpp point.hpp wb_utils.hpp
operator_hough_accumulator_create.o: polar_line.hpp operator_utils.hpp
operator_hough_accumulator_create.o: operator_hough_accumulator_create.hpp
operator_hough_accumulator_create.o: operator.hpp data_source_descriptor.hpp
operator_hough_draw_line.o: hough.hpp errors.hpp hough_accum.hpp
operator_hough_draw_line.o: file_utils.hpp image.hpp bounds.hpp histogram.hpp
operator_hough_draw_line.o: variance_stats.hpp image_header.hpp wb_defs.hpp
operator_hough_draw_line.o: line_segment.hpp point.hpp wb_utils.hpp
operator_hough_draw_line.o: polar_line.hpp operator_utils.hpp
operator_hough_draw_line.o: operator_hough_draw_line.hpp operator.hpp
operator_hough_draw_line.o: data_source_descriptor.hpp
operator_transform_intensity_map.o: operator_transform_intensity_map.hpp
operator_transform_intensity_map.o: operator.hpp wb_defs.hpp
operator_transform_intensity_map.o: data_source_descriptor.hpp hough.hpp
operator_transform_intensity_map.o: errors.hpp hough_accum.hpp file_utils.hpp
operator_transform_intensity_map.o: image.hpp bounds.hpp histogram.hpp
operator_transform_intensity_map.o: variance_stats.hpp image_header.hpp
operator_transform_intensity_map.o: line_segment.hpp point.hpp wb_utils.hpp
operator_transform_intensity_map.o: polar_line.hpp operator_utils.hpp
operator_utils.o: errors.hpp wb_defs.hpp wb_utils.hpp operator_utils.hpp
point.o: point.hpp
polar_line.o: polar_line.hpp point.hpp
variance_stats.o: wb_utils.hpp errors.hpp wb_defs.hpp variance_stats.hpp
variance_stats.o: bounds.hpp
wb_json_utils.o: wb_json_utils.hpp errors.hpp
wb_utils.o: errors.hpp wb_defs.hpp wb_utils.hpp
