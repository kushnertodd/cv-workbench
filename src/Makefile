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
  linear_features.o \
  morphology.o \
  one_pass_mean.o \
  operator_dispatcher.o \
  operator_filter_edge_kirsch.o \
  operator_filter_edge_laplacian.o \
  operator_filter_edge_linear.o \
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
  operator_hough_draw_lines.o \
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
  runtime.o \
  theta.o \
  variance_stats.o \
  wb_data_format.o \
  wb_data_type.o \
  wb_filename.o \
  wb_image_depth.o \
  wb_json_utils.o \
  wb_log.o \
  wb_linear_config_mask.o \
  wb_morphology_types.o \
  wb_repository_type.o \
  wb_utils.o \
  wb_window.o

PROGRAMS = \
  cv-workbench \
  image-copy \
  image-corr \
  image-dump \
  image-features \
  image-info \
  image-map \
  image-mask \
  image-mean \
  image-morph \
  image-read 
#  image-trig \

%.o: %.cpp %.hpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

all: $(PROGRAMS)

image-copy: image-copy.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

image-corr: image-corr.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

image-dump: image-dump.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

image-features: image-features.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

image-info: image-info.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

image-map: image-map.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

image-mask: image-mask.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

image-mean: image-mean.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

image-morph: image-morph.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

image-read: image-read.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

#image-trig: image-trig.o theta.o
#	$(CXX) $< -o $@ theta.o $(CXXFLAGS) 

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
	doxygen doxygen.config; cp ../doc/images/*.jpg html

depend:
	makedepend -- $(CXXFLAGS) -- $(SRCFILES)

programs:
	@echo $(PROGRAMS)

# DO NOT DELETE

berkeley_db_data_source_descriptor.o: wb_data_format.hpp wb_data_type.hpp
berkeley_db_data_source_descriptor.o: wb_repository_type.hpp
berkeley_db_data_source_descriptor.o: wb_json_utils.hpp errors.hpp
berkeley_db_data_source_descriptor.o: data_source_descriptor.hpp wb_defs.hpp
berkeley_db_data_source_descriptor.o: histogram.hpp hough.hpp hough_accum.hpp
berkeley_db_data_source_descriptor.o: image.hpp bounds.hpp image_header.hpp
berkeley_db_data_source_descriptor.o: wb_image_depth.hpp line_segment.hpp
berkeley_db_data_source_descriptor.o: point.hpp wb_log.hpp variance_stats.hpp
berkeley_db_data_source_descriptor.o: theta.hpp wb_utils.hpp hough_peak.hpp
berkeley_db_data_source_descriptor.o: polar_line.hpp wb_filename.hpp
berkeley_db_data_source_descriptor.o: berkeley_db_data_source_descriptor.hpp
bounds.o: bounds.hpp
cv-workbench.o: experiment.hpp wb_defs.hpp errors.hpp image.hpp bounds.hpp
cv-workbench.o: image_header.hpp wb_data_format.hpp wb_data_type.hpp
cv-workbench.o: wb_image_depth.hpp wb_repository_type.hpp line_segment.hpp
cv-workbench.o: point.hpp wb_log.hpp variance_stats.hpp histogram.hpp
cv-workbench.o: hough.hpp hough_accum.hpp theta.hpp wb_utils.hpp
cv-workbench.o: hough_peak.hpp polar_line.hpp wb_filename.hpp
cv-workbench.o: experiment_step.hpp data_source_descriptor.hpp
cv-workbench.o: wb_json_utils.hpp file_utils.hpp runtime.hpp
data_source_descriptor.o: berkeley_db_data_source_descriptor.hpp
data_source_descriptor.o: wb_image_depth.hpp data_source_descriptor.hpp
data_source_descriptor.o: wb_defs.hpp histogram.hpp errors.hpp hough.hpp
data_source_descriptor.o: hough_accum.hpp image.hpp bounds.hpp
data_source_descriptor.o: image_header.hpp wb_data_format.hpp
data_source_descriptor.o: wb_data_type.hpp wb_repository_type.hpp
data_source_descriptor.o: line_segment.hpp point.hpp wb_log.hpp
data_source_descriptor.o: variance_stats.hpp theta.hpp wb_utils.hpp
data_source_descriptor.o: hough_peak.hpp polar_line.hpp wb_filename.hpp
data_source_descriptor.o: filesystem_data_source_descriptor.hpp
data_source_descriptor.o: internet_data_source_descriptor.hpp
data_source_descriptor.o: wb_json_utils.hpp
errors.o: errors.hpp
experiment.o: runtime.hpp wb_defs.hpp experiment.hpp errors.hpp image.hpp
experiment.o: bounds.hpp image_header.hpp wb_data_format.hpp wb_data_type.hpp
experiment.o: wb_image_depth.hpp wb_repository_type.hpp line_segment.hpp
experiment.o: point.hpp wb_log.hpp variance_stats.hpp histogram.hpp hough.hpp
experiment.o: hough_accum.hpp theta.hpp wb_utils.hpp hough_peak.hpp
experiment.o: polar_line.hpp wb_filename.hpp experiment_step.hpp
experiment.o: data_source_descriptor.hpp wb_json_utils.hpp
experiment_step.o: wb_data_type.hpp data_source_descriptor.hpp wb_defs.hpp
experiment_step.o: histogram.hpp errors.hpp hough.hpp hough_accum.hpp
experiment_step.o: image.hpp bounds.hpp image_header.hpp wb_data_format.hpp
experiment_step.o: wb_image_depth.hpp wb_repository_type.hpp line_segment.hpp
experiment_step.o: point.hpp wb_log.hpp variance_stats.hpp theta.hpp
experiment_step.o: wb_utils.hpp hough_peak.hpp polar_line.hpp wb_filename.hpp
experiment_step.o: experiment_step.hpp operator.hpp operator_dispatcher.hpp
experiment_step.o: wb_json_utils.hpp
filesystem_data_source_descriptor.o: file_utils.hpp errors.hpp
filesystem_data_source_descriptor.o: data_source_descriptor.hpp wb_defs.hpp
filesystem_data_source_descriptor.o: histogram.hpp hough.hpp hough_accum.hpp
filesystem_data_source_descriptor.o: image.hpp bounds.hpp image_header.hpp
filesystem_data_source_descriptor.o: wb_data_format.hpp wb_data_type.hpp
filesystem_data_source_descriptor.o: wb_image_depth.hpp
filesystem_data_source_descriptor.o: wb_repository_type.hpp line_segment.hpp
filesystem_data_source_descriptor.o: point.hpp wb_log.hpp variance_stats.hpp
filesystem_data_source_descriptor.o: theta.hpp wb_utils.hpp hough_peak.hpp
filesystem_data_source_descriptor.o: polar_line.hpp wb_filename.hpp
filesystem_data_source_descriptor.o: filesystem_data_source_descriptor.hpp
filesystem_data_source_descriptor.o: wb_json_utils.hpp
file_utils.o: file_utils.hpp errors.hpp
histogram.o: errors.hpp file_utils.hpp wb_utils.hpp wb_data_format.hpp
histogram.o: wb_data_type.hpp wb_image_depth.hpp wb_repository_type.hpp
histogram.o: wb_defs.hpp theta.hpp histogram.hpp hough.hpp hough_accum.hpp
histogram.o: image.hpp bounds.hpp image_header.hpp line_segment.hpp point.hpp
histogram.o: wb_log.hpp variance_stats.hpp hough_peak.hpp polar_line.hpp
histogram.o: wb_filename.hpp
hough_accum.o: image.hpp bounds.hpp errors.hpp image_header.hpp
hough_accum.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
hough_accum.o: wb_repository_type.hpp wb_defs.hpp line_segment.hpp point.hpp
hough_accum.o: wb_log.hpp variance_stats.hpp theta.hpp wb_utils.hpp
hough_accum.o: wb_window.hpp polar_line.hpp hough_accum.hpp hough_peak.hpp
hough.o: file_utils.hpp errors.hpp image.hpp bounds.hpp image_header.hpp
hough.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
hough.o: wb_repository_type.hpp wb_defs.hpp line_segment.hpp point.hpp
hough.o: wb_log.hpp variance_stats.hpp wb_utils.hpp hough.hpp hough_accum.hpp
hough.o: theta.hpp hough_peak.hpp polar_line.hpp
hough_peak.o: errors.hpp file_utils.hpp hough_accum.hpp image.hpp bounds.hpp
hough_peak.o: image_header.hpp wb_data_format.hpp wb_data_type.hpp
hough_peak.o: wb_image_depth.hpp wb_repository_type.hpp wb_defs.hpp
hough_peak.o: line_segment.hpp point.hpp wb_log.hpp variance_stats.hpp
hough_peak.o: theta.hpp wb_utils.hpp hough_peak.hpp polar_line.hpp
hough_peak.o: wb_window.hpp
image-copy.o: errors.hpp image.hpp bounds.hpp image_header.hpp
image-copy.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
image-copy.o: wb_repository_type.hpp wb_defs.hpp line_segment.hpp point.hpp
image-copy.o: wb_log.hpp variance_stats.hpp wb_filename.hpp wb_utils.hpp
image-corr.o: errors.hpp image.hpp bounds.hpp image_header.hpp
image-corr.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
image-corr.o: wb_repository_type.hpp wb_defs.hpp line_segment.hpp point.hpp
image-corr.o: wb_log.hpp variance_stats.hpp wb_filename.hpp wb_utils.hpp
image-corr.o: pearsons_correlation.hpp kernel.hpp wb_morphology_types.hpp
image-corr.o: one_pass_mean.hpp
image.o: file_utils.hpp errors.hpp image.hpp bounds.hpp image_header.hpp
image.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
image.o: wb_repository_type.hpp wb_defs.hpp line_segment.hpp point.hpp
image.o: wb_log.hpp variance_stats.hpp wb_utils.hpp
image-dump.o: errors.hpp image.hpp bounds.hpp image_header.hpp
image-dump.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
image-dump.o: wb_repository_type.hpp wb_defs.hpp line_segment.hpp point.hpp
image-dump.o: wb_log.hpp variance_stats.hpp wb_filename.hpp wb_utils.hpp
image-features.o: errors.hpp image.hpp bounds.hpp image_header.hpp
image-features.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
image-features.o: wb_repository_type.hpp wb_defs.hpp line_segment.hpp
image-features.o: point.hpp wb_log.hpp variance_stats.hpp linear_features.hpp
image-features.o: wb_utils.hpp wb_filename.hpp
image_header.o: wb_utils.hpp wb_data_format.hpp wb_data_type.hpp
image_header.o: wb_image_depth.hpp wb_repository_type.hpp errors.hpp
image_header.o: wb_defs.hpp image_header.hpp
image-info.o: errors.hpp histogram.hpp hough.hpp hough_accum.hpp image.hpp
image-info.o: bounds.hpp image_header.hpp wb_data_format.hpp wb_data_type.hpp
image-info.o: wb_image_depth.hpp wb_repository_type.hpp wb_defs.hpp
image-info.o: line_segment.hpp point.hpp wb_log.hpp variance_stats.hpp
image-info.o: theta.hpp wb_utils.hpp hough_peak.hpp polar_line.hpp
image-info.o: wb_filename.hpp
image-map.o: errors.hpp image.hpp bounds.hpp image_header.hpp
image-map.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
image-map.o: wb_repository_type.hpp wb_defs.hpp line_segment.hpp point.hpp
image-map.o: wb_log.hpp variance_stats.hpp wb_filename.hpp wb_utils.hpp
image-mask.o: errors.hpp kernel.hpp image.hpp bounds.hpp image_header.hpp
image-mask.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
image-mask.o: wb_repository_type.hpp wb_defs.hpp line_segment.hpp point.hpp
image-mask.o: wb_log.hpp variance_stats.hpp wb_morphology_types.hpp
image-mask.o: wb_filename.hpp wb_utils.hpp
image-mean.o: image.hpp bounds.hpp errors.hpp image_header.hpp
image-mean.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
image-mean.o: wb_repository_type.hpp wb_defs.hpp line_segment.hpp point.hpp
image-mean.o: wb_log.hpp variance_stats.hpp one_pass_mean.hpp
image-morph.o: errors.hpp image.hpp bounds.hpp image_header.hpp
image-morph.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
image-morph.o: wb_repository_type.hpp wb_defs.hpp line_segment.hpp point.hpp
image-morph.o: wb_log.hpp variance_stats.hpp morphology.hpp kernel.hpp
image-morph.o: wb_morphology_types.hpp wb_filename.hpp wb_utils.hpp
image-read.o: errors.hpp image.hpp bounds.hpp image_header.hpp
image-read.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
image-read.o: wb_repository_type.hpp wb_defs.hpp line_segment.hpp point.hpp
image-read.o: wb_log.hpp variance_stats.hpp wb_filename.hpp wb_utils.hpp
image-trig.o: theta.hpp wb_utils.hpp wb_data_format.hpp wb_data_type.hpp
image-trig.o: wb_image_depth.hpp wb_repository_type.hpp errors.hpp
image-trig.o: wb_defs.hpp
internet_data_source_descriptor.o: wb_json_utils.hpp errors.hpp
internet_data_source_descriptor.o: data_source_descriptor.hpp wb_defs.hpp
internet_data_source_descriptor.o: histogram.hpp hough.hpp hough_accum.hpp
internet_data_source_descriptor.o: image.hpp bounds.hpp image_header.hpp
internet_data_source_descriptor.o: wb_data_format.hpp wb_data_type.hpp
internet_data_source_descriptor.o: wb_image_depth.hpp wb_repository_type.hpp
internet_data_source_descriptor.o: line_segment.hpp point.hpp wb_log.hpp
internet_data_source_descriptor.o: variance_stats.hpp theta.hpp wb_utils.hpp
internet_data_source_descriptor.o: hough_peak.hpp polar_line.hpp
internet_data_source_descriptor.o: wb_filename.hpp
internet_data_source_descriptor.o: internet_data_source_descriptor.hpp
kernel.o: theta.hpp wb_utils.hpp wb_data_format.hpp wb_data_type.hpp
kernel.o: wb_image_depth.hpp wb_repository_type.hpp errors.hpp wb_defs.hpp
kernel.o: wb_linear_config_mask.hpp wb_config_mask.hpp
kernel.o: wb_morphology_types.hpp wb_window.hpp line_segment.hpp point.hpp
kernel.o: wb_log.hpp polar_line.hpp kernel.hpp image.hpp bounds.hpp
kernel.o: image_header.hpp variance_stats.hpp
linear_features.o: line_segment.hpp point.hpp wb_log.hpp errors.hpp
linear_features.o: linear_features.hpp image.hpp bounds.hpp image_header.hpp
linear_features.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
linear_features.o: wb_repository_type.hpp wb_defs.hpp variance_stats.hpp
linear_features.o: wb_utils.hpp theta.hpp wb_window.hpp polar_line.hpp
line_segment.o: wb_utils.hpp wb_data_format.hpp wb_data_type.hpp
line_segment.o: wb_image_depth.hpp wb_repository_type.hpp errors.hpp
line_segment.o: wb_defs.hpp line_segment.hpp point.hpp wb_log.hpp
morphology.o: morphology.hpp kernel.hpp image.hpp bounds.hpp errors.hpp
morphology.o: image_header.hpp wb_data_format.hpp wb_data_type.hpp
morphology.o: wb_image_depth.hpp wb_repository_type.hpp wb_defs.hpp
morphology.o: line_segment.hpp point.hpp wb_log.hpp variance_stats.hpp
morphology.o: wb_morphology_types.hpp
one_pass_mean.o: wb_utils.hpp wb_data_format.hpp wb_data_type.hpp
one_pass_mean.o: wb_image_depth.hpp wb_repository_type.hpp errors.hpp
one_pass_mean.o: wb_defs.hpp one_pass_mean.hpp image.hpp bounds.hpp
one_pass_mean.o: image_header.hpp line_segment.hpp point.hpp wb_log.hpp
one_pass_mean.o: variance_stats.hpp
operator.o: operator.hpp wb_defs.hpp wb_log.hpp errors.hpp
operator.o: data_source_descriptor.hpp histogram.hpp hough.hpp
operator.o: hough_accum.hpp image.hpp bounds.hpp image_header.hpp
operator.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
operator.o: wb_repository_type.hpp line_segment.hpp point.hpp
operator.o: variance_stats.hpp theta.hpp wb_utils.hpp hough_peak.hpp
operator.o: polar_line.hpp wb_filename.hpp
operator_dispatcher.o: operator_filter_edge_kirsch.hpp wb_defs.hpp
operator_dispatcher.o: operator.hpp wb_log.hpp errors.hpp
operator_dispatcher.o: data_source_descriptor.hpp histogram.hpp hough.hpp
operator_dispatcher.o: hough_accum.hpp image.hpp bounds.hpp image_header.hpp
operator_dispatcher.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
operator_dispatcher.o: wb_repository_type.hpp line_segment.hpp point.hpp
operator_dispatcher.o: variance_stats.hpp theta.hpp wb_utils.hpp
operator_dispatcher.o: hough_peak.hpp polar_line.hpp wb_filename.hpp
operator_dispatcher.o: operator_filter_edge_laplacian.hpp
operator_dispatcher.o: operator_filter_edge_linear.hpp
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
operator_dispatcher.o: operator_hough_draw_lines.hpp
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
operator_filter_edge_kirsch.o: histogram.hpp hough.hpp hough_accum.hpp
operator_filter_edge_kirsch.o: theta.hpp wb_utils.hpp hough_peak.hpp
operator_filter_edge_kirsch.o: polar_line.hpp wb_filename.hpp
operator_filter_edge_kirsch.o: operator_filter_edge_kirsch.hpp operator.hpp
operator_filter_edge_laplacian.o: operator_filter_edge_laplacian.hpp
operator_filter_edge_laplacian.o: operator.hpp wb_defs.hpp wb_log.hpp
operator_filter_edge_laplacian.o: errors.hpp data_source_descriptor.hpp
operator_filter_edge_laplacian.o: histogram.hpp hough.hpp hough_accum.hpp
operator_filter_edge_laplacian.o: image.hpp bounds.hpp image_header.hpp
operator_filter_edge_laplacian.o: wb_data_format.hpp wb_data_type.hpp
operator_filter_edge_laplacian.o: wb_image_depth.hpp wb_repository_type.hpp
operator_filter_edge_laplacian.o: line_segment.hpp point.hpp
operator_filter_edge_laplacian.o: variance_stats.hpp theta.hpp wb_utils.hpp
operator_filter_edge_laplacian.o: hough_peak.hpp polar_line.hpp
operator_filter_edge_laplacian.o: wb_filename.hpp
operator_filter_edge_linear.o: kernel.hpp image.hpp bounds.hpp errors.hpp
operator_filter_edge_linear.o: image_header.hpp wb_data_format.hpp
operator_filter_edge_linear.o: wb_data_type.hpp wb_image_depth.hpp
operator_filter_edge_linear.o: wb_repository_type.hpp wb_defs.hpp
operator_filter_edge_linear.o: line_segment.hpp point.hpp wb_log.hpp
operator_filter_edge_linear.o: variance_stats.hpp wb_morphology_types.hpp
operator_filter_edge_linear.o: operator_utils.hpp data_source_descriptor.hpp
operator_filter_edge_linear.o: histogram.hpp hough.hpp hough_accum.hpp
operator_filter_edge_linear.o: theta.hpp wb_utils.hpp hough_peak.hpp
operator_filter_edge_linear.o: polar_line.hpp wb_filename.hpp
operator_filter_edge_linear.o: operator_filter_edge_linear.hpp operator.hpp
operator_filter_edge_linear.o: wb_linear_config_mask.hpp wb_config_mask.hpp
operator_filter_edge_prewitt.o: kernel.hpp image.hpp bounds.hpp errors.hpp
operator_filter_edge_prewitt.o: image_header.hpp wb_data_format.hpp
operator_filter_edge_prewitt.o: wb_data_type.hpp wb_image_depth.hpp
operator_filter_edge_prewitt.o: wb_repository_type.hpp wb_defs.hpp
operator_filter_edge_prewitt.o: line_segment.hpp point.hpp wb_log.hpp
operator_filter_edge_prewitt.o: variance_stats.hpp wb_morphology_types.hpp
operator_filter_edge_prewitt.o: operator_utils.hpp data_source_descriptor.hpp
operator_filter_edge_prewitt.o: histogram.hpp hough.hpp hough_accum.hpp
operator_filter_edge_prewitt.o: theta.hpp wb_utils.hpp hough_peak.hpp
operator_filter_edge_prewitt.o: polar_line.hpp wb_filename.hpp
operator_filter_edge_prewitt.o: operator_filter_edge_prewitt.hpp operator.hpp
operator_filter_edge_roberts.o: kernel.hpp image.hpp bounds.hpp errors.hpp
operator_filter_edge_roberts.o: image_header.hpp wb_data_format.hpp
operator_filter_edge_roberts.o: wb_data_type.hpp wb_image_depth.hpp
operator_filter_edge_roberts.o: wb_repository_type.hpp wb_defs.hpp
operator_filter_edge_roberts.o: line_segment.hpp point.hpp wb_log.hpp
operator_filter_edge_roberts.o: variance_stats.hpp wb_morphology_types.hpp
operator_filter_edge_roberts.o: operator_utils.hpp data_source_descriptor.hpp
operator_filter_edge_roberts.o: histogram.hpp hough.hpp hough_accum.hpp
operator_filter_edge_roberts.o: theta.hpp wb_utils.hpp hough_peak.hpp
operator_filter_edge_roberts.o: polar_line.hpp wb_filename.hpp
operator_filter_edge_roberts.o: operator_filter_edge_roberts.hpp operator.hpp
operator_filter_edge_sobel.o: kernel.hpp image.hpp bounds.hpp errors.hpp
operator_filter_edge_sobel.o: image_header.hpp wb_data_format.hpp
operator_filter_edge_sobel.o: wb_data_type.hpp wb_image_depth.hpp
operator_filter_edge_sobel.o: wb_repository_type.hpp wb_defs.hpp
operator_filter_edge_sobel.o: line_segment.hpp point.hpp wb_log.hpp
operator_filter_edge_sobel.o: variance_stats.hpp wb_morphology_types.hpp
operator_filter_edge_sobel.o: operator_utils.hpp data_source_descriptor.hpp
operator_filter_edge_sobel.o: histogram.hpp hough.hpp hough_accum.hpp
operator_filter_edge_sobel.o: theta.hpp wb_utils.hpp hough_peak.hpp
operator_filter_edge_sobel.o: polar_line.hpp wb_filename.hpp
operator_filter_edge_sobel.o: operator_filter_edge_sobel.hpp operator.hpp
operator_filter_image_morphology.o: kernel.hpp image.hpp bounds.hpp
operator_filter_image_morphology.o: errors.hpp image_header.hpp
operator_filter_image_morphology.o: wb_data_format.hpp wb_data_type.hpp
operator_filter_image_morphology.o: wb_image_depth.hpp wb_repository_type.hpp
operator_filter_image_morphology.o: wb_defs.hpp line_segment.hpp point.hpp
operator_filter_image_morphology.o: wb_log.hpp variance_stats.hpp
operator_filter_image_morphology.o: wb_morphology_types.hpp morphology.hpp
operator_filter_image_morphology.o: operator_utils.hpp
operator_filter_image_morphology.o: data_source_descriptor.hpp histogram.hpp
operator_filter_image_morphology.o: hough.hpp hough_accum.hpp theta.hpp
operator_filter_image_morphology.o: wb_utils.hpp hough_peak.hpp
operator_filter_image_morphology.o: polar_line.hpp wb_filename.hpp
operator_filter_image_morphology.o: operator_filter_image_morphology.hpp
operator_filter_image_morphology.o: operator.hpp
operator_filter_smooth_average.o: kernel.hpp image.hpp bounds.hpp errors.hpp
operator_filter_smooth_average.o: image_header.hpp wb_data_format.hpp
operator_filter_smooth_average.o: wb_data_type.hpp wb_image_depth.hpp
operator_filter_smooth_average.o: wb_repository_type.hpp wb_defs.hpp
operator_filter_smooth_average.o: line_segment.hpp point.hpp wb_log.hpp
operator_filter_smooth_average.o: variance_stats.hpp wb_morphology_types.hpp
operator_filter_smooth_average.o: operator_utils.hpp
operator_filter_smooth_average.o: data_source_descriptor.hpp histogram.hpp
operator_filter_smooth_average.o: hough.hpp hough_accum.hpp theta.hpp
operator_filter_smooth_average.o: wb_utils.hpp hough_peak.hpp polar_line.hpp
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
operator_filter_smooth_gaussian.o: data_source_descriptor.hpp histogram.hpp
operator_filter_smooth_gaussian.o: hough.hpp hough_accum.hpp theta.hpp
operator_filter_smooth_gaussian.o: wb_utils.hpp hough_peak.hpp polar_line.hpp
operator_filter_smooth_gaussian.o: wb_filename.hpp
operator_filter_smooth_gaussian.o: operator_filter_smooth_gaussian.hpp
operator_filter_smooth_gaussian.o: operator.hpp
operator_filter_smooth_median.o: operator_filter_smooth_median.hpp
operator_filter_smooth_median.o: operator.hpp wb_defs.hpp wb_log.hpp
operator_filter_smooth_median.o: errors.hpp data_source_descriptor.hpp
operator_filter_smooth_median.o: histogram.hpp hough.hpp hough_accum.hpp
operator_filter_smooth_median.o: image.hpp bounds.hpp image_header.hpp
operator_filter_smooth_median.o: wb_data_format.hpp wb_data_type.hpp
operator_filter_smooth_median.o: wb_image_depth.hpp wb_repository_type.hpp
operator_filter_smooth_median.o: line_segment.hpp point.hpp
operator_filter_smooth_median.o: variance_stats.hpp theta.hpp wb_utils.hpp
operator_filter_smooth_median.o: hough_peak.hpp polar_line.hpp
operator_filter_smooth_median.o: wb_filename.hpp
operator_histogram_hough_create.o: berkeley_db_data_source_descriptor.hpp
operator_histogram_hough_create.o: wb_image_depth.hpp
operator_histogram_hough_create.o: data_source_descriptor.hpp wb_defs.hpp
operator_histogram_hough_create.o: histogram.hpp errors.hpp hough.hpp
operator_histogram_hough_create.o: hough_accum.hpp image.hpp bounds.hpp
operator_histogram_hough_create.o: image_header.hpp wb_data_format.hpp
operator_histogram_hough_create.o: wb_data_type.hpp wb_repository_type.hpp
operator_histogram_hough_create.o: line_segment.hpp point.hpp wb_log.hpp
operator_histogram_hough_create.o: variance_stats.hpp theta.hpp wb_utils.hpp
operator_histogram_hough_create.o: hough_peak.hpp polar_line.hpp
operator_histogram_hough_create.o: wb_filename.hpp operator_utils.hpp
operator_histogram_hough_create.o: operator_histogram_hough_create.hpp
operator_histogram_hough_create.o: operator.hpp
operator_histogram_image_create.o: berkeley_db_data_source_descriptor.hpp
operator_histogram_image_create.o: wb_image_depth.hpp
operator_histogram_image_create.o: data_source_descriptor.hpp wb_defs.hpp
operator_histogram_image_create.o: histogram.hpp errors.hpp hough.hpp
operator_histogram_image_create.o: hough_accum.hpp image.hpp bounds.hpp
operator_histogram_image_create.o: image_header.hpp wb_data_format.hpp
operator_histogram_image_create.o: wb_data_type.hpp wb_repository_type.hpp
operator_histogram_image_create.o: line_segment.hpp point.hpp wb_log.hpp
operator_histogram_image_create.o: variance_stats.hpp theta.hpp wb_utils.hpp
operator_histogram_image_create.o: hough_peak.hpp polar_line.hpp
operator_histogram_image_create.o: wb_filename.hpp operator_utils.hpp
operator_histogram_image_create.o: operator_histogram_image_create.hpp
operator_histogram_image_create.o: operator.hpp
operator_histogram_peak_detect.o: operator_histogram_peak_detect.hpp
operator_histogram_peak_detect.o: operator.hpp wb_defs.hpp wb_log.hpp
operator_histogram_peak_detect.o: errors.hpp data_source_descriptor.hpp
operator_histogram_peak_detect.o: histogram.hpp hough.hpp hough_accum.hpp
operator_histogram_peak_detect.o: image.hpp bounds.hpp image_header.hpp
operator_histogram_peak_detect.o: wb_data_format.hpp wb_data_type.hpp
operator_histogram_peak_detect.o: wb_image_depth.hpp wb_repository_type.hpp
operator_histogram_peak_detect.o: line_segment.hpp point.hpp
operator_histogram_peak_detect.o: variance_stats.hpp theta.hpp wb_utils.hpp
operator_histogram_peak_detect.o: hough_peak.hpp polar_line.hpp
operator_histogram_peak_detect.o: wb_filename.hpp
operator_hough_draw_line.o: hough.hpp hough_accum.hpp image.hpp bounds.hpp
operator_hough_draw_line.o: errors.hpp image_header.hpp wb_data_format.hpp
operator_hough_draw_line.o: wb_data_type.hpp wb_image_depth.hpp
operator_hough_draw_line.o: wb_repository_type.hpp wb_defs.hpp
operator_hough_draw_line.o: line_segment.hpp point.hpp wb_log.hpp
operator_hough_draw_line.o: variance_stats.hpp theta.hpp wb_utils.hpp
operator_hough_draw_line.o: hough_peak.hpp polar_line.hpp operator_utils.hpp
operator_hough_draw_line.o: data_source_descriptor.hpp histogram.hpp
operator_hough_draw_line.o: wb_filename.hpp wb_window.hpp
operator_hough_draw_line.o: operator_hough_draw_line.hpp operator.hpp
operator_hough_draw_lines.o: hough.hpp hough_accum.hpp image.hpp bounds.hpp
operator_hough_draw_lines.o: errors.hpp image_header.hpp wb_data_format.hpp
operator_hough_draw_lines.o: wb_data_type.hpp wb_image_depth.hpp
operator_hough_draw_lines.o: wb_repository_type.hpp wb_defs.hpp
operator_hough_draw_lines.o: line_segment.hpp point.hpp wb_log.hpp
operator_hough_draw_lines.o: variance_stats.hpp theta.hpp wb_utils.hpp
operator_hough_draw_lines.o: hough_peak.hpp polar_line.hpp operator_utils.hpp
operator_hough_draw_lines.o: data_source_descriptor.hpp histogram.hpp
operator_hough_draw_lines.o: wb_filename.hpp wb_window.hpp
operator_hough_draw_lines.o: operator_hough_draw_lines.hpp operator.hpp
operator_hough_image_create.o: hough.hpp hough_accum.hpp image.hpp bounds.hpp
operator_hough_image_create.o: errors.hpp image_header.hpp wb_data_format.hpp
operator_hough_image_create.o: wb_data_type.hpp wb_image_depth.hpp
operator_hough_image_create.o: wb_repository_type.hpp wb_defs.hpp
operator_hough_image_create.o: line_segment.hpp point.hpp wb_log.hpp
operator_hough_image_create.o: variance_stats.hpp theta.hpp wb_utils.hpp
operator_hough_image_create.o: hough_peak.hpp polar_line.hpp
operator_hough_image_create.o: operator_utils.hpp data_source_descriptor.hpp
operator_hough_image_create.o: histogram.hpp wb_filename.hpp
operator_hough_image_create.o: operator_hough_image_create.hpp operator.hpp
operator_hough_peak_detect.o: operator_utils.hpp data_source_descriptor.hpp
operator_hough_peak_detect.o: wb_defs.hpp histogram.hpp errors.hpp hough.hpp
operator_hough_peak_detect.o: hough_accum.hpp image.hpp bounds.hpp
operator_hough_peak_detect.o: image_header.hpp wb_data_format.hpp
operator_hough_peak_detect.o: wb_data_type.hpp wb_image_depth.hpp
operator_hough_peak_detect.o: wb_repository_type.hpp line_segment.hpp
operator_hough_peak_detect.o: point.hpp wb_log.hpp variance_stats.hpp
operator_hough_peak_detect.o: theta.hpp wb_utils.hpp hough_peak.hpp
operator_hough_peak_detect.o: polar_line.hpp wb_filename.hpp
operator_hough_peak_detect.o: operator_hough_peak_detect.hpp operator.hpp
operator_transform_image_combine.o: operator_transform_image_combine.hpp
operator_transform_image_combine.o: operator.hpp wb_defs.hpp wb_log.hpp
operator_transform_image_combine.o: errors.hpp data_source_descriptor.hpp
operator_transform_image_combine.o: histogram.hpp hough.hpp hough_accum.hpp
operator_transform_image_combine.o: image.hpp bounds.hpp image_header.hpp
operator_transform_image_combine.o: wb_data_format.hpp wb_data_type.hpp
operator_transform_image_combine.o: wb_image_depth.hpp wb_repository_type.hpp
operator_transform_image_combine.o: line_segment.hpp point.hpp
operator_transform_image_combine.o: variance_stats.hpp theta.hpp wb_utils.hpp
operator_transform_image_combine.o: hough_peak.hpp polar_line.hpp
operator_transform_image_combine.o: wb_filename.hpp operator_utils.hpp
operator_transform_image_copy.o: operator_transform_image_copy.hpp
operator_transform_image_copy.o: operator.hpp wb_defs.hpp wb_log.hpp
operator_transform_image_copy.o: errors.hpp data_source_descriptor.hpp
operator_transform_image_copy.o: histogram.hpp hough.hpp hough_accum.hpp
operator_transform_image_copy.o: image.hpp bounds.hpp image_header.hpp
operator_transform_image_copy.o: wb_data_format.hpp wb_data_type.hpp
operator_transform_image_copy.o: wb_image_depth.hpp wb_repository_type.hpp
operator_transform_image_copy.o: line_segment.hpp point.hpp
operator_transform_image_copy.o: variance_stats.hpp theta.hpp wb_utils.hpp
operator_transform_image_copy.o: hough_peak.hpp polar_line.hpp
operator_transform_image_copy.o: wb_filename.hpp
operator_transform_image_create.o: operator_transform_image_create.hpp
operator_transform_image_create.o: operator.hpp wb_defs.hpp wb_log.hpp
operator_transform_image_create.o: errors.hpp data_source_descriptor.hpp
operator_transform_image_create.o: histogram.hpp hough.hpp hough_accum.hpp
operator_transform_image_create.o: image.hpp bounds.hpp image_header.hpp
operator_transform_image_create.o: wb_data_format.hpp wb_data_type.hpp
operator_transform_image_create.o: wb_image_depth.hpp wb_repository_type.hpp
operator_transform_image_create.o: line_segment.hpp point.hpp
operator_transform_image_create.o: variance_stats.hpp theta.hpp wb_utils.hpp
operator_transform_image_create.o: hough_peak.hpp polar_line.hpp
operator_transform_image_create.o: wb_filename.hpp operator_utils.hpp
operator_transform_intensity_map.o: operator_transform_intensity_map.hpp
operator_transform_intensity_map.o: operator.hpp wb_defs.hpp wb_log.hpp
operator_transform_intensity_map.o: errors.hpp data_source_descriptor.hpp
operator_transform_intensity_map.o: histogram.hpp hough.hpp hough_accum.hpp
operator_transform_intensity_map.o: image.hpp bounds.hpp image_header.hpp
operator_transform_intensity_map.o: wb_data_format.hpp wb_data_type.hpp
operator_transform_intensity_map.o: wb_image_depth.hpp wb_repository_type.hpp
operator_transform_intensity_map.o: line_segment.hpp point.hpp
operator_transform_intensity_map.o: variance_stats.hpp theta.hpp wb_utils.hpp
operator_transform_intensity_map.o: hough_peak.hpp polar_line.hpp
operator_transform_intensity_map.o: wb_filename.hpp operator_utils.hpp
operator_utils.o: data_source_descriptor.hpp wb_defs.hpp histogram.hpp
operator_utils.o: errors.hpp hough.hpp hough_accum.hpp image.hpp bounds.hpp
operator_utils.o: image_header.hpp wb_data_format.hpp wb_data_type.hpp
operator_utils.o: wb_image_depth.hpp wb_repository_type.hpp line_segment.hpp
operator_utils.o: point.hpp wb_log.hpp variance_stats.hpp theta.hpp
operator_utils.o: wb_utils.hpp hough_peak.hpp polar_line.hpp wb_filename.hpp
operator_utils.o: operator_utils.hpp
pearsons_correlation.o: pearsons_correlation.hpp image.hpp bounds.hpp
pearsons_correlation.o: errors.hpp image_header.hpp wb_data_format.hpp
pearsons_correlation.o: wb_data_type.hpp wb_image_depth.hpp
pearsons_correlation.o: wb_repository_type.hpp wb_defs.hpp line_segment.hpp
pearsons_correlation.o: point.hpp wb_log.hpp variance_stats.hpp kernel.hpp
pearsons_correlation.o: wb_morphology_types.hpp one_pass_mean.hpp
point.o: theta.hpp wb_utils.hpp wb_data_format.hpp wb_data_type.hpp
point.o: wb_image_depth.hpp wb_repository_type.hpp errors.hpp wb_defs.hpp
point.o: wb_window.hpp line_segment.hpp point.hpp wb_log.hpp polar_line.hpp
polar_line.o: file_utils.hpp errors.hpp point.hpp theta.hpp wb_utils.hpp
polar_line.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
polar_line.o: wb_repository_type.hpp wb_defs.hpp wb_window.hpp
polar_line.o: line_segment.hpp wb_log.hpp polar_line.hpp
runtime.o: runtime.hpp wb_utils.hpp wb_data_format.hpp wb_data_type.hpp
runtime.o: wb_image_depth.hpp wb_repository_type.hpp errors.hpp wb_defs.hpp
runtime.o: wb_version.hpp
theta.o: theta.hpp wb_utils.hpp wb_data_format.hpp wb_data_type.hpp
theta.o: wb_image_depth.hpp wb_repository_type.hpp errors.hpp wb_defs.hpp
theta.o: theta_static.hpp
variance_stats.o: wb_utils.hpp wb_data_format.hpp wb_data_type.hpp
variance_stats.o: wb_image_depth.hpp wb_repository_type.hpp errors.hpp
variance_stats.o: wb_defs.hpp variance_stats.hpp bounds.hpp
wb_data_format.o: wb_data_format.hpp
wb_data_type.o: wb_data_type.hpp
wb_filename.o: errors.hpp wb_utils.hpp wb_data_format.hpp wb_data_type.hpp
wb_filename.o: wb_image_depth.hpp wb_repository_type.hpp wb_defs.hpp
wb_filename.o: wb_filename.hpp
wb_image_depth.o: wb_image_depth.hpp
wb_json_utils.o: wb_json_utils.hpp errors.hpp
wb_linear_config_mask.o: point.hpp wb_window.hpp errors.hpp line_segment.hpp
wb_linear_config_mask.o: wb_log.hpp polar_line.hpp theta.hpp wb_utils.hpp
wb_linear_config_mask.o: wb_data_format.hpp wb_data_type.hpp
wb_linear_config_mask.o: wb_image_depth.hpp wb_repository_type.hpp
wb_linear_config_mask.o: wb_defs.hpp wb_linear_config_mask.hpp
wb_linear_config_mask.o: wb_config_mask.hpp
wb_log.o: errors.hpp wb_log.hpp
wb_morphology_types.o: wb_morphology_types.hpp
wb_repository_type.o: wb_repository_type.hpp
wb_utils.o: errors.hpp wb_defs.hpp wb_utils.hpp wb_data_format.hpp
wb_utils.o: wb_data_type.hpp wb_image_depth.hpp wb_repository_type.hpp
wb_window.o: wb_window.hpp errors.hpp line_segment.hpp point.hpp wb_log.hpp
wb_window.o: polar_line.hpp theta.hpp wb_utils.hpp wb_data_format.hpp
wb_window.o: wb_data_type.hpp wb_image_depth.hpp wb_repository_type.hpp
wb_window.o: wb_defs.hpp
