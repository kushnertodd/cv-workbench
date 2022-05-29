LOCALDIR=/usr/local/BerkeleyDB.$(LIBVERSION)
INCSDIR=$(LOCALDIR)/include
LIBSDIR=$(LOCALDIR)/lib
LIBVERSION=18.1
OBJS=example_database_read.o example_database_load.o gettingstarted_common.o
PROGRAMS=example_database_read example_database_load
SRCS=example_database_read.c example_database_load.c gettingstarted_common.c
all: example_database_load example_database_read
example_database_load: $(SRCS) 
	cc -c -I$(INCSDIR) -D_GNU_SOURCE -D_REENTRANT -O3 example_database_load.c  -fPIC -DPIC -o example_database_load.o
	cc -c -I$(INCSDIR) -D_GNU_SOURCE -D_REENTRANT -O3 gettingstarted_common.c  -fPIC -DPIC -o gettingstarted_common.o
	cc -O3 -o example_database_load example_database_load.o gettingstarted_common.o $(LIBSDIR)/libdb-$(LIBVERSION).so -lpthread  -Wl,-rpath -Wl,$(LOCALDIR)/lib
example_database_read: $(SRCS)
	cc -c -I$(INCSDIR) -D_GNU_SOURCE -D_REENTRANT -O3 example_database_read.c  -fPIC -DPIC -o example_database_read.o
	cc -c -I$(INCSDIR) -D_GNU_SOURCE -D_REENTRANT -O3 gettingstarted_common.c  -fPIC -DPIC -o gettingstarted_common.o
	cc -O3 -o example_database_read example_database_read.o gettingstarted_common.o $(LIBSDIR)/libdb-$(LIBVERSION).so -lpthread  -Wl,-rpath -Wl,$(LOCALDIR)/lib
run:
	./example_database_load
	./example_database_read
clean:
	rm -f $(OBJS) $(PROGRAMS) *.db
