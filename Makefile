CXX = gcc
CXX_FLAGS -Wall
DEPS = analyze.h lexical.h

%.o %.cpp $(DEPS)
***$(CXX) -c -o $@ $c $(CXX_FLAGS)
subc: (OBJ)
***gcc -o $@ $^ $(CXX_FLAGS)