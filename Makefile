CXX=g++
RM=rm -f
CPPFLAGS=-Wall -c -I includes
LDLIBS=-lwiringPi

SRCS=src/*.cpp
OBJS=$(subst .cc,.o,$(SRCS))

all: rpi_slam

rpi_slam: $(OBJS)

rpi_slam: $(OBJS)
    $(CXX) $(LDFLAGS) -o rpi_slam $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
    rm -f ./.depend
    $(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
    $(RM) $(OBJS)

dist-clean: clean
    $(RM) *~ .depend

include .depend