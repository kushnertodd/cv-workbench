CXX=g++
CCFLAGS=-g -Wall -I/usr/local/include
CXXFLAGS=-g ${CCFLAGS}
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
  hough_accum.o \
  hough.o \
  image.o \
  image_depth.o \
  image_frame.o \
  image_header.o \
  image_line_segment.o \
  internet_data_source_descriptor.o \
  kernel.o \
  line_segment.o \
  morphology.o \
  one_pass_mean.o \
  operator.o \
  operator_dispatcher.o \
  operator_filter_edge_color.o \
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
  operator_transform_image_combine.o \
  operator_transform_image_copy.o \
  operator_transform_image_create.o \
  operator_transform_image_resize.o \
  operator_transform_intensity_map.o \
  operator_utils.o \
  pearsons_correlation.o \
  pixel.o \
  point.o \
  polar_line.o \
  polar_trig.o \
  runtime.o \
  variance_stats.o \
  wb_data_format.o \
  wb_data_type.o \
  wb_filename.o \
  wb_json_utils.o \
  wb_log.o \
  wb_morphology_types.o \
  wb_repository_type.o \
  wb_resize_types.o \
  wb_utils.o \
  wb_window.o

PROGRAMS = \
  image-copy \
  image-corr \
  image-dump \
  image-info \
  image-map \
  image-mean \
  image-morph \
  image-read \
  image-trig \
  cv-workbench

%.o: %.cpp %.hpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

all: $(PROGRAMS)

image-copy: image-copy.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

image-corr: image-corr.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

image-dump: image-dump.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

image-info: image-info.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

image-map: image-map.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

image-mean: image-mean.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

image-morph: image-morph.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

image-read: image-read.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

cv-workbench : cv-workbench.o $(SRCOBJS)
	$(CXX) $< -o $@ $(SRCOBJS) $(CXXFLAGS) $(LDFLAGS_JSON) $(LDFLAGS_JPEG)

gen_polar_trig_static: gen_polar_trig_static.o
	$(CXX) $< -o $@ 

polar_trig_static.hpp: gen_polar_trig_static
	./gen_polar_trig_static >polar_trig_static.hpp

objs:
	@echo $(OBJS)

clean:
	rm -f $(OBJS)

clobber: 
	rm -f $(OBJS) $(PROGRAMS)

install:
	cp $(PROGRAMS) ../bin

doc:
	doxygen doxygen.config

# DO NOT DELETE

