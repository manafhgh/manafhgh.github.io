CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic
.PHONY: all run clean
all: point-demo
point-demo: main.cpp point.cpp point.h
	$(CXX) $(CXXFLAGS) main.cpp point.cpp -o $@
run: point-demo
	./point-demo
clean:
	rm -f point-demo
