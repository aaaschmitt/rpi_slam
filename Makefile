OS := $(shell uname)
ifeq ($(OS), Darwin)
	COMPILER=/Volumes/xtools/armv8-rpi3-linux-gnueabihf/bin/armv8-rpi3-linux-gnueabihf-g++
	INCLUDES=includes/
else
	COMPILER=g++-6
	INCLUDES=includes/ -lwiringPi
endif

CXX=$(COMPILER) -std=c++14
RM=rm -f
CPPFLAGS=-Wall -c -I $(INCLUDES)
LDLIBS=-I $(INCLUDES) -I lib/wiringPi/wiringPi

SRCS=src/*.cpp
OBJS=$(subst .cc,.o,$(SRCS))

all: rpi_slam

rpi_slam: $(OBJS)

rpi_slam: $(OBJS)
	$(CXX) $(LDFLAGS) -o rpi_slam $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .depend

include .depend
