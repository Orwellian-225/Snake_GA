appname := snake_ga

CXX := clang++
CXXFLAGS := -std=c++11 -Iinclude

srcfiles := $(shell find "src/*.cpp")
objects  := $(patsubst %.C, %.o, $(srcfiles))

all: $(appname)

$(appname): $(objects)
    $(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)

depend: .depend

.depend: $(srcfiles)
    rm -f ./.depend
    $(CXX) $(CXXFLAGS) -MM $^>>./.depend;

clean:
    rm -f $(objects)

dist-clean: clean
    rm -f *~ .depend

include .depend