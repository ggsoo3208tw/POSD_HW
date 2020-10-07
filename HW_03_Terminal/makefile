.PHONY: dirs clean

all: dirs ut_main geo

SRC = src/shape.h src/ellipse.h src/rectangle.h src/two_dimensional_coordinate.h src/triangle.h src/sort.h src/terminal.h
TEST = test/ut_rectangle.h test/ut_ellipse.h test/ut_triangle.h test/ut_sort.h test/ut_terminal.h

ut_main:  test/ut_main.cpp $(SRC) $(TEST)
	g++ test/ut_main.cpp -o bin/ut_main -lgtest -lpthread

geo: src/main.cpp $(SRC) $(TEST)
	g++ src/main.cpp -o bin/geo -lgtest -lpthread

dirs:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -f bin/*
