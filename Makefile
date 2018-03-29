# Makefile for general visualization

CXX = g++
#CXXFLAGS = -std=c++11 -g -Wall -march=native -fopenmp -fno-omit-frame-pointer -O2 -flto -Wno-sign-compare -fsanitize=address
CXXFLAGS = -std=c++11 -g -O2 #-Wall -march=native -fopenmp -fno-omit-frame-pointer -flto -Wno-sign-compare

CAIROFLAGS = `pkg-config --cflags --libs cairo`
BINS = vis_test
OBJ = vis_test.o scene.o camera.o shapes.o
DEPS = include/vec.h include/scene.h include/camera.h include/shapes.h

$(BINS): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(BINS) $^ $(CAIROFLAGS)
	#./vis_test

%.o: src/%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(CAIROFLAGS)

clean:
	rm -Rf $(BINS) $(OBJ) file*


