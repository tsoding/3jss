ifdef OS # windows nt (mingw of msys2)
CXXFLAGS=-Wall -Wextra -std=c++17 -pedantic -fno-exceptions $(shell pkg-config --cflags sdl2)
LIBS=$(shell pkg-config --libs sdl2)
else # linux
CXXFLAGS=-Wall -Wextra -std=c++17 -pedantic -fno-exceptions `pkg-config --cflags sdl2`
LIBS=`pkg-config --libs sdl2`
endif

3jss: src/3jss.cpp
	$(CXX) $(CXXFLAGS) -I./src/ -o 3jss src/3jss.cpp $(LIBS)
