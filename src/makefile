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
  wb_data_format.o \
  wb_data_type.o \
  wb_image_depth.o \
  wb_repository_type.o \
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
  operator_dispatcher.o \
  operator_filter_edge_gaussian.o \
  operator_filter_edge_kirsch.o \
  operator_filter_edge_laplacian.o \
  operator_filter_edge_prewitt.o \
  operator_filter_edge_roberts.o \
  operator_filter_edge_sobel.o \
  operator_filter_smooth_average.o \
  operator_filter_smooth_gaussian.o \
  operator_filter_smooth_median.o \
  operator_histogram_hough_create.o \
  operator_histogram_image_create.o \
  operator_histogram_peak_detect.o \
  operator_hough_draw_line.o \
  operator_hough_image_create.o \
  operator_hough_peak_detect.o \
  operator_transform_image_copy.o \
  operator_transform_image_morphology.o \
  operator_transform_intensity_map.o \
  operator_utils.o \
  point.o \
  polar_line.o \
  variance_stats.o \
  wb_filename.o \
  wb_json_utils.o \
  wb_log.o \
  wb_utils.o 

PROGRAMS = \
  image-copy \
  image-dump \
  image-info \
  image-map \
  cv-workbench 

%.o: %.cpp %.hpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

all: $(PROGRAMS)

image-copy: image-copy.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

image-dump: image-dump.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

image-info: image-info.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

image-map: image-map.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

cv-workbench : cv-workbench.o $(SRCOBJS)
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

berkeley_db_data_source_descriptor.o: wb_data_format.hpp wb_data_type.hpp
berkeley_db_data_source_descriptor.o: wb_repository_type.hpp
berkeley_db_data_source_descriptor.o: wb_json_utils.hpp errors.hpp
berkeley_db_data_source_descriptor.o: data_source_descriptor.hpp wb_defs.hpp
berkeley_db_data_source_descriptor.o: histogram.hpp hough.hpp hough_accum.hpp
berkeley_db_data_source_descriptor.o: file_utils.hpp image.hpp bounds.hpp
berkeley_db_data_source_descriptor.o: image_header.hpp wb_image_depth.hpp
berkeley_db_data_source_descriptor.o: line_segment.hpp point.hpp
berkeley_db_data_source_descriptor.o: variance_stats.hpp wb_utils.hpp
berkeley_db_data_source_descriptor.o: polar_line.hpp wb_filename.hpp
berkeley_db_data_source_descriptor.o: berkeley_db_data_source_descriptor.hpp
bounds.o: bounds.hpp
cv-workbench.o: wb_log.hpp errors.hpp experiment.hpp wb_defs.hpp image.hpp
cv-workbench.o: bounds.hpp image_header.hpp wb_data_format.hpp
cv-workbench.o: wb_data_type.hpp wb_image_depth.hpp wb_repository_type.hpp
cv-workbench.o: line_segment.hpp point.hpp variance_stats.hpp histogram.hpp
cv-workbench.o: hough.hpp hough_accum.hpp file_utils.hpp wb_utils.hpp
cv-workbench.o: polar_line.hpp wb_filename.hpp experiment_step.hpp
cv-workbench.o: data_source_descriptor.hpp wb_json_utils.hpp
data_source_descriptor.o: wb_data_format.hpp wb_data_type.hpp
data_source_descriptor.o: wb_repository_type.hpp data_source_descriptor.hpp
data_source_descriptor.o: wb_defs.hpp histogram.hpp errors.hpp hough.hpp
data_source_descriptor.o: hough_accum.hpp file_utils.hpp image.hpp bounds.hpp
data_source_descriptor.o: image_header.hpp wb_image_depth.hpp
data_source_descriptor.o: line_segment.hpp point.hpp variance_stats.hpp
data_source_descriptor.o: wb_utils.hpp polar_line.hpp wb_filename.hpp
errors.o: errors.hpp
experiment.o: experiment.hpp wb_defs.hpp errors.hpp image.hpp bounds.hpp
experiment.o: image_header.hpp wb_data_format.hpp wb_data_type.hpp
experiment.o: wb_image_depth.hpp wb_repository_type.hpp line_segment.hpp
experiment.o: point.hpp variance_stats.hpp histogram.hpp hough.hpp
experiment.o: hough_accum.hpp file_utils.hpp wb_utils.hpp polar_line.hpp
experiment.o: wb_filename.hpp experiment_step.hpp data_source_descriptor.hpp
experiment.o: wb_json_utils.hpp
experiment_step.o: wb_data_format.hpp wb_data_type.hpp wb_repository_type.hpp
experiment_step.o: data_source_descriptor.hpp wb_defs.hpp histogram.hpp
experiment_step.o: errors.hpp hough.hpp hough_accum.hpp file_utils.hpp
experiment_step.o: image.hpp bounds.hpp image_header.hpp wb_image_depth.hpp
experiment_step.o: line_segment.hpp point.hpp variance_stats.hpp wb_utils.hpp
experiment_step.o: polar_line.hpp wb_filename.hpp
experiment_step.o: berkeley_db_data_source_descriptor.hpp experiment_step.hpp
experiment_step.o: experiment_step_data_source_descriptor.hpp
experiment_step.o: filesystem_data_source_descriptor.hpp
experiment_step.o: internet_data_source_descriptor.hpp operator.hpp
experiment_step.o: operator_dispatcher.hpp wb_json_utils.hpp
experiment_step_data_source_descriptor.o: wb_data_format.hpp wb_data_type.hpp
experiment_step_data_source_descriptor.o: wb_repository_type.hpp
experiment_step_data_source_descriptor.o: wb_json_utils.hpp errors.hpp
experiment_step_data_source_descriptor.o: data_source_descriptor.hpp
experiment_step_data_source_descriptor.o: wb_defs.hpp histogram.hpp hough.hpp
experiment_step_data_source_descriptor.o: hough_accum.hpp file_utils.hpp
experiment_step_data_source_descriptor.o: image.hpp bounds.hpp
experiment_step_data_source_descriptor.o: image_header.hpp wb_image_depth.hpp
experiment_step_data_source_descriptor.o: line_segment.hpp point.hpp
experiment_step_data_source_descriptor.o: variance_stats.hpp wb_utils.hpp
experiment_step_data_source_descriptor.o: polar_line.hpp wb_filename.hpp
experiment_step_data_source_descriptor.o: experiment_step_data_source_descriptor.hpp
filesystem_data_source_descriptor.o: wb_data_format.hpp wb_data_type.hpp
filesystem_data_source_descriptor.o: wb_repository_type.hpp wb_json_utils.hpp
filesystem_data_source_descriptor.o: errors.hpp wb_utils.hpp
filesystem_data_source_descriptor.o: wb_image_depth.hpp wb_defs.hpp
filesystem_data_source_descriptor.o: data_source_descriptor.hpp histogram.hpp
filesystem_data_source_descriptor.o: hough.hpp hough_accum.hpp file_utils.hpp
filesystem_data_source_descriptor.o: image.hpp bounds.hpp image_header.hpp
filesystem_data_source_descriptor.o: line_segment.hpp point.hpp
filesystem_data_source_descriptor.o: variance_stats.hpp polar_line.hpp
filesystem_data_source_descriptor.o: wb_filename.hpp
filesystem_data_source_descriptor.o: filesystem_data_source_descriptor.hpp
file_utils.o: file_utils.hpp
histogram.o: errors.hpp file_utils.hpp wb_utils.hpp wb_data_format.hpp
histogram.o: wb_data_type.hpp wb_image_depth.hpp wb_repository_type.hpp
histogram.o: wb_defs.hpp histogram.hpp hough.hpp hough_accum.hpp image.hpp
histogram.o: bounds.hpp image_header.hpp line_segment.hpp point.hpp
histogram.o: variance_stats.hpp polar_line.hpp wb_filename.hpp
hough_accum.o: image.hpp bounds.hpp errors.hpp image_header.hpp
hough_accum.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
hough_accum.o: wb_repository_type.hpp wb_defs.hpp line_segment.hpp point.hpp
hough_accum.o: variance_stats.hpp polar_line.hpp hough_accum.hpp
hough_accum.o: file_utils.hpp wb_utils.hpp
hough.o: errors.hpp file_utils.hpp wb_utils.hpp wb_data_format.hpp
hough.o: wb_data_type.hpp wb_image_depth.hpp wb_repository_type.hpp
hough.o: wb_defs.hpp hough_accum.hpp image.hpp bounds.hpp image_header.hpp
hough.o: line_segment.hpp point.hpp variance_stats.hpp polar_line.hpp
hough.o: hough.hpp
image-copy.o: errors.hpp image.hpp bounds.hpp image_header.hpp
image-copy.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
image-copy.o: wb_repository_type.hpp wb_defs.hpp line_segment.hpp point.hpp
image-copy.o: variance_stats.hpp wb_filename.hpp wb_utils.hpp
image.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
image.o: wb_repository_type.hpp image.hpp bounds.hpp errors.hpp
image.o: image_header.hpp wb_defs.hpp line_segment.hpp point.hpp
image.o: variance_stats.hpp wb_utils.hpp
image-dump.o: errors.hpp image.hpp bounds.hpp image_header.hpp
image-dump.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
image-dump.o: wb_repository_type.hpp wb_defs.hpp line_segment.hpp point.hpp
image-dump.o: variance_stats.hpp wb_filename.hpp wb_utils.hpp
image_header.o: wb_utils.hpp wb_data_format.hpp wb_data_type.hpp
image_header.o: wb_image_depth.hpp wb_repository_type.hpp errors.hpp
image_header.o: wb_defs.hpp image_header.hpp
image-info.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
image-info.o: wb_repository_type.hpp errors.hpp file_utils.hpp histogram.hpp
image-info.o: hough.hpp hough_accum.hpp image.hpp bounds.hpp image_header.hpp
image-info.o: wb_defs.hpp line_segment.hpp point.hpp variance_stats.hpp
image-info.o: wb_utils.hpp polar_line.hpp wb_filename.hpp
image-map.o: errors.hpp image.hpp bounds.hpp image_header.hpp
image-map.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
image-map.o: wb_repository_type.hpp wb_defs.hpp line_segment.hpp point.hpp
image-map.o: variance_stats.hpp wb_filename.hpp wb_utils.hpp
image_point_list.o: image_point_list.hpp point.hpp
internet_data_source_descriptor.o: wb_json_utils.hpp errors.hpp
internet_data_source_descriptor.o: data_source_descriptor.hpp wb_defs.hpp
internet_data_source_descriptor.o: histogram.hpp hough.hpp hough_accum.hpp
internet_data_source_descriptor.o: file_utils.hpp image.hpp bounds.hpp
internet_data_source_descriptor.o: image_header.hpp wb_data_format.hpp
internet_data_source_descriptor.o: wb_data_type.hpp wb_image_depth.hpp
internet_data_source_descriptor.o: wb_repository_type.hpp line_segment.hpp
internet_data_source_descriptor.o: point.hpp variance_stats.hpp wb_utils.hpp
internet_data_source_descriptor.o: polar_line.hpp wb_filename.hpp
internet_data_source_descriptor.o: internet_data_source_descriptor.hpp
kernel.o: wb_utils.hpp wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
kernel.o: wb_repository_type.hpp errors.hpp wb_defs.hpp kernel.hpp image.hpp
kernel.o: bounds.hpp image_header.hpp line_segment.hpp point.hpp
kernel.o: variance_stats.hpp
line_segment.o: line_segment.hpp point.hpp
operator.o: operator.hpp wb_defs.hpp data_source_descriptor.hpp histogram.hpp
operator.o: errors.hpp hough.hpp hough_accum.hpp file_utils.hpp image.hpp
operator.o: bounds.hpp image_header.hpp wb_data_format.hpp wb_data_type.hpp
operator.o: wb_image_depth.hpp wb_repository_type.hpp line_segment.hpp
operator.o: point.hpp variance_stats.hpp wb_utils.hpp polar_line.hpp
operator.o: wb_filename.hpp
operator_dispatcher.o: operator_filter_edge_gaussian.hpp operator.hpp
operator_dispatcher.o: wb_defs.hpp data_source_descriptor.hpp histogram.hpp
operator_dispatcher.o: errors.hpp hough.hpp hough_accum.hpp file_utils.hpp
operator_dispatcher.o: image.hpp bounds.hpp image_header.hpp
operator_dispatcher.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
operator_dispatcher.o: wb_repository_type.hpp line_segment.hpp point.hpp
operator_dispatcher.o: variance_stats.hpp wb_utils.hpp polar_line.hpp
operator_dispatcher.o: wb_filename.hpp operator_filter_edge_kirsch.hpp
operator_dispatcher.o: operator_filter_edge_laplacian.hpp
operator_dispatcher.o: operator_filter_edge_prewitt.hpp
operator_dispatcher.o: operator_filter_edge_roberts.hpp
operator_dispatcher.o: operator_filter_edge_sobel.hpp
operator_dispatcher.o: operator_filter_smooth_average.hpp
operator_dispatcher.o: operator_filter_smooth_gaussian.hpp
operator_dispatcher.o: operator_filter_smooth_median.hpp
operator_dispatcher.o: operator_histogram_hough_create.hpp
operator_dispatcher.o: operator_histogram_image_create.hpp
operator_dispatcher.o: operator_histogram_peak_detect.hpp
operator_dispatcher.o: operator_hough_draw_line.hpp
operator_dispatcher.o: operator_hough_image_create.hpp
operator_dispatcher.o: operator_hough_peak_detect.hpp
operator_dispatcher.o: operator_transform_image_copy.hpp
operator_dispatcher.o: operator_transform_image_morphology.hpp
operator_dispatcher.o: operator_transform_intensity_map.hpp
operator_dispatcher.o: operator_dispatcher.hpp
operator_filter_edge_gaussian.o: operator_filter_edge_gaussian.hpp
operator_filter_edge_gaussian.o: operator.hpp wb_defs.hpp
operator_filter_edge_gaussian.o: data_source_descriptor.hpp histogram.hpp
operator_filter_edge_gaussian.o: errors.hpp hough.hpp hough_accum.hpp
operator_filter_edge_gaussian.o: file_utils.hpp image.hpp bounds.hpp
operator_filter_edge_gaussian.o: image_header.hpp wb_data_format.hpp
operator_filter_edge_gaussian.o: wb_data_type.hpp wb_image_depth.hpp
operator_filter_edge_gaussian.o: wb_repository_type.hpp line_segment.hpp
operator_filter_edge_gaussian.o: point.hpp variance_stats.hpp wb_utils.hpp
operator_filter_edge_gaussian.o: polar_line.hpp wb_filename.hpp
operator_filter_edge_kirsch.o: kernel.hpp image.hpp bounds.hpp errors.hpp
operator_filter_edge_kirsch.o: image_header.hpp wb_data_format.hpp
operator_filter_edge_kirsch.o: wb_data_type.hpp wb_image_depth.hpp
operator_filter_edge_kirsch.o: wb_repository_type.hpp wb_defs.hpp
operator_filter_edge_kirsch.o: line_segment.hpp point.hpp variance_stats.hpp
operator_filter_edge_kirsch.o: operator_utils.hpp
operator_filter_edge_kirsch.o: operator_filter_edge_kirsch.hpp operator.hpp
operator_filter_edge_kirsch.o: data_source_descriptor.hpp histogram.hpp
operator_filter_edge_kirsch.o: hough.hpp hough_accum.hpp file_utils.hpp
operator_filter_edge_kirsch.o: wb_utils.hpp polar_line.hpp wb_filename.hpp
operator_filter_edge_laplacian.o: operator_filter_edge_laplacian.hpp
operator_filter_edge_laplacian.o: operator.hpp wb_defs.hpp
operator_filter_edge_laplacian.o: data_source_descriptor.hpp histogram.hpp
operator_filter_edge_laplacian.o: errors.hpp hough.hpp hough_accum.hpp
operator_filter_edge_laplacian.o: file_utils.hpp image.hpp bounds.hpp
operator_filter_edge_laplacian.o: image_header.hpp wb_data_format.hpp
operator_filter_edge_laplacian.o: wb_data_type.hpp wb_image_depth.hpp
operator_filter_edge_laplacian.o: wb_repository_type.hpp line_segment.hpp
operator_filter_edge_laplacian.o: point.hpp variance_stats.hpp wb_utils.hpp
operator_filter_edge_laplacian.o: polar_line.hpp wb_filename.hpp
operator_filter_edge_prewitt.o: kernel.hpp image.hpp bounds.hpp errors.hpp
operator_filter_edge_prewitt.o: image_header.hpp wb_data_format.hpp
operator_filter_edge_prewitt.o: wb_data_type.hpp wb_image_depth.hpp
operator_filter_edge_prewitt.o: wb_repository_type.hpp wb_defs.hpp
operator_filter_edge_prewitt.o: line_segment.hpp point.hpp variance_stats.hpp
operator_filter_edge_prewitt.o: operator_utils.hpp
operator_filter_edge_prewitt.o: operator_filter_edge_prewitt.hpp operator.hpp
operator_filter_edge_prewitt.o: data_source_descriptor.hpp histogram.hpp
operator_filter_edge_prewitt.o: hough.hpp hough_accum.hpp file_utils.hpp
operator_filter_edge_prewitt.o: wb_utils.hpp polar_line.hpp wb_filename.hpp
operator_filter_edge_roberts.o: kernel.hpp image.hpp bounds.hpp errors.hpp
operator_filter_edge_roberts.o: image_header.hpp wb_data_format.hpp
operator_filter_edge_roberts.o: wb_data_type.hpp wb_image_depth.hpp
operator_filter_edge_roberts.o: wb_repository_type.hpp wb_defs.hpp
operator_filter_edge_roberts.o: line_segment.hpp point.hpp variance_stats.hpp
operator_filter_edge_roberts.o: operator_utils.hpp
operator_filter_edge_roberts.o: operator_filter_edge_roberts.hpp operator.hpp
operator_filter_edge_roberts.o: data_source_descriptor.hpp histogram.hpp
operator_filter_edge_roberts.o: hough.hpp hough_accum.hpp file_utils.hpp
operator_filter_edge_roberts.o: wb_utils.hpp polar_line.hpp wb_filename.hpp
operator_filter_edge_sobel.o: kernel.hpp image.hpp bounds.hpp errors.hpp
operator_filter_edge_sobel.o: image_header.hpp wb_data_format.hpp
operator_filter_edge_sobel.o: wb_data_type.hpp wb_image_depth.hpp
operator_filter_edge_sobel.o: wb_repository_type.hpp wb_defs.hpp
operator_filter_edge_sobel.o: line_segment.hpp point.hpp variance_stats.hpp
operator_filter_edge_sobel.o: operator_utils.hpp
operator_filter_edge_sobel.o: operator_filter_edge_sobel.hpp operator.hpp
operator_filter_edge_sobel.o: data_source_descriptor.hpp histogram.hpp
operator_filter_edge_sobel.o: hough.hpp hough_accum.hpp file_utils.hpp
operator_filter_edge_sobel.o: wb_utils.hpp polar_line.hpp wb_filename.hpp
operator_filter_smooth_average.o: operator_filter_smooth_average.hpp
operator_filter_smooth_average.o: operator.hpp wb_defs.hpp
operator_filter_smooth_average.o: data_source_descriptor.hpp histogram.hpp
operator_filter_smooth_average.o: errors.hpp hough.hpp hough_accum.hpp
operator_filter_smooth_average.o: file_utils.hpp image.hpp bounds.hpp
operator_filter_smooth_average.o: image_header.hpp wb_data_format.hpp
operator_filter_smooth_average.o: wb_data_type.hpp wb_image_depth.hpp
operator_filter_smooth_average.o: wb_repository_type.hpp line_segment.hpp
operator_filter_smooth_average.o: point.hpp variance_stats.hpp wb_utils.hpp
operator_filter_smooth_average.o: polar_line.hpp wb_filename.hpp
operator_filter_smooth_gaussian.o: operator_filter_smooth_gaussian.hpp
operator_filter_smooth_gaussian.o: operator.hpp wb_defs.hpp
operator_filter_smooth_gaussian.o: data_source_descriptor.hpp histogram.hpp
operator_filter_smooth_gaussian.o: errors.hpp hough.hpp hough_accum.hpp
operator_filter_smooth_gaussian.o: file_utils.hpp image.hpp bounds.hpp
operator_filter_smooth_gaussian.o: image_header.hpp wb_data_format.hpp
operator_filter_smooth_gaussian.o: wb_data_type.hpp wb_image_depth.hpp
operator_filter_smooth_gaussian.o: wb_repository_type.hpp line_segment.hpp
operator_filter_smooth_gaussian.o: point.hpp variance_stats.hpp wb_utils.hpp
operator_filter_smooth_gaussian.o: polar_line.hpp wb_filename.hpp
operator_filter_smooth_median.o: operator_filter_smooth_median.hpp
operator_filter_smooth_median.o: operator.hpp wb_defs.hpp
operator_filter_smooth_median.o: data_source_descriptor.hpp histogram.hpp
operator_filter_smooth_median.o: errors.hpp hough.hpp hough_accum.hpp
operator_filter_smooth_median.o: file_utils.hpp image.hpp bounds.hpp
operator_filter_smooth_median.o: image_header.hpp wb_data_format.hpp
operator_filter_smooth_median.o: wb_data_type.hpp wb_image_depth.hpp
operator_filter_smooth_median.o: wb_repository_type.hpp line_segment.hpp
operator_filter_smooth_median.o: point.hpp variance_stats.hpp wb_utils.hpp
operator_filter_smooth_median.o: polar_line.hpp wb_filename.hpp
operator_histogram_hough_create.o: berkeley_db_data_source_descriptor.hpp
operator_histogram_hough_create.o: wb_image_depth.hpp
operator_histogram_hough_create.o: data_source_descriptor.hpp wb_defs.hpp
operator_histogram_hough_create.o: histogram.hpp errors.hpp hough.hpp
operator_histogram_hough_create.o: hough_accum.hpp file_utils.hpp image.hpp
operator_histogram_hough_create.o: bounds.hpp image_header.hpp
operator_histogram_hough_create.o: wb_data_format.hpp wb_data_type.hpp
operator_histogram_hough_create.o: wb_repository_type.hpp line_segment.hpp
operator_histogram_hough_create.o: point.hpp variance_stats.hpp wb_utils.hpp
operator_histogram_hough_create.o: polar_line.hpp wb_filename.hpp
operator_histogram_hough_create.o: operator_utils.hpp
operator_histogram_hough_create.o: operator_histogram_hough_create.hpp
operator_histogram_hough_create.o: operator.hpp
operator_histogram_image_create.o: berkeley_db_data_source_descriptor.hpp
operator_histogram_image_create.o: wb_image_depth.hpp
operator_histogram_image_create.o: data_source_descriptor.hpp wb_defs.hpp
operator_histogram_image_create.o: histogram.hpp errors.hpp hough.hpp
operator_histogram_image_create.o: hough_accum.hpp file_utils.hpp image.hpp
operator_histogram_image_create.o: bounds.hpp image_header.hpp
operator_histogram_image_create.o: wb_data_format.hpp wb_data_type.hpp
operator_histogram_image_create.o: wb_repository_type.hpp line_segment.hpp
operator_histogram_image_create.o: point.hpp variance_stats.hpp wb_utils.hpp
operator_histogram_image_create.o: polar_line.hpp wb_filename.hpp
operator_histogram_image_create.o: operator_utils.hpp
operator_histogram_image_create.o: operator_histogram_image_create.hpp
operator_histogram_image_create.o: operator.hpp
operator_histogram_peak_detect.o: operator_histogram_peak_detect.hpp
operator_histogram_peak_detect.o: operator.hpp wb_defs.hpp
operator_histogram_peak_detect.o: data_source_descriptor.hpp histogram.hpp
operator_histogram_peak_detect.o: errors.hpp hough.hpp hough_accum.hpp
operator_histogram_peak_detect.o: file_utils.hpp image.hpp bounds.hpp
operator_histogram_peak_detect.o: image_header.hpp wb_data_format.hpp
operator_histogram_peak_detect.o: wb_data_type.hpp wb_image_depth.hpp
operator_histogram_peak_detect.o: wb_repository_type.hpp line_segment.hpp
operator_histogram_peak_detect.o: point.hpp variance_stats.hpp wb_utils.hpp
operator_histogram_peak_detect.o: polar_line.hpp wb_filename.hpp
operator_hough_draw_line.o: hough.hpp errors.hpp hough_accum.hpp
operator_hough_draw_line.o: file_utils.hpp image.hpp bounds.hpp
operator_hough_draw_line.o: image_header.hpp wb_data_format.hpp
operator_hough_draw_line.o: wb_data_type.hpp wb_image_depth.hpp
operator_hough_draw_line.o: wb_repository_type.hpp wb_defs.hpp
operator_hough_draw_line.o: line_segment.hpp point.hpp variance_stats.hpp
operator_hough_draw_line.o: wb_utils.hpp polar_line.hpp operator_utils.hpp
operator_hough_draw_line.o: operator_hough_draw_line.hpp operator.hpp
operator_hough_draw_line.o: data_source_descriptor.hpp histogram.hpp
operator_hough_draw_line.o: wb_filename.hpp
operator_hough_image_create.o: berkeley_db_data_source_descriptor.hpp
operator_hough_image_create.o: wb_image_depth.hpp data_source_descriptor.hpp
operator_hough_image_create.o: wb_defs.hpp histogram.hpp errors.hpp hough.hpp
operator_hough_image_create.o: hough_accum.hpp file_utils.hpp image.hpp
operator_hough_image_create.o: bounds.hpp image_header.hpp wb_data_format.hpp
operator_hough_image_create.o: wb_data_type.hpp wb_repository_type.hpp
operator_hough_image_create.o: line_segment.hpp point.hpp variance_stats.hpp
operator_hough_image_create.o: wb_utils.hpp polar_line.hpp wb_filename.hpp
operator_hough_image_create.o: operator_utils.hpp
operator_hough_image_create.o: operator_hough_image_create.hpp operator.hpp
operator_hough_peak_detect.o: operator_hough_peak_detect.hpp operator.hpp
operator_hough_peak_detect.o: wb_defs.hpp data_source_descriptor.hpp
operator_hough_peak_detect.o: histogram.hpp errors.hpp hough.hpp
operator_hough_peak_detect.o: hough_accum.hpp file_utils.hpp image.hpp
operator_hough_peak_detect.o: bounds.hpp image_header.hpp wb_data_format.hpp
operator_hough_peak_detect.o: wb_data_type.hpp wb_image_depth.hpp
operator_hough_peak_detect.o: wb_repository_type.hpp line_segment.hpp
operator_hough_peak_detect.o: point.hpp variance_stats.hpp wb_utils.hpp
operator_hough_peak_detect.o: polar_line.hpp wb_filename.hpp
operator_transform_image_copy.o: operator_transform_image_copy.hpp
operator_transform_image_copy.o: operator.hpp wb_defs.hpp
operator_transform_image_copy.o: data_source_descriptor.hpp histogram.hpp
operator_transform_image_copy.o: errors.hpp hough.hpp hough_accum.hpp
operator_transform_image_copy.o: file_utils.hpp image.hpp bounds.hpp
operator_transform_image_copy.o: image_header.hpp wb_data_format.hpp
operator_transform_image_copy.o: wb_data_type.hpp wb_image_depth.hpp
operator_transform_image_copy.o: wb_repository_type.hpp line_segment.hpp
operator_transform_image_copy.o: point.hpp variance_stats.hpp wb_utils.hpp
operator_transform_image_copy.o: polar_line.hpp wb_filename.hpp
operator_transform_image_morphology.o: operator_transform_image_morphology.hpp
operator_transform_image_morphology.o: operator.hpp wb_defs.hpp
operator_transform_image_morphology.o: data_source_descriptor.hpp
operator_transform_image_morphology.o: histogram.hpp errors.hpp hough.hpp
operator_transform_image_morphology.o: hough_accum.hpp file_utils.hpp
operator_transform_image_morphology.o: image.hpp bounds.hpp image_header.hpp
operator_transform_image_morphology.o: wb_data_format.hpp wb_data_type.hpp
operator_transform_image_morphology.o: wb_image_depth.hpp
operator_transform_image_morphology.o: wb_repository_type.hpp
operator_transform_image_morphology.o: line_segment.hpp point.hpp
operator_transform_image_morphology.o: variance_stats.hpp wb_utils.hpp
operator_transform_image_morphology.o: polar_line.hpp wb_filename.hpp
operator_transform_intensity_map.o: operator_transform_intensity_map.hpp
operator_transform_intensity_map.o: operator.hpp wb_defs.hpp
operator_transform_intensity_map.o: data_source_descriptor.hpp histogram.hpp
operator_transform_intensity_map.o: errors.hpp hough.hpp hough_accum.hpp
operator_transform_intensity_map.o: file_utils.hpp image.hpp bounds.hpp
operator_transform_intensity_map.o: image_header.hpp wb_data_format.hpp
operator_transform_intensity_map.o: wb_data_type.hpp wb_image_depth.hpp
operator_transform_intensity_map.o: wb_repository_type.hpp line_segment.hpp
operator_transform_intensity_map.o: point.hpp variance_stats.hpp wb_utils.hpp
operator_transform_intensity_map.o: polar_line.hpp wb_filename.hpp
operator_transform_intensity_map.o: operator_utils.hpp
operator_utils.o: errors.hpp wb_defs.hpp wb_utils.hpp wb_data_format.hpp
operator_utils.o: wb_data_type.hpp wb_image_depth.hpp wb_repository_type.hpp
operator_utils.o: operator_utils.hpp
point.o: point.hpp
polar_line.o: polar_line.hpp point.hpp
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
wb_log.o: errors.hpp wb_log.hpp
wb_repository_type.o: wb_repository_type.hpp
wb_utils.o: wb_repository_type.hpp errors.hpp wb_defs.hpp wb_utils.hpp
wb_utils.o: wb_data_format.hpp wb_data_type.hpp wb_image_depth.hpp
