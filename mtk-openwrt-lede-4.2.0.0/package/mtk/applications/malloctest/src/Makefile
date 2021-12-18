# $Id: //WIFI_SOC/MP/SDK_5_0_0_0/RT288x_SDK/source/user/miniupnpd-1.6/Makefile#1 $
# MiniUPnP project
# (c) 2006-2011 Thomas Bernard
# http://miniupnp.free.fr/ or http://miniupnp.tuxfamily.org/
# Author : Thomas Bernard
# for use with GNU Make
#
# To install use :
# $ PREFIX=/dummyinstalldir make -f Makefile.linux install
# or :
# $ INSTALLPREFIX=/usr/local make -f Makefile.linux install
# or :
# $ make -f Makefile.linux install
#
# if your system hasn't iptables libiptc headers and binary correctly
# installed, you need to get iptables sources from http://netfilter.org/
# ./configure them and build them then miniupnpd will build using :
# $ IPTABLESPATH=/path/to/iptables-1.4.1 make -f Makefile.linux
#
#CFLAGS = -Wall -O -D_GNU_SOURCE -g -DDEBUG -ansi
#CFLAGS ?= -Wall -Os -D_GNU_SOURCE -fno-strict-aliasing -Wstrict-prototypes
#CC ?= gcc
#RM = rm -f
#INSTALL = install
#STRIP ?= strip
#CP = cp

BASEOBJS = multithread_malloc_testcode.o

LDFLAGS += $(LDFLAFGS) -lpthread

EXECUTABLES = multithread_malloc_testcode multithread_malloc_testcode_t1 multithread_malloc_testcode_t2 multithread_malloc_testcode_t0

.PHONY:	all clean install

all:	$(EXECUTABLES)
	$(STRIP) multithread_malloc_testcode multithread_malloc_testcode_t1 multithread_malloc_testcode_t2 multithread_malloc_testcode_t0

clean:
	$(RM) $(EXECUTABLES)
	find ./ -name "*.o" -exec rm {} \;


# genuuid is using the uuidgen CLI tool which is part of libuuid
# from the e2fsprogs

multithread_malloc_testcode:  multithread_malloc_testcode.o $(LIBS) 
multithread_malloc_testcode_t1: multithread_malloc_testcode_t1.o $(LIBS) 
multithread_malloc_testcode_t2: multithread_malloc_testcode_t2.o $(LIBS) 
multithread_malloc_testcode_t0: multithread_malloc_testcode_t0.o $(LIBS) 



