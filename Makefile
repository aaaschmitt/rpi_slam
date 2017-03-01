CXX=g++
RM=rm -f
INCLUDES=includes/
CPPFLAGS=-Wall -c -I $(INCLUDES)
LDLIBS=-I $(INCLUDES)

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
