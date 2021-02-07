CXXFLAGS=-Wall -Wextra -std=c++17 -pedantic -fno-exceptions `pkg-config --cflags sdl2`
LIBS=`pkg-config --libs sdl2`

3jss: src/3jss.cpp
	$(CXX) $(CXXFLAGS) -I./src/ -o 3jss src/3jss.cpp $(LIBS)
