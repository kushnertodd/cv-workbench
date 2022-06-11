#LDFLAGS=-L /usr/local/lib
#LDFLAGS=-Wl,-static
LDFLAGS=
all: djpeginfo
djpeginfo: djpeginfo.c
	cc  -g   djpeginfo.c $(LDFLAGS) -ljpeg  -o djpeginfo # rdcolmap.o wrbmp.o wrgif.o wrppm.o wrrle.o wrtarga.o
clean:
	rm -f djpeginfo.o djpeginfo
