CXX ?= g++
PROGRAMS =  \
    ascii2char \
    at_test \
    cin \
    conv \
    cout \
    ConvolveImage \
    create_getopt_long_sample \
    DisplayImage \
    DisplayImage2 \
    getline \
    getopt \
    getopt_sample \
    iomanip \
    map \
    operator \
    plot \
    point_test \
    static \
    string_compare \
    trig
    # test_workbenchGetopt \
    # masks_golden \
    # masks1 \
    # masks \
    # maskconv2 \
    # maskconv1 \
    # maskconv \
    # create_getopt_long \
    # create_getopt_fct \
    # masks2 \
    # masks3 \
    # parse_filename 

CXXFLAGS += \
    -c -Wall -I/usr/local/include/opencv4

LDFLAGS += \
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

SRCFILES := $(wildcard *.cpp) 
LIBOBJS := 
OBJS := $(patsubst %.cpp,%.o,$(SRCFILES))

%.o: %.cpp %.hpp
	$(CXX) $< -o $@ $(CXXFLAGS)

all: $(PROGRAMS)

ascii2char: ascii2char.o $(LIBOBJS)
	$(CXX) ascii2char.o $(LIBOBJS) -o $@ $(LDFLAGS)

at_test: at_test.o $(LIBOBJS)
	$(CXX) at_test.o $(LIBOBJS) -o $@ $(LDFLAGS)

cin: cin.o 
	$(CXX) cin.o -o $@ 

conv: conv.o $(LIBOBJS)
	$(CXX) conv.o $(LIBOBJS) -o $@ $(LDFLAGS)

cout: cout.o $(LIBOBJS)
	$(CXX) cout.o $(LIBOBJS) -o $@ $(LDFLAGS)

ConvolveImage: ConvolveImage.o $(LIBOBJS)
	$(CXX) ConvolveImage.o $(LIBOBJS) -o $@ $(LDFLAGS)

create_getopt_fct: create_getopt_fct.o
	$(CXX) create_getopt_fct.o -o create_getopt_fct

create_getopt_long: create_getopt_long.o
	$(CXX) create_getopt_long.o -o create_getopt_long

create_getopt_long_sample: create_getopt_long_sample.o
	$(CXX) create_getopt_long_sample.o -o create_getopt_long_sample

DisplayImage: DisplayImage.o $(LIBOBJS)
	$(CXX) DisplayImage.o $(LIBOBJS) -o $@ $(LDFLAGS)

DisplayImage2: DisplayImage2.o $(LIBOBJS)
	$(CXX) DisplayImage2.o $(LIBOBJS) -o $@ $(LDFLAGS)

esp32_cam2jpg: esp32_cam2jpg.o $(LIBOBJS)
	$(CXX) esp32_cam2jpg.o $(LIBOBJS) -o $@ $(LDFLAGS)

getline: getline.o
	$(CXX) getline.o -o getline

getopt: getopt_sample.o
	$(CXX) getopt_sample.o -o getopt_sample

iomanip: iomanip.o 
	$(CXX) iomanip.o -o $@ 

map: map.o
	$(CXX) map.o -o map

masks: masks.o
	$(CXX) masks.o -o masks

masks1: masks1.o
	$(CXX) masks1.o -o masks1

masks2: masks2.o
	$(CXX) masks2.o -o masks2

masks3: masks3.o
	$(CXX) masks3.o -o masks3

masks_golden: masks_golden.o
	$(CXX) masks_golden.o -o masks_golden

maskconv: maskconv.o
	$(CXX) maskconv.o -o maskconv

maskconv1: maskconv1.o
	$(CXX) maskconv1.o -o maskconv1

maskconv2: maskconv2.o
	$(CXX) maskconv2.o -o maskconv2

operator: operator.o $(LIBOBJS)
	$(CXX) operator.o $(LIBOBJS) -o $@ $(LDFLAGS)

parse_filename: parse_filename.o $(LIBOBJS)
	$(CXX) parse_filename.o $(LIBOBJS) -o $@ $(LDFLAGS)

plot: plot.o
	$(CXX) plot.o -o plot

point_test: point_test.o point.o trigLookup.o
	$(CXX) point_test.o point.o trigLookup.o -o point_test

static: static.o
	$(CXX) static.o -o $@

string_compare: string_compare.o
	$(CXX) string_compare.o -o $@

test_workbenchGetopt: test_workbenchGetopt.o workbenchGetopt.o
	$(CXX) test_workbenchGetopt.o workbenchGetopt.o -o $@ 

trig: trig.o
	$(CXX) trig.o -o $@ 
	./trig pts.hpp

ptslookup: ptslookup.o trig
	$(CXX) -c ptslookup.cpp

ptslookup_test: ptslookup_test.o ptslookup
	$(CXX) ptslookup_test.o ptslookup.o -o $@ 

clean:
	rm -f $(OBJS) 

clobber: 
	rm -f $(OBJS) $(PROGRAMS)

depend:
	makedepend -- $(CXXFLAGS) -- $(SRCFILES)

# DO NOT DELETE
