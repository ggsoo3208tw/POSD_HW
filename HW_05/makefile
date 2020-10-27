.PHONY: dirs clean

SRC = src/shape.h src/rectangle.h src/ellipse.h src/triangle.h src/two_dimensional_coordinate.h src/compound_shape.h src/iterator.h src/shape_iterator.h src/null_iterator.h src/utility.h

TEST = test/ut_rectangle.h test/ut_ellipse.h test/ut_triangle.h test/ut_compound_shape.h test/ut_iterator.h test/ut_utility.h

OBJ = obj/shape.o

all: dirs ut_main obj/shape.o

ut_main: test/ut_main.cpp $(TEST) $(SRC) $(OBJ)
	g++ -std=c++11 -Wfatal-errors -Wall test/ut_main.cpp obj/shape.o -o bin/ut_main -lgtest -lpthread
obj/shape.o: src/shape.cpp src/shape.h
	g++ -std=c++11 -Wfatal-errors -c src/shape.cpp -o obj/shape.o

dirs:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -f bin/*
	rm -f obj/*

stat:
	wc -l src/* test/*.h test/*.cpp
