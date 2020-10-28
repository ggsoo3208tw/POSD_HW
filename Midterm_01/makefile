.PHONY: dirs clean

SRC = src/node.h src/app.h src/folder.h src/iterator.h src/node_iterator.h src/null_iterator.h src/utility.h

TEST = test/ut_app.h test/ut_folder.h test/ut_iterator.h test/ut_utility.h

OBJ = obj/node.o

SRC1 = src/node.h src/iterator.h src/node_iterator.h src/null_iterator.h

all: dirs ut_main obj/node.o

ut_main: test/ut_main.cpp $(TEST) $(SRC) $(OBJ)
	g++ -std=c++11 -Wfatal-errors -Wall test/ut_main.cpp obj/node.o -o bin/ut_main -lgtest -lpthread
obj/node.o: src/node.cpp src/node.h
	g++ -std=c++11 -Wfatal-errors -c src/node.cpp -o obj/node.o

dirs:
	mkdir -p bin
	mkdir -p obj

clean:
	rm -f bin/*
	rm -f obj/*

stat:
	wc -l src/* test/*.h test/*.cpp
