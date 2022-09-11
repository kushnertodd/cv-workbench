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
LDFLAGS_JSON = -static -ljson-c
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
  filesystem_data_source_descriptor.o \
  file_utils.o \
  histogram.o \
  hough.o \
  hough_accum.o \
  hough_peak.o \
  image_header.o \
  image.o \
  internet_data_source_descriptor.o \
  kernel.o \
  line_segment.o \
  morphology.o \
  one_pass_mean.o \
  operator_dispatcher.o \
  operator_filter_edge_kirsch.o \
  operator_filter_edge_laplacian.o \
  operator_filter_edge_prewitt.o \
  operator_filter_edge_roberts.o \
  operator_filter_edge_sobel.o \
  operator_filter_image_morphology.o \
  operator_filter_smooth_average.o \
  operator_filter_smooth_gaussian.o \
  operator_filter_smooth_median.o \
  operator_histogram_hough_create.o \
  operator_histogram_image_create.o \
  operator_histogram_peak_detect.o \
  operator_hough_draw_line.o \
  operator_hough_image_create.o \
  operator_hough_peak_detect.o \
  operator.o \
  operator_transform_image_combine.o \
  operator_transform_image_copy.o \
  operator_transform_image_create.o \
  operator_transform_intensity_map.o \
  operator_utils.o \
  pearsons_correlation.o \
  point.o \
  polar_line.o \
  polar_trig.o \
  runtime.o \
  variance_stats.o \
  wb_data_format.o \
  wb_data_type.o \
  wb_filename.o \
  wb_image_depth.o \
  wb_json_utils.o \
  wb_log.o \
  wb_morphology_types.o \
  wb_repository_type.o \
  wb_utils.o \
  wb_window.o

PROGRAMS = \
  cv-workbench
#  image-copy \
#  image-corr \
#  image-dump \
#  image-info \
#  image-map \
#  image-mean \
#  image-morph \
#  image-read \
#  image-trig \

%.o: %.cpp %.hpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

all: $(PROGRAMS)

# image-copy: image-copy.o $(SRCOBJS)
# 	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)
# 
# image-corr: image-corr.o $(SRCOBJS)
# 	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)
# 
# image-dump: image-dump.o $(SRCOBJS)
# 	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)
# 
# image-info: image-info.o $(SRCOBJS)
# 	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)
# 
# image-map: image-map.o $(SRCOBJS)
# 	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)
# 
# image-mean: image-mean.o $(SRCOBJS)
# 	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)
# 
# image-morph: image-morph.o $(SRCOBJS)
# 	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)
#
# image-read: image-read.o $(SRCOBJS)
# 	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

cv-workbench : cv-workbench.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

objs:
	@echo $(OBJS)

clean:
	rm -f $(OBJS)

clobber: 
	rm -f $(OBJS) $(PROGRAMS)

install:
	cp $(PROGRAMS) `which jpegtran` ~/bin

doc:
	doxygen doxygen.config

depend:
	makedepend -- $(CXXFLAGS) -- $(SRCFILES)

programs:
	@echo $(PROGRAMS)

# DO NOT DELETE

berkeley_db_data_source_descriptor.o: wb_data_format.hpp wb_data_type.hpp
berkeley_db_data_source_descriptor.o: wb_repository_type.hpp
berkeley_db_data_source_descriptor.o: wb_json_utils.hpp
berkeley_db_data_source_descriptor.o: /usr/include/json-c/json.h
berkeley_db_data_source_descriptor.o: /usr/include/json-c/arraylist.h
berkeley_db_data_source_descriptor.o: /usr/include/json-c/debug.h
berkeley_db_data_source_descriptor.o: /usr/include/stdlib.h
berkeley_db_data_source_descriptor.o: /usr/include/json-c/json_c_version.h
berkeley_db_data_source_descriptor.o: /usr/include/json-c/json_object.h
berkeley_db_data_source_descriptor.o: /usr/include/json-c/json_inttypes.h
berkeley_db_data_source_descriptor.o: /usr/include/json-c/json_config.h
berkeley_db_data_source_descriptor.o: /usr/include/inttypes.h
berkeley_db_data_source_descriptor.o: /usr/include/features.h
berkeley_db_data_source_descriptor.o: /usr/include/stdc-predef.h
berkeley_db_data_source_descriptor.o: /usr/include/stdint.h
berkeley_db_data_source_descriptor.o: /usr/include/json-c/json_types.h
berkeley_db_data_source_descriptor.o: /usr/include/json-c/printbuf.h
berkeley_db_data_source_descriptor.o: /usr/include/json-c/json_object_iterator.h
berkeley_db_data_source_descriptor.o: /usr/include/json-c/json_pointer.h
berkeley_db_data_source_descriptor.o: /usr/include/json-c/json_tokener.h
berkeley_db_data_source_descriptor.o: /usr/include/json-c/json_util.h
berkeley_db_data_source_descriptor.o: /usr/include/json-c/linkhash.h
berkeley_db_data_source_descriptor.o: errors.hpp data_source_descriptor.hpp
berkeley_db_data_source_descriptor.o: wb_defs.hpp histogram.hpp hough.hpp
berkeley_db_data_source_descriptor.o: hough_accum.hpp hough_peak.hpp
berkeley_db_data_source_descriptor.o: polar_line.hpp variance_stats.hpp
berkeley_db_data_source_descriptor.o: bounds.hpp file_utils.hpp image.hpp
berkeley_db_data_source_descriptor.o: image_header.hpp wb_image_depth.hpp
berkeley_db_data_source_descriptor.o: line_segment.hpp point.hpp wb_log.hpp
berkeley_db_data_source_descriptor.o: polar_trig.hpp wb_utils.hpp
berkeley_db_data_source_descriptor.o: wb_filename.hpp
berkeley_db_data_source_descriptor.o: berkeley_db_data_source_descriptor.hpp
bounds.o: bounds.hpp
cv-workbench.o: /usr/include/json-c/json.h /usr/include/json-c/arraylist.h
cv-workbench.o: /usr/include/json-c/debug.h /usr/include/stdlib.h
cv-workbench.o: /usr/include/json-c/json_c_version.h
cv-workbench.o: /usr/include/json-c/json_object.h
cv-workbench.o: /usr/include/json-c/json_inttypes.h
cv-workbench.o: /usr/include/json-c/json_config.h /usr/include/inttypes.h
cv-workbench.o: /usr/include/features.h /usr/include/stdc-predef.h
cv-workbench.o: /usr/include/stdint.h /usr/include/json-c/json_types.h
cv-workbench.o: /usr/include/json-c/printbuf.h
cv-workbench.o: /usr/include/json-c/json_object_iterator.h
cv-workbench.o: /usr/include/json-c/json_pointer.h
cv-workbench.o: /usr/include/json-c/json_tokener.h
cv-workbench.o: /usr/include/json-c/json_util.h
cv-workbench.o: /usr/include/json-c/linkhash.h wb_log.hpp errors.hpp
cv-workbench.o: experiment.hpp wb_defs.hpp image.hpp bounds.hpp
cv-workbench.o: image_header.hpp wb_data_format.hpp wb_data_type.hpp
cv-workbench.o: wb_image_depth.hpp wb_repository_type.hpp line_segment.hpp
cv-workbench.o: point.hpp variance_stats.hpp histogram.hpp hough.hpp
cv-workbench.o: hough_accum.hpp hough_peak.hpp polar_line.hpp file_utils.hpp
cv-workbench.o: polar_trig.hpp wb_utils.hpp wb_filename.hpp
cv-workbench.o: experiment_step.hpp data_source_descriptor.hpp
cv-workbench.o: wb_json_utils.hpp runtime.hpp
data_source_descriptor.o: berkeley_db_data_source_descriptor.hpp
data_source_descriptor.o: /usr/include/json-c/json.h
data_source_descriptor.o: /usr/include/json-c/arraylist.h
data_source_descriptor.o: /usr/include/json-c/debug.h /usr/include/stdlib.h
data_source_descriptor.o: /usr/include/json-c/json_c_version.h
data_source_descriptor.o: /usr/include/json-c/json_object.h
data_source_descriptor.o: /usr/include/json-c/json_inttypes.h
data_source_descriptor.o: /usr/include/json-c/json_config.h
data_source_descriptor.o: /usr/include/inttypes.h /usr/include/features.h
data_source_descriptor.o: /usr/include/stdc-predef.h /usr/include/stdint.h
data_source_descriptor.o: /usr/include/json-c/json_types.h
data_source_descriptor.o: /usr/include/json-c/printbuf.h
data_source_descriptor.o: /usr/include/json-c/json_object_iterator.h
data_source_descriptor.o: /usr/include/json-c/json_pointer.h
data_source_descriptor.o: /usr/include/json-c/json_tokener.h
data_source_descriptor.o: /usr/include/json-c/json_util.h
data_source_descriptor.o: /usr/include/json-c/linkhash.h wb_image_depth.hpp
data_source_descriptor.o: data_source_descriptor.hpp wb_defs.hpp
data_source_descriptor.o: histogram.hpp errors.hpp hough.hpp hough_accum.hpp
data_source_descriptor.o: hough_peak.hpp polar_line.hpp variance_stats.hpp
data_source_descriptor.o: bounds.hpp file_utils.hpp image.hpp
data_source_descriptor.o: image_header.hpp wb_data_format.hpp
data_source_descriptor.o: wb_data_type.hpp wb_repository_type.hpp
data_source_descriptor.o: line_segment.hpp point.hpp wb_log.hpp
data_source_descriptor.o: polar_trig.hpp wb_utils.hpp wb_filename.hpp
data_source_descriptor.o: filesystem_data_source_descriptor.hpp
data_source_descriptor.o: internet_data_source_descriptor.hpp
data_source_descriptor.o: wb_json_utils.hpp
errors.o: errors.hpp
experiment.o: runtime.hpp /usr/include/json-c/json.h
experiment.o: /usr/include/json-c/arraylist.h /usr/include/json-c/debug.h
experiment.o: /usr/include/stdlib.h /usr/include/json-c/json_c_version.h
experiment.o: /usr/include/json-c/json_object.h
experiment.o: /usr/include/json-c/json_inttypes.h
experiment.o: /usr/include/json-c/json_config.h /usr/include/inttypes.h
experiment.o: /usr/include/features.h /usr/include/stdc-predef.h
experiment.o: /usr/include/stdint.h /usr/include/json-c/json_types.h
experiment.o: /usr/include/json-c/printbuf.h
experiment.o: /usr/include/json-c/json_object_iterator.h
experiment.o: /usr/include/json-c/json_pointer.h
experiment.o: /usr/include/json-c/json_tokener.h
experiment.o: /usr/include/json-c/json_util.h /usr/include/json-c/linkhash.h
experiment.o: wb_defs.hpp experiment.hpp errors.hpp image.hpp bounds.hpp
experiment.o: image_header.hpp wb_data_format.hpp wb_data_type.hpp
experiment.o: wb_image_depth.hpp wb_repository_type.hpp line_segment.hpp
experiment.o: point.hpp wb_log.hpp variance_stats.hpp histogram.hpp hough.hpp
experiment.o: hough_accum.hpp hough_peak.hpp polar_line.hpp file_utils.hpp
experiment.o: polar_trig.hpp wb_utils.hpp wb_filename.hpp experiment_step.hpp
experiment.o: data_source_descriptor.hpp wb_json_utils.hpp
experiment_step.o: wb_data_type.hpp data_source_descriptor.hpp
experiment_step.o: /usr/include/json-c/json.h /usr/include/json-c/arraylist.h
experiment_step.o: /usr/include/json-c/debug.h /usr/include/stdlib.h
experiment_step.o: /usr/include/json-c/json_c_version.h
experiment_step.o: /usr/include/json-c/json_object.h
experiment_step.o: /usr/include/json-c/json_inttypes.h
experiment_step.o: /usr/include/json-c/json_config.h /usr/include/inttypes.h
experiment_step.o: /usr/include/features.h /usr/include/stdc-predef.h
experiment_step.o: /usr/include/stdint.h /usr/include/json-c/json_types.h
experiment_step.o: /usr/include/json-c/printbuf.h
experiment_step.o: /usr/include/json-c/json_object_iterator.h
experiment_step.o: /usr/include/json-c/json_pointer.h
experiment_step.o: /usr/include/json-c/json_tokener.h
experiment_step.o: /usr/include/json-c/json_util.h
experiment_step.o: /usr/include/json-c/linkhash.h wb_defs.hpp histogram.hpp
experiment_step.o: errors.hpp hough.hpp hough_accum.hpp hough_peak.hpp
experiment_step.o: polar_line.hpp variance_stats.hpp bounds.hpp
experiment_step.o: file_utils.hpp image.hpp image_header.hpp
experiment_step.o: wb_data_format.hpp wb_image_depth.hpp
experiment_step.o: wb_repository_type.hpp line_segment.hpp point.hpp
experiment_step.o: wb_log.hpp polar_trig.hpp wb_utils.hpp wb_filename.hpp
experiment_step.o: experiment_step.hpp operator.hpp operator_dispatcher.hpp
experiment_step.o: wb_json_utils.hpp
filesystem_data_source_descriptor.o: wb_data_format.hpp wb_data_type.hpp
filesystem_data_source_descriptor.o: wb_repository_type.hpp wb_json_utils.hpp
filesystem_data_source_descriptor.o: /usr/include/json-c/json.h
filesystem_data_source_descriptor.o: /usr/include/json-c/arraylist.h
filesystem_data_source_descriptor.o: /usr/include/json-c/debug.h
filesystem_data_source_descriptor.o: /usr/include/stdlib.h
filesystem_data_source_descriptor.o: /usr/include/json-c/json_c_version.h
filesystem_data_source_descriptor.o: /usr/include/json-c/json_object.h
filesystem_data_source_descriptor.o: /usr/include/json-c/json_inttypes.h
filesystem_data_source_descriptor.o: /usr/include/json-c/json_config.h
filesystem_data_source_descriptor.o: /usr/include/inttypes.h
filesystem_data_source_descriptor.o: /usr/include/features.h
filesystem_data_source_descriptor.o: /usr/include/stdc-predef.h
filesystem_data_source_descriptor.o: /usr/include/stdint.h
filesystem_data_source_descriptor.o: /usr/include/json-c/json_types.h
filesystem_data_source_descriptor.o: /usr/include/json-c/printbuf.h
filesystem_data_source_descriptor.o: /usr/include/json-c/json_object_iterator.h
filesystem_data_source_descriptor.o: /usr/include/json-c/json_pointer.h
filesystem_data_source_descriptor.o: /usr/include/json-c/json_tokener.h
filesystem_data_source_descriptor.o: /usr/include/json-c/json_util.h
filesystem_data_source_descriptor.o: /usr/include/json-c/linkhash.h
filesystem_data_source_descriptor.o: errors.hpp data_source_descriptor.hpp
filesystem_data_source_descriptor.o: wb_defs.hpp histogram.hpp hough.hpp
filesystem_data_source_descriptor.o: hough_accum.hpp hough_peak.hpp
filesystem_data_source_descriptor.o: polar_line.hpp variance_stats.hpp
filesystem_data_source_descriptor.o: bounds.hpp file_utils.hpp image.hpp
filesystem_data_source_descriptor.o: image_header.hpp wb_image_depth.hpp
filesystem_data_source_descriptor.o: line_segment.hpp point.hpp wb_log.hpp
filesystem_data_source_descriptor.o: polar_trig.hpp wb_utils.hpp
filesystem_data_source_descriptor.o: wb_filename.hpp
filesystem_data_source_descriptor.o: filesystem_data_source_descriptor.hpp
file_utils.o: file_utils.hpp errors.hpp
histogram.o: errors.hpp file_utils.hpp wb_utils.hpp
histogram.o: /usr/include/json-c/json.h /usr/include/json-c/arraylist.h
histogram.o: /usr/include/json-c/debug.h /usr/include/stdlib.h
histogram.o: /usr/include/json-c/json_c_version.h
histogram.o: /usr/include/json-c/json_object.h
histogram.o: /usr/include/json-c/json_inttypes.h
histogram.o: /usr/include/json-c/json_config.h /usr/include/inttypes.h
histogram.o: /usr/include/features.h /usr/include/stdc-predef.h
histogram.o: /usr/include/stdint.h /usr/include/json-c/json_types.h
histogram.o: /usr/include/json-c/printbuf.h
histogram.o: /usr/include/json-c/json_object_iterator.h
histogram.o: /usr/include/json-c/json_pointer.h
histogram.o: /usr/include/json-c/json_tokener.h
histogram.o: /usr/include/json-c/json_util.h /usr/include/json-c/linkhash.h
histogram.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
histogram.o: wb_repository_type.hpp wb_defs.hpp polar_trig.hpp histogram.hpp
histogram.o: hough.hpp hough_accum.hpp hough_peak.hpp polar_line.hpp
histogram.o: variance_stats.hpp bounds.hpp image.hpp image_header.hpp
histogram.o: line_segment.hpp point.hpp wb_log.hpp wb_filename.hpp
hough_accum.o: image.hpp bounds.hpp errors.hpp image_header.hpp
hough_accum.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
hough_accum.o: wb_repository_type.hpp wb_defs.hpp line_segment.hpp point.hpp
hough_accum.o: wb_log.hpp variance_stats.hpp polar_line.hpp hough_peak.hpp
hough_accum.o: hough_accum.hpp file_utils.hpp polar_trig.hpp wb_utils.hpp
hough_accum.o: /usr/include/json-c/json.h /usr/include/json-c/arraylist.h
hough_accum.o: /usr/include/json-c/debug.h /usr/include/stdlib.h
hough_accum.o: /usr/include/json-c/json_c_version.h
hough_accum.o: /usr/include/json-c/json_object.h
hough_accum.o: /usr/include/json-c/json_inttypes.h
hough_accum.o: /usr/include/json-c/json_config.h /usr/include/inttypes.h
hough_accum.o: /usr/include/features.h /usr/include/stdc-predef.h
hough_accum.o: /usr/include/stdint.h /usr/include/json-c/json_types.h
hough_accum.o: /usr/include/json-c/printbuf.h
hough_accum.o: /usr/include/json-c/json_object_iterator.h
hough_accum.o: /usr/include/json-c/json_pointer.h
hough_accum.o: /usr/include/json-c/json_tokener.h
hough_accum.o: /usr/include/json-c/json_util.h /usr/include/json-c/linkhash.h
hough.o: errors.hpp file_utils.hpp hough_accum.hpp hough_peak.hpp
hough.o: polar_line.hpp variance_stats.hpp bounds.hpp image.hpp
hough.o: image_header.hpp wb_data_format.hpp wb_data_type.hpp
hough.o: wb_image_depth.hpp wb_repository_type.hpp wb_defs.hpp
hough.o: line_segment.hpp point.hpp wb_log.hpp polar_trig.hpp wb_utils.hpp
hough.o: /usr/include/json-c/json.h /usr/include/json-c/arraylist.h
hough.o: /usr/include/json-c/debug.h /usr/include/stdlib.h
hough.o: /usr/include/json-c/json_c_version.h
hough.o: /usr/include/json-c/json_object.h
hough.o: /usr/include/json-c/json_inttypes.h
hough.o: /usr/include/json-c/json_config.h /usr/include/inttypes.h
hough.o: /usr/include/features.h /usr/include/stdc-predef.h
hough.o: /usr/include/stdint.h /usr/include/json-c/json_types.h
hough.o: /usr/include/json-c/printbuf.h
hough.o: /usr/include/json-c/json_object_iterator.h
hough.o: /usr/include/json-c/json_pointer.h
hough.o: /usr/include/json-c/json_tokener.h /usr/include/json-c/json_util.h
hough.o: /usr/include/json-c/linkhash.h wb_window.hpp hough.hpp
hough_peak.o: errors.hpp file_utils.hpp hough_accum.hpp hough_peak.hpp
hough_peak.o: polar_line.hpp variance_stats.hpp bounds.hpp image.hpp
hough_peak.o: image_header.hpp wb_data_format.hpp wb_data_type.hpp
hough_peak.o: wb_image_depth.hpp wb_repository_type.hpp wb_defs.hpp
hough_peak.o: line_segment.hpp point.hpp wb_log.hpp polar_trig.hpp
hough_peak.o: wb_utils.hpp /usr/include/json-c/json.h
hough_peak.o: /usr/include/json-c/arraylist.h /usr/include/json-c/debug.h
hough_peak.o: /usr/include/stdlib.h /usr/include/json-c/json_c_version.h
hough_peak.o: /usr/include/json-c/json_object.h
hough_peak.o: /usr/include/json-c/json_inttypes.h
hough_peak.o: /usr/include/json-c/json_config.h /usr/include/inttypes.h
hough_peak.o: /usr/include/features.h /usr/include/stdc-predef.h
hough_peak.o: /usr/include/stdint.h /usr/include/json-c/json_types.h
hough_peak.o: /usr/include/json-c/printbuf.h
hough_peak.o: /usr/include/json-c/json_object_iterator.h
hough_peak.o: /usr/include/json-c/json_pointer.h
hough_peak.o: /usr/include/json-c/json_tokener.h
hough_peak.o: /usr/include/json-c/json_util.h /usr/include/json-c/linkhash.h
hough_peak.o: wb_window.hpp hough.hpp
image.o: file_utils.hpp errors.hpp image.hpp bounds.hpp image_header.hpp
image.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
image.o: wb_repository_type.hpp wb_defs.hpp line_segment.hpp point.hpp
image.o: wb_log.hpp variance_stats.hpp wb_utils.hpp
image.o: /usr/include/json-c/json.h /usr/include/json-c/arraylist.h
image.o: /usr/include/json-c/debug.h /usr/include/stdlib.h
image.o: /usr/include/json-c/json_c_version.h
image.o: /usr/include/json-c/json_object.h
image.o: /usr/include/json-c/json_inttypes.h
image.o: /usr/include/json-c/json_config.h /usr/include/inttypes.h
image.o: /usr/include/features.h /usr/include/stdc-predef.h
image.o: /usr/include/stdint.h /usr/include/json-c/json_types.h
image.o: /usr/include/json-c/printbuf.h
image.o: /usr/include/json-c/json_object_iterator.h
image.o: /usr/include/json-c/json_pointer.h
image.o: /usr/include/json-c/json_tokener.h /usr/include/json-c/json_util.h
image.o: /usr/include/json-c/linkhash.h
image_header.o: wb_utils.hpp /usr/include/json-c/json.h
image_header.o: /usr/include/json-c/arraylist.h /usr/include/json-c/debug.h
image_header.o: /usr/include/stdlib.h /usr/include/json-c/json_c_version.h
image_header.o: /usr/include/json-c/json_object.h
image_header.o: /usr/include/json-c/json_inttypes.h
image_header.o: /usr/include/json-c/json_config.h /usr/include/inttypes.h
image_header.o: /usr/include/features.h /usr/include/stdc-predef.h
image_header.o: /usr/include/stdint.h /usr/include/json-c/json_types.h
image_header.o: /usr/include/json-c/printbuf.h
image_header.o: /usr/include/json-c/json_object_iterator.h
image_header.o: /usr/include/json-c/json_pointer.h
image_header.o: /usr/include/json-c/json_tokener.h
image_header.o: /usr/include/json-c/json_util.h
image_header.o: /usr/include/json-c/linkhash.h wb_data_format.hpp
image_header.o: wb_data_type.hpp wb_image_depth.hpp wb_repository_type.hpp
image_header.o: errors.hpp wb_defs.hpp image_header.hpp
internet_data_source_descriptor.o: wb_json_utils.hpp
internet_data_source_descriptor.o: /usr/include/json-c/json.h
internet_data_source_descriptor.o: /usr/include/json-c/arraylist.h
internet_data_source_descriptor.o: /usr/include/json-c/debug.h
internet_data_source_descriptor.o: /usr/include/stdlib.h
internet_data_source_descriptor.o: /usr/include/json-c/json_c_version.h
internet_data_source_descriptor.o: /usr/include/json-c/json_object.h
internet_data_source_descriptor.o: /usr/include/json-c/json_inttypes.h
internet_data_source_descriptor.o: /usr/include/json-c/json_config.h
internet_data_source_descriptor.o: /usr/include/inttypes.h
internet_data_source_descriptor.o: /usr/include/features.h
internet_data_source_descriptor.o: /usr/include/stdc-predef.h
internet_data_source_descriptor.o: /usr/include/stdint.h
internet_data_source_descriptor.o: /usr/include/json-c/json_types.h
internet_data_source_descriptor.o: /usr/include/json-c/printbuf.h
internet_data_source_descriptor.o: /usr/include/json-c/json_object_iterator.h
internet_data_source_descriptor.o: /usr/include/json-c/json_pointer.h
internet_data_source_descriptor.o: /usr/include/json-c/json_tokener.h
internet_data_source_descriptor.o: /usr/include/json-c/json_util.h
internet_data_source_descriptor.o: /usr/include/json-c/linkhash.h errors.hpp
internet_data_source_descriptor.o: data_source_descriptor.hpp wb_defs.hpp
internet_data_source_descriptor.o: histogram.hpp hough.hpp hough_accum.hpp
internet_data_source_descriptor.o: hough_peak.hpp polar_line.hpp
internet_data_source_descriptor.o: variance_stats.hpp bounds.hpp
internet_data_source_descriptor.o: file_utils.hpp image.hpp image_header.hpp
internet_data_source_descriptor.o: wb_data_format.hpp wb_data_type.hpp
internet_data_source_descriptor.o: wb_image_depth.hpp wb_repository_type.hpp
internet_data_source_descriptor.o: line_segment.hpp point.hpp wb_log.hpp
internet_data_source_descriptor.o: polar_trig.hpp wb_utils.hpp
internet_data_source_descriptor.o: wb_filename.hpp
internet_data_source_descriptor.o: internet_data_source_descriptor.hpp
kernel.o: wb_morphology_types.hpp wb_utils.hpp /usr/include/json-c/json.h
kernel.o: /usr/include/json-c/arraylist.h /usr/include/json-c/debug.h
kernel.o: /usr/include/stdlib.h /usr/include/json-c/json_c_version.h
kernel.o: /usr/include/json-c/json_object.h
kernel.o: /usr/include/json-c/json_inttypes.h
kernel.o: /usr/include/json-c/json_config.h /usr/include/inttypes.h
kernel.o: /usr/include/features.h /usr/include/stdc-predef.h
kernel.o: /usr/include/stdint.h /usr/include/json-c/json_types.h
kernel.o: /usr/include/json-c/printbuf.h
kernel.o: /usr/include/json-c/json_object_iterator.h
kernel.o: /usr/include/json-c/json_pointer.h
kernel.o: /usr/include/json-c/json_tokener.h /usr/include/json-c/json_util.h
kernel.o: /usr/include/json-c/linkhash.h wb_data_format.hpp wb_data_type.hpp
kernel.o: wb_image_depth.hpp wb_repository_type.hpp errors.hpp wb_defs.hpp
kernel.o: kernel.hpp image.hpp bounds.hpp image_header.hpp line_segment.hpp
kernel.o: point.hpp wb_log.hpp variance_stats.hpp
line_segment.o: wb_utils.hpp /usr/include/json-c/json.h
line_segment.o: /usr/include/json-c/arraylist.h /usr/include/json-c/debug.h
line_segment.o: /usr/include/stdlib.h /usr/include/json-c/json_c_version.h
line_segment.o: /usr/include/json-c/json_object.h
line_segment.o: /usr/include/json-c/json_inttypes.h
line_segment.o: /usr/include/json-c/json_config.h /usr/include/inttypes.h
line_segment.o: /usr/include/features.h /usr/include/stdc-predef.h
line_segment.o: /usr/include/stdint.h /usr/include/json-c/json_types.h
line_segment.o: /usr/include/json-c/printbuf.h
line_segment.o: /usr/include/json-c/json_object_iterator.h
line_segment.o: /usr/include/json-c/json_pointer.h
line_segment.o: /usr/include/json-c/json_tokener.h
line_segment.o: /usr/include/json-c/json_util.h
line_segment.o: /usr/include/json-c/linkhash.h wb_data_format.hpp
line_segment.o: wb_data_type.hpp wb_image_depth.hpp wb_repository_type.hpp
line_segment.o: errors.hpp wb_defs.hpp line_segment.hpp point.hpp wb_log.hpp
morphology.o: morphology.hpp kernel.hpp image.hpp bounds.hpp errors.hpp
morphology.o: image_header.hpp wb_data_format.hpp wb_data_type.hpp
morphology.o: wb_image_depth.hpp wb_repository_type.hpp wb_defs.hpp
morphology.o: line_segment.hpp point.hpp wb_log.hpp variance_stats.hpp
morphology.o: wb_morphology_types.hpp
one_pass_mean.o: wb_utils.hpp /usr/include/json-c/json.h
one_pass_mean.o: /usr/include/json-c/arraylist.h /usr/include/json-c/debug.h
one_pass_mean.o: /usr/include/stdlib.h /usr/include/json-c/json_c_version.h
one_pass_mean.o: /usr/include/json-c/json_object.h
one_pass_mean.o: /usr/include/json-c/json_inttypes.h
one_pass_mean.o: /usr/include/json-c/json_config.h /usr/include/inttypes.h
one_pass_mean.o: /usr/include/features.h /usr/include/stdc-predef.h
one_pass_mean.o: /usr/include/stdint.h /usr/include/json-c/json_types.h
one_pass_mean.o: /usr/include/json-c/printbuf.h
one_pass_mean.o: /usr/include/json-c/json_object_iterator.h
one_pass_mean.o: /usr/include/json-c/json_pointer.h
one_pass_mean.o: /usr/include/json-c/json_tokener.h
one_pass_mean.o: /usr/include/json-c/json_util.h
one_pass_mean.o: /usr/include/json-c/linkhash.h wb_data_format.hpp
one_pass_mean.o: wb_data_type.hpp wb_image_depth.hpp wb_repository_type.hpp
one_pass_mean.o: errors.hpp wb_defs.hpp one_pass_mean.hpp image.hpp
one_pass_mean.o: bounds.hpp image_header.hpp line_segment.hpp point.hpp
one_pass_mean.o: wb_log.hpp variance_stats.hpp
operator.o: operator.hpp wb_defs.hpp wb_log.hpp errors.hpp
operator.o: data_source_descriptor.hpp /usr/include/json-c/json.h
operator.o: /usr/include/json-c/arraylist.h /usr/include/json-c/debug.h
operator.o: /usr/include/stdlib.h /usr/include/json-c/json_c_version.h
operator.o: /usr/include/json-c/json_object.h
operator.o: /usr/include/json-c/json_inttypes.h
operator.o: /usr/include/json-c/json_config.h /usr/include/inttypes.h
operator.o: /usr/include/features.h /usr/include/stdc-predef.h
operator.o: /usr/include/stdint.h /usr/include/json-c/json_types.h
operator.o: /usr/include/json-c/printbuf.h
operator.o: /usr/include/json-c/json_object_iterator.h
operator.o: /usr/include/json-c/json_pointer.h
operator.o: /usr/include/json-c/json_tokener.h
operator.o: /usr/include/json-c/json_util.h /usr/include/json-c/linkhash.h
operator.o: histogram.hpp hough.hpp hough_accum.hpp hough_peak.hpp
operator.o: polar_line.hpp variance_stats.hpp bounds.hpp file_utils.hpp
operator.o: image.hpp image_header.hpp wb_data_format.hpp wb_data_type.hpp
operator.o: wb_image_depth.hpp wb_repository_type.hpp line_segment.hpp
operator.o: point.hpp polar_trig.hpp wb_utils.hpp wb_filename.hpp
operator_dispatcher.o: operator_filter_edge_kirsch.hpp wb_defs.hpp
operator_dispatcher.o: operator.hpp wb_log.hpp errors.hpp
operator_dispatcher.o: data_source_descriptor.hpp /usr/include/json-c/json.h
operator_dispatcher.o: /usr/include/json-c/arraylist.h
operator_dispatcher.o: /usr/include/json-c/debug.h /usr/include/stdlib.h
operator_dispatcher.o: /usr/include/json-c/json_c_version.h
operator_dispatcher.o: /usr/include/json-c/json_object.h
operator_dispatcher.o: /usr/include/json-c/json_inttypes.h
operator_dispatcher.o: /usr/include/json-c/json_config.h
operator_dispatcher.o: /usr/include/inttypes.h /usr/include/features.h
operator_dispatcher.o: /usr/include/stdc-predef.h /usr/include/stdint.h
operator_dispatcher.o: /usr/include/json-c/json_types.h
operator_dispatcher.o: /usr/include/json-c/printbuf.h
operator_dispatcher.o: /usr/include/json-c/json_object_iterator.h
operator_dispatcher.o: /usr/include/json-c/json_pointer.h
operator_dispatcher.o: /usr/include/json-c/json_tokener.h
operator_dispatcher.o: /usr/include/json-c/json_util.h
operator_dispatcher.o: /usr/include/json-c/linkhash.h histogram.hpp hough.hpp
operator_dispatcher.o: hough_accum.hpp hough_peak.hpp polar_line.hpp
operator_dispatcher.o: variance_stats.hpp bounds.hpp file_utils.hpp image.hpp
operator_dispatcher.o: image_header.hpp wb_data_format.hpp wb_data_type.hpp
operator_dispatcher.o: wb_image_depth.hpp wb_repository_type.hpp
operator_dispatcher.o: line_segment.hpp point.hpp polar_trig.hpp wb_utils.hpp
operator_dispatcher.o: wb_filename.hpp operator_filter_edge_laplacian.hpp
operator_dispatcher.o: operator_filter_edge_prewitt.hpp
operator_dispatcher.o: operator_filter_edge_roberts.hpp
operator_dispatcher.o: operator_filter_edge_sobel.hpp
operator_dispatcher.o: operator_filter_image_morphology.hpp
operator_dispatcher.o: operator_filter_smooth_average.hpp
operator_dispatcher.o: operator_filter_smooth_gaussian.hpp
operator_dispatcher.o: operator_filter_smooth_median.hpp
operator_dispatcher.o: operator_histogram_hough_create.hpp
operator_dispatcher.o: operator_histogram_image_create.hpp
operator_dispatcher.o: operator_histogram_peak_detect.hpp
operator_dispatcher.o: operator_hough_draw_line.hpp
operator_dispatcher.o: operator_hough_image_create.hpp
operator_dispatcher.o: operator_hough_peak_detect.hpp
operator_dispatcher.o: operator_transform_image_combine.hpp
operator_dispatcher.o: operator_transform_image_copy.hpp
operator_dispatcher.o: operator_transform_image_create.hpp
operator_dispatcher.o: operator_transform_intensity_map.hpp
operator_dispatcher.o: operator_dispatcher.hpp
operator_filter_edge_kirsch.o: kernel.hpp image.hpp bounds.hpp errors.hpp
operator_filter_edge_kirsch.o: image_header.hpp wb_data_format.hpp
operator_filter_edge_kirsch.o: wb_data_type.hpp wb_image_depth.hpp
operator_filter_edge_kirsch.o: wb_repository_type.hpp wb_defs.hpp
operator_filter_edge_kirsch.o: line_segment.hpp point.hpp wb_log.hpp
operator_filter_edge_kirsch.o: variance_stats.hpp wb_morphology_types.hpp
operator_filter_edge_kirsch.o: operator_utils.hpp data_source_descriptor.hpp
operator_filter_edge_kirsch.o: /usr/include/json-c/json.h
operator_filter_edge_kirsch.o: /usr/include/json-c/arraylist.h
operator_filter_edge_kirsch.o: /usr/include/json-c/debug.h
operator_filter_edge_kirsch.o: /usr/include/stdlib.h
operator_filter_edge_kirsch.o: /usr/include/json-c/json_c_version.h
operator_filter_edge_kirsch.o: /usr/include/json-c/json_object.h
operator_filter_edge_kirsch.o: /usr/include/json-c/json_inttypes.h
operator_filter_edge_kirsch.o: /usr/include/json-c/json_config.h
operator_filter_edge_kirsch.o: /usr/include/inttypes.h
operator_filter_edge_kirsch.o: /usr/include/features.h
operator_filter_edge_kirsch.o: /usr/include/stdc-predef.h
operator_filter_edge_kirsch.o: /usr/include/stdint.h
operator_filter_edge_kirsch.o: /usr/include/json-c/json_types.h
operator_filter_edge_kirsch.o: /usr/include/json-c/printbuf.h
operator_filter_edge_kirsch.o: /usr/include/json-c/json_object_iterator.h
operator_filter_edge_kirsch.o: /usr/include/json-c/json_pointer.h
operator_filter_edge_kirsch.o: /usr/include/json-c/json_tokener.h
operator_filter_edge_kirsch.o: /usr/include/json-c/json_util.h
operator_filter_edge_kirsch.o: /usr/include/json-c/linkhash.h histogram.hpp
operator_filter_edge_kirsch.o: hough.hpp hough_accum.hpp hough_peak.hpp
operator_filter_edge_kirsch.o: polar_line.hpp file_utils.hpp polar_trig.hpp
operator_filter_edge_kirsch.o: wb_utils.hpp wb_filename.hpp
operator_filter_edge_kirsch.o: operator_filter_edge_kirsch.hpp operator.hpp
operator_filter_edge_laplacian.o: operator_filter_edge_laplacian.hpp
operator_filter_edge_laplacian.o: operator.hpp wb_defs.hpp wb_log.hpp
operator_filter_edge_laplacian.o: errors.hpp data_source_descriptor.hpp
operator_filter_edge_laplacian.o: /usr/include/json-c/json.h
operator_filter_edge_laplacian.o: /usr/include/json-c/arraylist.h
operator_filter_edge_laplacian.o: /usr/include/json-c/debug.h
operator_filter_edge_laplacian.o: /usr/include/stdlib.h
operator_filter_edge_laplacian.o: /usr/include/json-c/json_c_version.h
operator_filter_edge_laplacian.o: /usr/include/json-c/json_object.h
operator_filter_edge_laplacian.o: /usr/include/json-c/json_inttypes.h
operator_filter_edge_laplacian.o: /usr/include/json-c/json_config.h
operator_filter_edge_laplacian.o: /usr/include/inttypes.h
operator_filter_edge_laplacian.o: /usr/include/features.h
operator_filter_edge_laplacian.o: /usr/include/stdc-predef.h
operator_filter_edge_laplacian.o: /usr/include/stdint.h
operator_filter_edge_laplacian.o: /usr/include/json-c/json_types.h
operator_filter_edge_laplacian.o: /usr/include/json-c/printbuf.h
operator_filter_edge_laplacian.o: /usr/include/json-c/json_object_iterator.h
operator_filter_edge_laplacian.o: /usr/include/json-c/json_pointer.h
operator_filter_edge_laplacian.o: /usr/include/json-c/json_tokener.h
operator_filter_edge_laplacian.o: /usr/include/json-c/json_util.h
operator_filter_edge_laplacian.o: /usr/include/json-c/linkhash.h
operator_filter_edge_laplacian.o: histogram.hpp hough.hpp hough_accum.hpp
operator_filter_edge_laplacian.o: hough_peak.hpp polar_line.hpp
operator_filter_edge_laplacian.o: variance_stats.hpp bounds.hpp
operator_filter_edge_laplacian.o: file_utils.hpp image.hpp image_header.hpp
operator_filter_edge_laplacian.o: wb_data_format.hpp wb_data_type.hpp
operator_filter_edge_laplacian.o: wb_image_depth.hpp wb_repository_type.hpp
operator_filter_edge_laplacian.o: line_segment.hpp point.hpp polar_trig.hpp
operator_filter_edge_laplacian.o: wb_utils.hpp wb_filename.hpp
operator_filter_edge_prewitt.o: kernel.hpp image.hpp bounds.hpp errors.hpp
operator_filter_edge_prewitt.o: image_header.hpp wb_data_format.hpp
operator_filter_edge_prewitt.o: wb_data_type.hpp wb_image_depth.hpp
operator_filter_edge_prewitt.o: wb_repository_type.hpp wb_defs.hpp
operator_filter_edge_prewitt.o: line_segment.hpp point.hpp wb_log.hpp
operator_filter_edge_prewitt.o: variance_stats.hpp wb_morphology_types.hpp
operator_filter_edge_prewitt.o: operator_utils.hpp data_source_descriptor.hpp
operator_filter_edge_prewitt.o: /usr/include/json-c/json.h
operator_filter_edge_prewitt.o: /usr/include/json-c/arraylist.h
operator_filter_edge_prewitt.o: /usr/include/json-c/debug.h
operator_filter_edge_prewitt.o: /usr/include/stdlib.h
operator_filter_edge_prewitt.o: /usr/include/json-c/json_c_version.h
operator_filter_edge_prewitt.o: /usr/include/json-c/json_object.h
operator_filter_edge_prewitt.o: /usr/include/json-c/json_inttypes.h
operator_filter_edge_prewitt.o: /usr/include/json-c/json_config.h
operator_filter_edge_prewitt.o: /usr/include/inttypes.h
operator_filter_edge_prewitt.o: /usr/include/features.h
operator_filter_edge_prewitt.o: /usr/include/stdc-predef.h
operator_filter_edge_prewitt.o: /usr/include/stdint.h
operator_filter_edge_prewitt.o: /usr/include/json-c/json_types.h
operator_filter_edge_prewitt.o: /usr/include/json-c/printbuf.h
operator_filter_edge_prewitt.o: /usr/include/json-c/json_object_iterator.h
operator_filter_edge_prewitt.o: /usr/include/json-c/json_pointer.h
operator_filter_edge_prewitt.o: /usr/include/json-c/json_tokener.h
operator_filter_edge_prewitt.o: /usr/include/json-c/json_util.h
operator_filter_edge_prewitt.o: /usr/include/json-c/linkhash.h histogram.hpp
operator_filter_edge_prewitt.o: hough.hpp hough_accum.hpp hough_peak.hpp
operator_filter_edge_prewitt.o: polar_line.hpp file_utils.hpp polar_trig.hpp
operator_filter_edge_prewitt.o: wb_utils.hpp wb_filename.hpp
operator_filter_edge_prewitt.o: operator_filter_edge_prewitt.hpp operator.hpp
operator_filter_edge_roberts.o: kernel.hpp image.hpp bounds.hpp errors.hpp
operator_filter_edge_roberts.o: image_header.hpp wb_data_format.hpp
operator_filter_edge_roberts.o: wb_data_type.hpp wb_image_depth.hpp
operator_filter_edge_roberts.o: wb_repository_type.hpp wb_defs.hpp
operator_filter_edge_roberts.o: line_segment.hpp point.hpp wb_log.hpp
operator_filter_edge_roberts.o: variance_stats.hpp wb_morphology_types.hpp
operator_filter_edge_roberts.o: operator_utils.hpp data_source_descriptor.hpp
operator_filter_edge_roberts.o: /usr/include/json-c/json.h
operator_filter_edge_roberts.o: /usr/include/json-c/arraylist.h
operator_filter_edge_roberts.o: /usr/include/json-c/debug.h
operator_filter_edge_roberts.o: /usr/include/stdlib.h
operator_filter_edge_roberts.o: /usr/include/json-c/json_c_version.h
operator_filter_edge_roberts.o: /usr/include/json-c/json_object.h
operator_filter_edge_roberts.o: /usr/include/json-c/json_inttypes.h
operator_filter_edge_roberts.o: /usr/include/json-c/json_config.h
operator_filter_edge_roberts.o: /usr/include/inttypes.h
operator_filter_edge_roberts.o: /usr/include/features.h
operator_filter_edge_roberts.o: /usr/include/stdc-predef.h
operator_filter_edge_roberts.o: /usr/include/stdint.h
operator_filter_edge_roberts.o: /usr/include/json-c/json_types.h
operator_filter_edge_roberts.o: /usr/include/json-c/printbuf.h
operator_filter_edge_roberts.o: /usr/include/json-c/json_object_iterator.h
operator_filter_edge_roberts.o: /usr/include/json-c/json_pointer.h
operator_filter_edge_roberts.o: /usr/include/json-c/json_tokener.h
operator_filter_edge_roberts.o: /usr/include/json-c/json_util.h
operator_filter_edge_roberts.o: /usr/include/json-c/linkhash.h histogram.hpp
operator_filter_edge_roberts.o: hough.hpp hough_accum.hpp hough_peak.hpp
operator_filter_edge_roberts.o: polar_line.hpp file_utils.hpp polar_trig.hpp
operator_filter_edge_roberts.o: wb_utils.hpp wb_filename.hpp
operator_filter_edge_roberts.o: operator_filter_edge_roberts.hpp operator.hpp
operator_filter_edge_sobel.o: kernel.hpp image.hpp bounds.hpp errors.hpp
operator_filter_edge_sobel.o: image_header.hpp wb_data_format.hpp
operator_filter_edge_sobel.o: wb_data_type.hpp wb_image_depth.hpp
operator_filter_edge_sobel.o: wb_repository_type.hpp wb_defs.hpp
operator_filter_edge_sobel.o: line_segment.hpp point.hpp wb_log.hpp
operator_filter_edge_sobel.o: variance_stats.hpp wb_morphology_types.hpp
operator_filter_edge_sobel.o: operator_utils.hpp data_source_descriptor.hpp
operator_filter_edge_sobel.o: /usr/include/json-c/json.h
operator_filter_edge_sobel.o: /usr/include/json-c/arraylist.h
operator_filter_edge_sobel.o: /usr/include/json-c/debug.h
operator_filter_edge_sobel.o: /usr/include/stdlib.h
operator_filter_edge_sobel.o: /usr/include/json-c/json_c_version.h
operator_filter_edge_sobel.o: /usr/include/json-c/json_object.h
operator_filter_edge_sobel.o: /usr/include/json-c/json_inttypes.h
operator_filter_edge_sobel.o: /usr/include/json-c/json_config.h
operator_filter_edge_sobel.o: /usr/include/inttypes.h /usr/include/features.h
operator_filter_edge_sobel.o: /usr/include/stdc-predef.h
operator_filter_edge_sobel.o: /usr/include/stdint.h
operator_filter_edge_sobel.o: /usr/include/json-c/json_types.h
operator_filter_edge_sobel.o: /usr/include/json-c/printbuf.h
operator_filter_edge_sobel.o: /usr/include/json-c/json_object_iterator.h
operator_filter_edge_sobel.o: /usr/include/json-c/json_pointer.h
operator_filter_edge_sobel.o: /usr/include/json-c/json_tokener.h
operator_filter_edge_sobel.o: /usr/include/json-c/json_util.h
operator_filter_edge_sobel.o: /usr/include/json-c/linkhash.h histogram.hpp
operator_filter_edge_sobel.o: hough.hpp hough_accum.hpp hough_peak.hpp
operator_filter_edge_sobel.o: polar_line.hpp file_utils.hpp polar_trig.hpp
operator_filter_edge_sobel.o: wb_utils.hpp wb_filename.hpp
operator_filter_edge_sobel.o: operator_filter_edge_sobel.hpp operator.hpp
operator_filter_image_morphology.o: kernel.hpp image.hpp bounds.hpp
operator_filter_image_morphology.o: errors.hpp image_header.hpp
operator_filter_image_morphology.o: wb_data_format.hpp wb_data_type.hpp
operator_filter_image_morphology.o: wb_image_depth.hpp wb_repository_type.hpp
operator_filter_image_morphology.o: wb_defs.hpp line_segment.hpp point.hpp
operator_filter_image_morphology.o: wb_log.hpp variance_stats.hpp
operator_filter_image_morphology.o: wb_morphology_types.hpp morphology.hpp
operator_filter_image_morphology.o: operator_utils.hpp
operator_filter_image_morphology.o: data_source_descriptor.hpp
operator_filter_image_morphology.o: /usr/include/json-c/json.h
operator_filter_image_morphology.o: /usr/include/json-c/arraylist.h
operator_filter_image_morphology.o: /usr/include/json-c/debug.h
operator_filter_image_morphology.o: /usr/include/stdlib.h
operator_filter_image_morphology.o: /usr/include/json-c/json_c_version.h
operator_filter_image_morphology.o: /usr/include/json-c/json_object.h
operator_filter_image_morphology.o: /usr/include/json-c/json_inttypes.h
operator_filter_image_morphology.o: /usr/include/json-c/json_config.h
operator_filter_image_morphology.o: /usr/include/inttypes.h
operator_filter_image_morphology.o: /usr/include/features.h
operator_filter_image_morphology.o: /usr/include/stdc-predef.h
operator_filter_image_morphology.o: /usr/include/stdint.h
operator_filter_image_morphology.o: /usr/include/json-c/json_types.h
operator_filter_image_morphology.o: /usr/include/json-c/printbuf.h
operator_filter_image_morphology.o: /usr/include/json-c/json_object_iterator.h
operator_filter_image_morphology.o: /usr/include/json-c/json_pointer.h
operator_filter_image_morphology.o: /usr/include/json-c/json_tokener.h
operator_filter_image_morphology.o: /usr/include/json-c/json_util.h
operator_filter_image_morphology.o: /usr/include/json-c/linkhash.h
operator_filter_image_morphology.o: histogram.hpp hough.hpp hough_accum.hpp
operator_filter_image_morphology.o: hough_peak.hpp polar_line.hpp
operator_filter_image_morphology.o: file_utils.hpp polar_trig.hpp
operator_filter_image_morphology.o: wb_utils.hpp wb_filename.hpp
operator_filter_image_morphology.o: operator_filter_image_morphology.hpp
operator_filter_image_morphology.o: operator.hpp
operator_filter_smooth_average.o: kernel.hpp image.hpp bounds.hpp errors.hpp
operator_filter_smooth_average.o: image_header.hpp wb_data_format.hpp
operator_filter_smooth_average.o: wb_data_type.hpp wb_image_depth.hpp
operator_filter_smooth_average.o: wb_repository_type.hpp wb_defs.hpp
operator_filter_smooth_average.o: line_segment.hpp point.hpp wb_log.hpp
operator_filter_smooth_average.o: variance_stats.hpp wb_morphology_types.hpp
operator_filter_smooth_average.o: operator_utils.hpp
operator_filter_smooth_average.o: data_source_descriptor.hpp
operator_filter_smooth_average.o: /usr/include/json-c/json.h
operator_filter_smooth_average.o: /usr/include/json-c/arraylist.h
operator_filter_smooth_average.o: /usr/include/json-c/debug.h
operator_filter_smooth_average.o: /usr/include/stdlib.h
operator_filter_smooth_average.o: /usr/include/json-c/json_c_version.h
operator_filter_smooth_average.o: /usr/include/json-c/json_object.h
operator_filter_smooth_average.o: /usr/include/json-c/json_inttypes.h
operator_filter_smooth_average.o: /usr/include/json-c/json_config.h
operator_filter_smooth_average.o: /usr/include/inttypes.h
operator_filter_smooth_average.o: /usr/include/features.h
operator_filter_smooth_average.o: /usr/include/stdc-predef.h
operator_filter_smooth_average.o: /usr/include/stdint.h
operator_filter_smooth_average.o: /usr/include/json-c/json_types.h
operator_filter_smooth_average.o: /usr/include/json-c/printbuf.h
operator_filter_smooth_average.o: /usr/include/json-c/json_object_iterator.h
operator_filter_smooth_average.o: /usr/include/json-c/json_pointer.h
operator_filter_smooth_average.o: /usr/include/json-c/json_tokener.h
operator_filter_smooth_average.o: /usr/include/json-c/json_util.h
operator_filter_smooth_average.o: /usr/include/json-c/linkhash.h
operator_filter_smooth_average.o: histogram.hpp hough.hpp hough_accum.hpp
operator_filter_smooth_average.o: hough_peak.hpp polar_line.hpp
operator_filter_smooth_average.o: file_utils.hpp polar_trig.hpp wb_utils.hpp
operator_filter_smooth_average.o: wb_filename.hpp
operator_filter_smooth_average.o: operator_filter_smooth_average.hpp
operator_filter_smooth_average.o: operator.hpp
operator_filter_smooth_gaussian.o: kernel.hpp image.hpp bounds.hpp errors.hpp
operator_filter_smooth_gaussian.o: image_header.hpp wb_data_format.hpp
operator_filter_smooth_gaussian.o: wb_data_type.hpp wb_image_depth.hpp
operator_filter_smooth_gaussian.o: wb_repository_type.hpp wb_defs.hpp
operator_filter_smooth_gaussian.o: line_segment.hpp point.hpp wb_log.hpp
operator_filter_smooth_gaussian.o: variance_stats.hpp wb_morphology_types.hpp
operator_filter_smooth_gaussian.o: operator_utils.hpp
operator_filter_smooth_gaussian.o: data_source_descriptor.hpp
operator_filter_smooth_gaussian.o: /usr/include/json-c/json.h
operator_filter_smooth_gaussian.o: /usr/include/json-c/arraylist.h
operator_filter_smooth_gaussian.o: /usr/include/json-c/debug.h
operator_filter_smooth_gaussian.o: /usr/include/stdlib.h
operator_filter_smooth_gaussian.o: /usr/include/json-c/json_c_version.h
operator_filter_smooth_gaussian.o: /usr/include/json-c/json_object.h
operator_filter_smooth_gaussian.o: /usr/include/json-c/json_inttypes.h
operator_filter_smooth_gaussian.o: /usr/include/json-c/json_config.h
operator_filter_smooth_gaussian.o: /usr/include/inttypes.h
operator_filter_smooth_gaussian.o: /usr/include/features.h
operator_filter_smooth_gaussian.o: /usr/include/stdc-predef.h
operator_filter_smooth_gaussian.o: /usr/include/stdint.h
operator_filter_smooth_gaussian.o: /usr/include/json-c/json_types.h
operator_filter_smooth_gaussian.o: /usr/include/json-c/printbuf.h
operator_filter_smooth_gaussian.o: /usr/include/json-c/json_object_iterator.h
operator_filter_smooth_gaussian.o: /usr/include/json-c/json_pointer.h
operator_filter_smooth_gaussian.o: /usr/include/json-c/json_tokener.h
operator_filter_smooth_gaussian.o: /usr/include/json-c/json_util.h
operator_filter_smooth_gaussian.o: /usr/include/json-c/linkhash.h
operator_filter_smooth_gaussian.o: histogram.hpp hough.hpp hough_accum.hpp
operator_filter_smooth_gaussian.o: hough_peak.hpp polar_line.hpp
operator_filter_smooth_gaussian.o: file_utils.hpp polar_trig.hpp wb_utils.hpp
operator_filter_smooth_gaussian.o: wb_filename.hpp
operator_filter_smooth_gaussian.o: operator_filter_smooth_gaussian.hpp
operator_filter_smooth_gaussian.o: operator.hpp
operator_filter_smooth_median.o: operator_filter_smooth_median.hpp
operator_filter_smooth_median.o: operator.hpp wb_defs.hpp wb_log.hpp
operator_filter_smooth_median.o: errors.hpp data_source_descriptor.hpp
operator_filter_smooth_median.o: /usr/include/json-c/json.h
operator_filter_smooth_median.o: /usr/include/json-c/arraylist.h
operator_filter_smooth_median.o: /usr/include/json-c/debug.h
operator_filter_smooth_median.o: /usr/include/stdlib.h
operator_filter_smooth_median.o: /usr/include/json-c/json_c_version.h
operator_filter_smooth_median.o: /usr/include/json-c/json_object.h
operator_filter_smooth_median.o: /usr/include/json-c/json_inttypes.h
operator_filter_smooth_median.o: /usr/include/json-c/json_config.h
operator_filter_smooth_median.o: /usr/include/inttypes.h
operator_filter_smooth_median.o: /usr/include/features.h
operator_filter_smooth_median.o: /usr/include/stdc-predef.h
operator_filter_smooth_median.o: /usr/include/stdint.h
operator_filter_smooth_median.o: /usr/include/json-c/json_types.h
operator_filter_smooth_median.o: /usr/include/json-c/printbuf.h
operator_filter_smooth_median.o: /usr/include/json-c/json_object_iterator.h
operator_filter_smooth_median.o: /usr/include/json-c/json_pointer.h
operator_filter_smooth_median.o: /usr/include/json-c/json_tokener.h
operator_filter_smooth_median.o: /usr/include/json-c/json_util.h
operator_filter_smooth_median.o: /usr/include/json-c/linkhash.h histogram.hpp
operator_filter_smooth_median.o: hough.hpp hough_accum.hpp hough_peak.hpp
operator_filter_smooth_median.o: polar_line.hpp variance_stats.hpp bounds.hpp
operator_filter_smooth_median.o: file_utils.hpp image.hpp image_header.hpp
operator_filter_smooth_median.o: wb_data_format.hpp wb_data_type.hpp
operator_filter_smooth_median.o: wb_image_depth.hpp wb_repository_type.hpp
operator_filter_smooth_median.o: line_segment.hpp point.hpp polar_trig.hpp
operator_filter_smooth_median.o: wb_utils.hpp wb_filename.hpp
operator_histogram_hough_create.o: berkeley_db_data_source_descriptor.hpp
operator_histogram_hough_create.o: /usr/include/json-c/json.h
operator_histogram_hough_create.o: /usr/include/json-c/arraylist.h
operator_histogram_hough_create.o: /usr/include/json-c/debug.h
operator_histogram_hough_create.o: /usr/include/stdlib.h
operator_histogram_hough_create.o: /usr/include/json-c/json_c_version.h
operator_histogram_hough_create.o: /usr/include/json-c/json_object.h
operator_histogram_hough_create.o: /usr/include/json-c/json_inttypes.h
operator_histogram_hough_create.o: /usr/include/json-c/json_config.h
operator_histogram_hough_create.o: /usr/include/inttypes.h
operator_histogram_hough_create.o: /usr/include/features.h
operator_histogram_hough_create.o: /usr/include/stdc-predef.h
operator_histogram_hough_create.o: /usr/include/stdint.h
operator_histogram_hough_create.o: /usr/include/json-c/json_types.h
operator_histogram_hough_create.o: /usr/include/json-c/printbuf.h
operator_histogram_hough_create.o: /usr/include/json-c/json_object_iterator.h
operator_histogram_hough_create.o: /usr/include/json-c/json_pointer.h
operator_histogram_hough_create.o: /usr/include/json-c/json_tokener.h
operator_histogram_hough_create.o: /usr/include/json-c/json_util.h
operator_histogram_hough_create.o: /usr/include/json-c/linkhash.h
operator_histogram_hough_create.o: wb_image_depth.hpp
operator_histogram_hough_create.o: data_source_descriptor.hpp wb_defs.hpp
operator_histogram_hough_create.o: histogram.hpp errors.hpp hough.hpp
operator_histogram_hough_create.o: hough_accum.hpp hough_peak.hpp
operator_histogram_hough_create.o: polar_line.hpp variance_stats.hpp
operator_histogram_hough_create.o: bounds.hpp file_utils.hpp image.hpp
operator_histogram_hough_create.o: image_header.hpp wb_data_format.hpp
operator_histogram_hough_create.o: wb_data_type.hpp wb_repository_type.hpp
operator_histogram_hough_create.o: line_segment.hpp point.hpp wb_log.hpp
operator_histogram_hough_create.o: polar_trig.hpp wb_utils.hpp
operator_histogram_hough_create.o: wb_filename.hpp operator_utils.hpp
operator_histogram_hough_create.o: operator_histogram_hough_create.hpp
operator_histogram_hough_create.o: operator.hpp
operator_histogram_image_create.o: berkeley_db_data_source_descriptor.hpp
operator_histogram_image_create.o: /usr/include/json-c/json.h
operator_histogram_image_create.o: /usr/include/json-c/arraylist.h
operator_histogram_image_create.o: /usr/include/json-c/debug.h
operator_histogram_image_create.o: /usr/include/stdlib.h
operator_histogram_image_create.o: /usr/include/json-c/json_c_version.h
operator_histogram_image_create.o: /usr/include/json-c/json_object.h
operator_histogram_image_create.o: /usr/include/json-c/json_inttypes.h
operator_histogram_image_create.o: /usr/include/json-c/json_config.h
operator_histogram_image_create.o: /usr/include/inttypes.h
operator_histogram_image_create.o: /usr/include/features.h
operator_histogram_image_create.o: /usr/include/stdc-predef.h
operator_histogram_image_create.o: /usr/include/stdint.h
operator_histogram_image_create.o: /usr/include/json-c/json_types.h
operator_histogram_image_create.o: /usr/include/json-c/printbuf.h
operator_histogram_image_create.o: /usr/include/json-c/json_object_iterator.h
operator_histogram_image_create.o: /usr/include/json-c/json_pointer.h
operator_histogram_image_create.o: /usr/include/json-c/json_tokener.h
operator_histogram_image_create.o: /usr/include/json-c/json_util.h
operator_histogram_image_create.o: /usr/include/json-c/linkhash.h
operator_histogram_image_create.o: wb_image_depth.hpp
operator_histogram_image_create.o: data_source_descriptor.hpp wb_defs.hpp
operator_histogram_image_create.o: histogram.hpp errors.hpp hough.hpp
operator_histogram_image_create.o: hough_accum.hpp hough_peak.hpp
operator_histogram_image_create.o: polar_line.hpp variance_stats.hpp
operator_histogram_image_create.o: bounds.hpp file_utils.hpp image.hpp
operator_histogram_image_create.o: image_header.hpp wb_data_format.hpp
operator_histogram_image_create.o: wb_data_type.hpp wb_repository_type.hpp
operator_histogram_image_create.o: line_segment.hpp point.hpp wb_log.hpp
operator_histogram_image_create.o: polar_trig.hpp wb_utils.hpp
operator_histogram_image_create.o: wb_filename.hpp operator_utils.hpp
operator_histogram_image_create.o: operator_histogram_image_create.hpp
operator_histogram_image_create.o: operator.hpp
operator_histogram_peak_detect.o: operator_histogram_peak_detect.hpp
operator_histogram_peak_detect.o: operator.hpp wb_defs.hpp wb_log.hpp
operator_histogram_peak_detect.o: errors.hpp data_source_descriptor.hpp
operator_histogram_peak_detect.o: /usr/include/json-c/json.h
operator_histogram_peak_detect.o: /usr/include/json-c/arraylist.h
operator_histogram_peak_detect.o: /usr/include/json-c/debug.h
operator_histogram_peak_detect.o: /usr/include/stdlib.h
operator_histogram_peak_detect.o: /usr/include/json-c/json_c_version.h
operator_histogram_peak_detect.o: /usr/include/json-c/json_object.h
operator_histogram_peak_detect.o: /usr/include/json-c/json_inttypes.h
operator_histogram_peak_detect.o: /usr/include/json-c/json_config.h
operator_histogram_peak_detect.o: /usr/include/inttypes.h
operator_histogram_peak_detect.o: /usr/include/features.h
operator_histogram_peak_detect.o: /usr/include/stdc-predef.h
operator_histogram_peak_detect.o: /usr/include/stdint.h
operator_histogram_peak_detect.o: /usr/include/json-c/json_types.h
operator_histogram_peak_detect.o: /usr/include/json-c/printbuf.h
operator_histogram_peak_detect.o: /usr/include/json-c/json_object_iterator.h
operator_histogram_peak_detect.o: /usr/include/json-c/json_pointer.h
operator_histogram_peak_detect.o: /usr/include/json-c/json_tokener.h
operator_histogram_peak_detect.o: /usr/include/json-c/json_util.h
operator_histogram_peak_detect.o: /usr/include/json-c/linkhash.h
operator_histogram_peak_detect.o: histogram.hpp hough.hpp hough_accum.hpp
operator_histogram_peak_detect.o: hough_peak.hpp polar_line.hpp
operator_histogram_peak_detect.o: variance_stats.hpp bounds.hpp
operator_histogram_peak_detect.o: file_utils.hpp image.hpp image_header.hpp
operator_histogram_peak_detect.o: wb_data_format.hpp wb_data_type.hpp
operator_histogram_peak_detect.o: wb_image_depth.hpp wb_repository_type.hpp
operator_histogram_peak_detect.o: line_segment.hpp point.hpp polar_trig.hpp
operator_histogram_peak_detect.o: wb_utils.hpp wb_filename.hpp
operator_hough_draw_line.o: hough.hpp errors.hpp hough_accum.hpp
operator_hough_draw_line.o: hough_peak.hpp polar_line.hpp variance_stats.hpp
operator_hough_draw_line.o: bounds.hpp file_utils.hpp image.hpp
operator_hough_draw_line.o: image_header.hpp wb_data_format.hpp
operator_hough_draw_line.o: wb_data_type.hpp wb_image_depth.hpp
operator_hough_draw_line.o: wb_repository_type.hpp wb_defs.hpp
operator_hough_draw_line.o: line_segment.hpp point.hpp wb_log.hpp
operator_hough_draw_line.o: polar_trig.hpp wb_utils.hpp
operator_hough_draw_line.o: /usr/include/json-c/json.h
operator_hough_draw_line.o: /usr/include/json-c/arraylist.h
operator_hough_draw_line.o: /usr/include/json-c/debug.h /usr/include/stdlib.h
operator_hough_draw_line.o: /usr/include/json-c/json_c_version.h
operator_hough_draw_line.o: /usr/include/json-c/json_object.h
operator_hough_draw_line.o: /usr/include/json-c/json_inttypes.h
operator_hough_draw_line.o: /usr/include/json-c/json_config.h
operator_hough_draw_line.o: /usr/include/inttypes.h /usr/include/features.h
operator_hough_draw_line.o: /usr/include/stdc-predef.h /usr/include/stdint.h
operator_hough_draw_line.o: /usr/include/json-c/json_types.h
operator_hough_draw_line.o: /usr/include/json-c/printbuf.h
operator_hough_draw_line.o: /usr/include/json-c/json_object_iterator.h
operator_hough_draw_line.o: /usr/include/json-c/json_pointer.h
operator_hough_draw_line.o: /usr/include/json-c/json_tokener.h
operator_hough_draw_line.o: /usr/include/json-c/json_util.h
operator_hough_draw_line.o: /usr/include/json-c/linkhash.h operator_utils.hpp
operator_hough_draw_line.o: data_source_descriptor.hpp histogram.hpp
operator_hough_draw_line.o: wb_filename.hpp wb_window.hpp
operator_hough_draw_line.o: operator_hough_draw_line.hpp operator.hpp
operator_hough_image_create.o: hough.hpp errors.hpp hough_accum.hpp
operator_hough_image_create.o: hough_peak.hpp polar_line.hpp
operator_hough_image_create.o: variance_stats.hpp bounds.hpp file_utils.hpp
operator_hough_image_create.o: image.hpp image_header.hpp wb_data_format.hpp
operator_hough_image_create.o: wb_data_type.hpp wb_image_depth.hpp
operator_hough_image_create.o: wb_repository_type.hpp wb_defs.hpp
operator_hough_image_create.o: line_segment.hpp point.hpp wb_log.hpp
operator_hough_image_create.o: polar_trig.hpp wb_utils.hpp
operator_hough_image_create.o: /usr/include/json-c/json.h
operator_hough_image_create.o: /usr/include/json-c/arraylist.h
operator_hough_image_create.o: /usr/include/json-c/debug.h
operator_hough_image_create.o: /usr/include/stdlib.h
operator_hough_image_create.o: /usr/include/json-c/json_c_version.h
operator_hough_image_create.o: /usr/include/json-c/json_object.h
operator_hough_image_create.o: /usr/include/json-c/json_inttypes.h
operator_hough_image_create.o: /usr/include/json-c/json_config.h
operator_hough_image_create.o: /usr/include/inttypes.h
operator_hough_image_create.o: /usr/include/features.h
operator_hough_image_create.o: /usr/include/stdc-predef.h
operator_hough_image_create.o: /usr/include/stdint.h
operator_hough_image_create.o: /usr/include/json-c/json_types.h
operator_hough_image_create.o: /usr/include/json-c/printbuf.h
operator_hough_image_create.o: /usr/include/json-c/json_object_iterator.h
operator_hough_image_create.o: /usr/include/json-c/json_pointer.h
operator_hough_image_create.o: /usr/include/json-c/json_tokener.h
operator_hough_image_create.o: /usr/include/json-c/json_util.h
operator_hough_image_create.o: /usr/include/json-c/linkhash.h
operator_hough_image_create.o: operator_utils.hpp data_source_descriptor.hpp
operator_hough_image_create.o: histogram.hpp wb_filename.hpp
operator_hough_image_create.o: operator_hough_image_create.hpp operator.hpp
operator_hough_peak_detect.o: operator_utils.hpp data_source_descriptor.hpp
operator_hough_peak_detect.o: /usr/include/json-c/json.h
operator_hough_peak_detect.o: /usr/include/json-c/arraylist.h
operator_hough_peak_detect.o: /usr/include/json-c/debug.h
operator_hough_peak_detect.o: /usr/include/stdlib.h
operator_hough_peak_detect.o: /usr/include/json-c/json_c_version.h
operator_hough_peak_detect.o: /usr/include/json-c/json_object.h
operator_hough_peak_detect.o: /usr/include/json-c/json_inttypes.h
operator_hough_peak_detect.o: /usr/include/json-c/json_config.h
operator_hough_peak_detect.o: /usr/include/inttypes.h /usr/include/features.h
operator_hough_peak_detect.o: /usr/include/stdc-predef.h
operator_hough_peak_detect.o: /usr/include/stdint.h
operator_hough_peak_detect.o: /usr/include/json-c/json_types.h
operator_hough_peak_detect.o: /usr/include/json-c/printbuf.h
operator_hough_peak_detect.o: /usr/include/json-c/json_object_iterator.h
operator_hough_peak_detect.o: /usr/include/json-c/json_pointer.h
operator_hough_peak_detect.o: /usr/include/json-c/json_tokener.h
operator_hough_peak_detect.o: /usr/include/json-c/json_util.h
operator_hough_peak_detect.o: /usr/include/json-c/linkhash.h wb_defs.hpp
operator_hough_peak_detect.o: histogram.hpp errors.hpp hough.hpp
operator_hough_peak_detect.o: hough_accum.hpp hough_peak.hpp polar_line.hpp
operator_hough_peak_detect.o: variance_stats.hpp bounds.hpp file_utils.hpp
operator_hough_peak_detect.o: image.hpp image_header.hpp wb_data_format.hpp
operator_hough_peak_detect.o: wb_data_type.hpp wb_image_depth.hpp
operator_hough_peak_detect.o: wb_repository_type.hpp line_segment.hpp
operator_hough_peak_detect.o: point.hpp wb_log.hpp polar_trig.hpp
operator_hough_peak_detect.o: wb_utils.hpp wb_filename.hpp
operator_hough_peak_detect.o: operator_hough_peak_detect.hpp operator.hpp
operator_transform_image_combine.o: operator_transform_image_combine.hpp
operator_transform_image_combine.o: operator.hpp wb_defs.hpp wb_log.hpp
operator_transform_image_combine.o: errors.hpp data_source_descriptor.hpp
operator_transform_image_combine.o: /usr/include/json-c/json.h
operator_transform_image_combine.o: /usr/include/json-c/arraylist.h
operator_transform_image_combine.o: /usr/include/json-c/debug.h
operator_transform_image_combine.o: /usr/include/stdlib.h
operator_transform_image_combine.o: /usr/include/json-c/json_c_version.h
operator_transform_image_combine.o: /usr/include/json-c/json_object.h
operator_transform_image_combine.o: /usr/include/json-c/json_inttypes.h
operator_transform_image_combine.o: /usr/include/json-c/json_config.h
operator_transform_image_combine.o: /usr/include/inttypes.h
operator_transform_image_combine.o: /usr/include/features.h
operator_transform_image_combine.o: /usr/include/stdc-predef.h
operator_transform_image_combine.o: /usr/include/stdint.h
operator_transform_image_combine.o: /usr/include/json-c/json_types.h
operator_transform_image_combine.o: /usr/include/json-c/printbuf.h
operator_transform_image_combine.o: /usr/include/json-c/json_object_iterator.h
operator_transform_image_combine.o: /usr/include/json-c/json_pointer.h
operator_transform_image_combine.o: /usr/include/json-c/json_tokener.h
operator_transform_image_combine.o: /usr/include/json-c/json_util.h
operator_transform_image_combine.o: /usr/include/json-c/linkhash.h
operator_transform_image_combine.o: histogram.hpp hough.hpp hough_accum.hpp
operator_transform_image_combine.o: hough_peak.hpp polar_line.hpp
operator_transform_image_combine.o: variance_stats.hpp bounds.hpp
operator_transform_image_combine.o: file_utils.hpp image.hpp image_header.hpp
operator_transform_image_combine.o: wb_data_format.hpp wb_data_type.hpp
operator_transform_image_combine.o: wb_image_depth.hpp wb_repository_type.hpp
operator_transform_image_combine.o: line_segment.hpp point.hpp polar_trig.hpp
operator_transform_image_combine.o: wb_utils.hpp wb_filename.hpp
operator_transform_image_combine.o: operator_utils.hpp
operator_transform_image_copy.o: operator_transform_image_copy.hpp
operator_transform_image_copy.o: operator.hpp wb_defs.hpp wb_log.hpp
operator_transform_image_copy.o: errors.hpp data_source_descriptor.hpp
operator_transform_image_copy.o: /usr/include/json-c/json.h
operator_transform_image_copy.o: /usr/include/json-c/arraylist.h
operator_transform_image_copy.o: /usr/include/json-c/debug.h
operator_transform_image_copy.o: /usr/include/stdlib.h
operator_transform_image_copy.o: /usr/include/json-c/json_c_version.h
operator_transform_image_copy.o: /usr/include/json-c/json_object.h
operator_transform_image_copy.o: /usr/include/json-c/json_inttypes.h
operator_transform_image_copy.o: /usr/include/json-c/json_config.h
operator_transform_image_copy.o: /usr/include/inttypes.h
operator_transform_image_copy.o: /usr/include/features.h
operator_transform_image_copy.o: /usr/include/stdc-predef.h
operator_transform_image_copy.o: /usr/include/stdint.h
operator_transform_image_copy.o: /usr/include/json-c/json_types.h
operator_transform_image_copy.o: /usr/include/json-c/printbuf.h
operator_transform_image_copy.o: /usr/include/json-c/json_object_iterator.h
operator_transform_image_copy.o: /usr/include/json-c/json_pointer.h
operator_transform_image_copy.o: /usr/include/json-c/json_tokener.h
operator_transform_image_copy.o: /usr/include/json-c/json_util.h
operator_transform_image_copy.o: /usr/include/json-c/linkhash.h histogram.hpp
operator_transform_image_copy.o: hough.hpp hough_accum.hpp hough_peak.hpp
operator_transform_image_copy.o: polar_line.hpp variance_stats.hpp bounds.hpp
operator_transform_image_copy.o: file_utils.hpp image.hpp image_header.hpp
operator_transform_image_copy.o: wb_data_format.hpp wb_data_type.hpp
operator_transform_image_copy.o: wb_image_depth.hpp wb_repository_type.hpp
operator_transform_image_copy.o: line_segment.hpp point.hpp polar_trig.hpp
operator_transform_image_copy.o: wb_utils.hpp wb_filename.hpp
operator_transform_image_create.o: operator_transform_image_create.hpp
operator_transform_image_create.o: operator.hpp wb_defs.hpp wb_log.hpp
operator_transform_image_create.o: errors.hpp data_source_descriptor.hpp
operator_transform_image_create.o: /usr/include/json-c/json.h
operator_transform_image_create.o: /usr/include/json-c/arraylist.h
operator_transform_image_create.o: /usr/include/json-c/debug.h
operator_transform_image_create.o: /usr/include/stdlib.h
operator_transform_image_create.o: /usr/include/json-c/json_c_version.h
operator_transform_image_create.o: /usr/include/json-c/json_object.h
operator_transform_image_create.o: /usr/include/json-c/json_inttypes.h
operator_transform_image_create.o: /usr/include/json-c/json_config.h
operator_transform_image_create.o: /usr/include/inttypes.h
operator_transform_image_create.o: /usr/include/features.h
operator_transform_image_create.o: /usr/include/stdc-predef.h
operator_transform_image_create.o: /usr/include/stdint.h
operator_transform_image_create.o: /usr/include/json-c/json_types.h
operator_transform_image_create.o: /usr/include/json-c/printbuf.h
operator_transform_image_create.o: /usr/include/json-c/json_object_iterator.h
operator_transform_image_create.o: /usr/include/json-c/json_pointer.h
operator_transform_image_create.o: /usr/include/json-c/json_tokener.h
operator_transform_image_create.o: /usr/include/json-c/json_util.h
operator_transform_image_create.o: /usr/include/json-c/linkhash.h
operator_transform_image_create.o: histogram.hpp hough.hpp hough_accum.hpp
operator_transform_image_create.o: hough_peak.hpp polar_line.hpp
operator_transform_image_create.o: variance_stats.hpp bounds.hpp
operator_transform_image_create.o: file_utils.hpp image.hpp image_header.hpp
operator_transform_image_create.o: wb_data_format.hpp wb_data_type.hpp
operator_transform_image_create.o: wb_image_depth.hpp wb_repository_type.hpp
operator_transform_image_create.o: line_segment.hpp point.hpp polar_trig.hpp
operator_transform_image_create.o: wb_utils.hpp wb_filename.hpp
operator_transform_image_create.o: operator_utils.hpp
operator_transform_intensity_map.o: operator_transform_intensity_map.hpp
operator_transform_intensity_map.o: operator.hpp wb_defs.hpp wb_log.hpp
operator_transform_intensity_map.o: errors.hpp data_source_descriptor.hpp
operator_transform_intensity_map.o: /usr/include/json-c/json.h
operator_transform_intensity_map.o: /usr/include/json-c/arraylist.h
operator_transform_intensity_map.o: /usr/include/json-c/debug.h
operator_transform_intensity_map.o: /usr/include/stdlib.h
operator_transform_intensity_map.o: /usr/include/json-c/json_c_version.h
operator_transform_intensity_map.o: /usr/include/json-c/json_object.h
operator_transform_intensity_map.o: /usr/include/json-c/json_inttypes.h
operator_transform_intensity_map.o: /usr/include/json-c/json_config.h
operator_transform_intensity_map.o: /usr/include/inttypes.h
operator_transform_intensity_map.o: /usr/include/features.h
operator_transform_intensity_map.o: /usr/include/stdc-predef.h
operator_transform_intensity_map.o: /usr/include/stdint.h
operator_transform_intensity_map.o: /usr/include/json-c/json_types.h
operator_transform_intensity_map.o: /usr/include/json-c/printbuf.h
operator_transform_intensity_map.o: /usr/include/json-c/json_object_iterator.h
operator_transform_intensity_map.o: /usr/include/json-c/json_pointer.h
operator_transform_intensity_map.o: /usr/include/json-c/json_tokener.h
operator_transform_intensity_map.o: /usr/include/json-c/json_util.h
operator_transform_intensity_map.o: /usr/include/json-c/linkhash.h
operator_transform_intensity_map.o: histogram.hpp hough.hpp hough_accum.hpp
operator_transform_intensity_map.o: hough_peak.hpp polar_line.hpp
operator_transform_intensity_map.o: variance_stats.hpp bounds.hpp
operator_transform_intensity_map.o: file_utils.hpp image.hpp image_header.hpp
operator_transform_intensity_map.o: wb_data_format.hpp wb_data_type.hpp
operator_transform_intensity_map.o: wb_image_depth.hpp wb_repository_type.hpp
operator_transform_intensity_map.o: line_segment.hpp point.hpp polar_trig.hpp
operator_transform_intensity_map.o: wb_utils.hpp wb_filename.hpp
operator_transform_intensity_map.o: operator_utils.hpp
operator_utils.o: data_source_descriptor.hpp /usr/include/json-c/json.h
operator_utils.o: /usr/include/json-c/arraylist.h /usr/include/json-c/debug.h
operator_utils.o: /usr/include/stdlib.h /usr/include/json-c/json_c_version.h
operator_utils.o: /usr/include/json-c/json_object.h
operator_utils.o: /usr/include/json-c/json_inttypes.h
operator_utils.o: /usr/include/json-c/json_config.h /usr/include/inttypes.h
operator_utils.o: /usr/include/features.h /usr/include/stdc-predef.h
operator_utils.o: /usr/include/stdint.h /usr/include/json-c/json_types.h
operator_utils.o: /usr/include/json-c/printbuf.h
operator_utils.o: /usr/include/json-c/json_object_iterator.h
operator_utils.o: /usr/include/json-c/json_pointer.h
operator_utils.o: /usr/include/json-c/json_tokener.h
operator_utils.o: /usr/include/json-c/json_util.h
operator_utils.o: /usr/include/json-c/linkhash.h wb_defs.hpp histogram.hpp
operator_utils.o: errors.hpp hough.hpp hough_accum.hpp hough_peak.hpp
operator_utils.o: polar_line.hpp variance_stats.hpp bounds.hpp file_utils.hpp
operator_utils.o: image.hpp image_header.hpp wb_data_format.hpp
operator_utils.o: wb_data_type.hpp wb_image_depth.hpp wb_repository_type.hpp
operator_utils.o: line_segment.hpp point.hpp wb_log.hpp polar_trig.hpp
operator_utils.o: wb_utils.hpp wb_filename.hpp operator_utils.hpp
pearsons_correlation.o: pearsons_correlation.hpp image.hpp bounds.hpp
pearsons_correlation.o: errors.hpp image_header.hpp wb_data_format.hpp
pearsons_correlation.o: wb_data_type.hpp wb_image_depth.hpp
pearsons_correlation.o: wb_repository_type.hpp wb_defs.hpp line_segment.hpp
pearsons_correlation.o: point.hpp wb_log.hpp variance_stats.hpp kernel.hpp
pearsons_correlation.o: wb_morphology_types.hpp one_pass_mean.hpp
point.o: wb_utils.hpp /usr/include/json-c/json.h
point.o: /usr/include/json-c/arraylist.h /usr/include/json-c/debug.h
point.o: /usr/include/stdlib.h /usr/include/json-c/json_c_version.h
point.o: /usr/include/json-c/json_object.h
point.o: /usr/include/json-c/json_inttypes.h
point.o: /usr/include/json-c/json_config.h /usr/include/inttypes.h
point.o: /usr/include/features.h /usr/include/stdc-predef.h
point.o: /usr/include/stdint.h /usr/include/json-c/json_types.h
point.o: /usr/include/json-c/printbuf.h
point.o: /usr/include/json-c/json_object_iterator.h
point.o: /usr/include/json-c/json_pointer.h
point.o: /usr/include/json-c/json_tokener.h /usr/include/json-c/json_util.h
point.o: /usr/include/json-c/linkhash.h wb_data_format.hpp wb_data_type.hpp
point.o: wb_image_depth.hpp wb_repository_type.hpp errors.hpp wb_defs.hpp
point.o: point.hpp
polar_line.o: polar_line.hpp hough_peak.hpp errors.hpp hough_accum.hpp
polar_line.o: bounds.hpp file_utils.hpp image.hpp image_header.hpp
polar_line.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
polar_line.o: wb_repository_type.hpp wb_defs.hpp line_segment.hpp point.hpp
polar_line.o: wb_log.hpp variance_stats.hpp polar_trig.hpp wb_utils.hpp
polar_line.o: /usr/include/json-c/json.h /usr/include/json-c/arraylist.h
polar_line.o: /usr/include/json-c/debug.h /usr/include/stdlib.h
polar_line.o: /usr/include/json-c/json_c_version.h
polar_line.o: /usr/include/json-c/json_object.h
polar_line.o: /usr/include/json-c/json_inttypes.h
polar_line.o: /usr/include/json-c/json_config.h /usr/include/inttypes.h
polar_line.o: /usr/include/features.h /usr/include/stdc-predef.h
polar_line.o: /usr/include/stdint.h /usr/include/json-c/json_types.h
polar_line.o: /usr/include/json-c/printbuf.h
polar_line.o: /usr/include/json-c/json_object_iterator.h
polar_line.o: /usr/include/json-c/json_pointer.h
polar_line.o: /usr/include/json-c/json_tokener.h
polar_line.o: /usr/include/json-c/json_util.h /usr/include/json-c/linkhash.h
polar_trig.o: polar_trig.hpp wb_utils.hpp /usr/include/json-c/json.h
polar_trig.o: /usr/include/json-c/arraylist.h /usr/include/json-c/debug.h
polar_trig.o: /usr/include/stdlib.h /usr/include/json-c/json_c_version.h
polar_trig.o: /usr/include/json-c/json_object.h
polar_trig.o: /usr/include/json-c/json_inttypes.h
polar_trig.o: /usr/include/json-c/json_config.h /usr/include/inttypes.h
polar_trig.o: /usr/include/features.h /usr/include/stdc-predef.h
polar_trig.o: /usr/include/stdint.h /usr/include/json-c/json_types.h
polar_trig.o: /usr/include/json-c/printbuf.h
polar_trig.o: /usr/include/json-c/json_object_iterator.h
polar_trig.o: /usr/include/json-c/json_pointer.h
polar_trig.o: /usr/include/json-c/json_tokener.h
polar_trig.o: /usr/include/json-c/json_util.h /usr/include/json-c/linkhash.h
polar_trig.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
polar_trig.o: wb_repository_type.hpp errors.hpp wb_defs.hpp point.hpp
polar_trig.o: polar_trig_static.hpp
runtime.o: runtime.hpp /usr/include/json-c/json.h
runtime.o: /usr/include/json-c/arraylist.h /usr/include/json-c/debug.h
runtime.o: /usr/include/stdlib.h /usr/include/json-c/json_c_version.h
runtime.o: /usr/include/json-c/json_object.h
runtime.o: /usr/include/json-c/json_inttypes.h
runtime.o: /usr/include/json-c/json_config.h /usr/include/inttypes.h
runtime.o: /usr/include/features.h /usr/include/stdc-predef.h
runtime.o: /usr/include/stdint.h /usr/include/json-c/json_types.h
runtime.o: /usr/include/json-c/printbuf.h
runtime.o: /usr/include/json-c/json_object_iterator.h
runtime.o: /usr/include/json-c/json_pointer.h
runtime.o: /usr/include/json-c/json_tokener.h /usr/include/json-c/json_util.h
runtime.o: /usr/include/json-c/linkhash.h wb_utils.hpp wb_data_format.hpp
runtime.o: wb_data_type.hpp wb_image_depth.hpp wb_repository_type.hpp
runtime.o: errors.hpp wb_defs.hpp wb_version.hpp
variance_stats.o: wb_utils.hpp /usr/include/json-c/json.h
variance_stats.o: /usr/include/json-c/arraylist.h /usr/include/json-c/debug.h
variance_stats.o: /usr/include/stdlib.h /usr/include/json-c/json_c_version.h
variance_stats.o: /usr/include/json-c/json_object.h
variance_stats.o: /usr/include/json-c/json_inttypes.h
variance_stats.o: /usr/include/json-c/json_config.h /usr/include/inttypes.h
variance_stats.o: /usr/include/features.h /usr/include/stdc-predef.h
variance_stats.o: /usr/include/stdint.h /usr/include/json-c/json_types.h
variance_stats.o: /usr/include/json-c/printbuf.h
variance_stats.o: /usr/include/json-c/json_object_iterator.h
variance_stats.o: /usr/include/json-c/json_pointer.h
variance_stats.o: /usr/include/json-c/json_tokener.h
variance_stats.o: /usr/include/json-c/json_util.h
variance_stats.o: /usr/include/json-c/linkhash.h wb_data_format.hpp
variance_stats.o: wb_data_type.hpp wb_image_depth.hpp wb_repository_type.hpp
variance_stats.o: errors.hpp wb_defs.hpp variance_stats.hpp bounds.hpp
wb_data_format.o: wb_data_format.hpp
wb_data_type.o: wb_data_type.hpp
wb_filename.o: errors.hpp wb_utils.hpp /usr/include/json-c/json.h
wb_filename.o: /usr/include/json-c/arraylist.h /usr/include/json-c/debug.h
wb_filename.o: /usr/include/stdlib.h /usr/include/json-c/json_c_version.h
wb_filename.o: /usr/include/json-c/json_object.h
wb_filename.o: /usr/include/json-c/json_inttypes.h
wb_filename.o: /usr/include/json-c/json_config.h /usr/include/inttypes.h
wb_filename.o: /usr/include/features.h /usr/include/stdc-predef.h
wb_filename.o: /usr/include/stdint.h /usr/include/json-c/json_types.h
wb_filename.o: /usr/include/json-c/printbuf.h
wb_filename.o: /usr/include/json-c/json_object_iterator.h
wb_filename.o: /usr/include/json-c/json_pointer.h
wb_filename.o: /usr/include/json-c/json_tokener.h
wb_filename.o: /usr/include/json-c/json_util.h /usr/include/json-c/linkhash.h
wb_filename.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
wb_filename.o: wb_repository_type.hpp wb_defs.hpp wb_filename.hpp
wb_image_depth.o: wb_image_depth.hpp
wb_json_utils.o: wb_json_utils.hpp /usr/include/json-c/json.h
wb_json_utils.o: /usr/include/json-c/arraylist.h /usr/include/json-c/debug.h
wb_json_utils.o: /usr/include/stdlib.h /usr/include/json-c/json_c_version.h
wb_json_utils.o: /usr/include/json-c/json_object.h
wb_json_utils.o: /usr/include/json-c/json_inttypes.h
wb_json_utils.o: /usr/include/json-c/json_config.h /usr/include/inttypes.h
wb_json_utils.o: /usr/include/features.h /usr/include/stdc-predef.h
wb_json_utils.o: /usr/include/stdint.h /usr/include/json-c/json_types.h
wb_json_utils.o: /usr/include/json-c/printbuf.h
wb_json_utils.o: /usr/include/json-c/json_object_iterator.h
wb_json_utils.o: /usr/include/json-c/json_pointer.h
wb_json_utils.o: /usr/include/json-c/json_tokener.h
wb_json_utils.o: /usr/include/json-c/json_util.h
wb_json_utils.o: /usr/include/json-c/linkhash.h errors.hpp
wb_log.o: errors.hpp wb_log.hpp
wb_morphology_types.o: wb_morphology_types.hpp
wb_repository_type.o: wb_repository_type.hpp
wb_utils.o: errors.hpp wb_defs.hpp wb_utils.hpp /usr/include/json-c/json.h
wb_utils.o: /usr/include/json-c/arraylist.h /usr/include/json-c/debug.h
wb_utils.o: /usr/include/stdlib.h /usr/include/json-c/json_c_version.h
wb_utils.o: /usr/include/json-c/json_object.h
wb_utils.o: /usr/include/json-c/json_inttypes.h
wb_utils.o: /usr/include/json-c/json_config.h /usr/include/inttypes.h
wb_utils.o: /usr/include/features.h /usr/include/stdc-predef.h
wb_utils.o: /usr/include/stdint.h /usr/include/json-c/json_types.h
wb_utils.o: /usr/include/json-c/printbuf.h
wb_utils.o: /usr/include/json-c/json_object_iterator.h
wb_utils.o: /usr/include/json-c/json_pointer.h
wb_utils.o: /usr/include/json-c/json_tokener.h
wb_utils.o: /usr/include/json-c/json_util.h /usr/include/json-c/linkhash.h
wb_utils.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
wb_utils.o: wb_repository_type.hpp
wb_window.o: polar_trig.hpp wb_window.hpp line_segment.hpp point.hpp
wb_window.o: wb_log.hpp errors.hpp polar_line.hpp hough_peak.hpp
wb_window.o: hough_accum.hpp bounds.hpp file_utils.hpp image.hpp
wb_window.o: image_header.hpp wb_data_format.hpp wb_data_type.hpp
wb_window.o: wb_image_depth.hpp wb_repository_type.hpp wb_defs.hpp
wb_window.o: variance_stats.hpp wb_utils.hpp /usr/include/json-c/json.h
wb_window.o: /usr/include/json-c/arraylist.h /usr/include/json-c/debug.h
wb_window.o: /usr/include/stdlib.h /usr/include/json-c/json_c_version.h
wb_window.o: /usr/include/json-c/json_object.h
wb_window.o: /usr/include/json-c/json_inttypes.h
wb_window.o: /usr/include/json-c/json_config.h /usr/include/inttypes.h
wb_window.o: /usr/include/features.h /usr/include/stdc-predef.h
wb_window.o: /usr/include/stdint.h /usr/include/json-c/json_types.h
wb_window.o: /usr/include/json-c/printbuf.h
wb_window.o: /usr/include/json-c/json_object_iterator.h
wb_window.o: /usr/include/json-c/json_pointer.h
wb_window.o: /usr/include/json-c/json_tokener.h
wb_window.o: /usr/include/json-c/json_util.h /usr/include/json-c/linkhash.h
