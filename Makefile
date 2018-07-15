# Makefile for general visualization

CXX = g++
#CXXFLAGS = -std=c++14 -g -Wall -march=native -fopenmp -fno-omit-frame-pointer -O2 -flto -Wno-sign-compare -fsanitize=address
CXXFLAGS = -std=c++14 -g -O2 #-Wall -march=native -fopenmp -fno-omit-frame-pointer -flto -Wno-sign-compare

LIBFLAGS = `pkg-config --cflags --libs cairo libavformat libavcodec libswresample libswscale libavutil`

VPATH = src src/animators src/objects src/encoders

SRCS = $(wildcard ./*.cpp) \
	$(wildcard src/*.cpp) \
	$(wildcard src/animators/*.cpp) \
	$(wildcard src/objects/*.cpp) \
	$(wildcard src/encoders/*.cpp)

DEPS = $(wildcard include/*.h) \
	$(wildcard include/animators/*.h) \
	$(wildcard include/objects/*.h) \
	$(wildcard include/encoders/*.h)

OBJS = $(notdir $(SRCS:.cpp=.o))

vis_test: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBFLAGS)

%.o:%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LIBFLAGS)

.PHONEY: clean

clean:
	rm -Rf vis_test $(OBJS)
