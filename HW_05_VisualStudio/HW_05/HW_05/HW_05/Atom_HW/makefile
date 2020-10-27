.PHONY: dirs clean

all: dirs ut_main obj/shape.o

ut_main: src/shape.h src/shape.cpp src/rectangle.h test/ut_rectangle.h src/ellipse.h test/ut_ellipse.h src/triangle.h test/ut_triangle.h src/compound_shape.h test/ut_compound_shape.h test/ut_main.cpp
	g++ test/ut_main.cpp src/shape.cpp -o bin/ut_main -lgtest -lpthread
obj/shape.o: src/shape.cpp src/shape.h
	g++ -std=c++11 -Wfatal-errors -c src/shape.cpp -o obj/shape.o 

dirs:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -f bin/*
	rm -f obj/*
