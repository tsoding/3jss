CXXFLAGS=-Wall -Wextra -std=c++17 -pedantic -fno-exceptions `pkg-config --cflags sdl2`
LIBS=`pkg-config --libs sdl2`

3jss: main.cpp
	$(CXX) $(CXXFLAGS) -o 3jss main.cpp $(LIBS)
