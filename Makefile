# Makefile for general visualization

CXX = g++
#CXXFLAGS = -std=c++14 -g -Wall -march=native -fopenmp -fno-omit-frame-pointer -O2 -flto -Wno-sign-compare -fsanitize=address
CXXFLAGS = -std=c++14 -g -O2 -fPIC#-Wall -march=native -fopenmp -fno-omit-frame-pointer -flto -Wno-sign-compare

LIBFLAGS = `pkg-config --cflags --libs cairo libavformat libavcodec libswresample libswscale libavutil`

VPATH = src src/animators src/objects src/encoders src/systems

SRCS = $(wildcard ./*.cpp) \
	$(wildcard src/*.cpp) \
	$(wildcard src/animators/*.cpp) \
	$(wildcard src/objects/*.cpp) \
	$(wildcard src/encoders/*.cpp) \
	$(wildcard src/systems/*.cpp)

DEPS = $(wildcard include/*.h) \
	$(wildcard include/animators/*.h) \
	$(wildcard include/objects/*.h) \
	$(wildcard include/encoders/*.h) \
	$(wildcard include/systems/*.h)

OBJS = $(notdir $(SRCS:.cpp=.o))

LIB_OBJS = $(filter-out vis_test.o, $(OBJS))

vis_test: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBFLAGS)

lib: $(LIB_OBJS)
	$(CXX) -shared -Wl,-soname,libgathvl.so.1 -o libgathvl.so.1.0 $^

%.o:%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LIBFLAGS)

.PHONEY: clean

clean:
rm -Rf vis_test $(OBJS)
