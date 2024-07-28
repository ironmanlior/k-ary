CXX = g++
CXXFLAGS = -std=c++17 -fPIC
QTINCLUDE = $(shell pkg-config --cflags Qt5Widgets)
QTLIBS = $(shell pkg-config --libs Qt5Widgets)

all: test

test: test_tree.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(QTINCLUDE) $(QTLIBS)

test_tree.o: test_tree.cpp
	$(CXX) -c $< $(CXXFLAGS) $(QTINCLUDE)

clean:
	rm -f *.o test