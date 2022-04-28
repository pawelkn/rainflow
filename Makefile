CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -I src -c
LXXFLAGS = -pthread
GTEST = -lgtest -lgtest_main

TEST = build/test_rainflow
EXAMPLE = build/example_rainflow

$(EXAMPLE): ./build/rainflow.o ./build/example_rainflow.o
	$(CXX) $(LXXFLAGS) -o $(EXAMPLE) ./build/rainflow.o ./build/example_rainflow.o

$(TEST): ./build/rainflow.o ./build/test_rainflow.o
	$(CXX) $(LXXFLAGS) -o $(TEST) ./build/rainflow.o ./build/test_rainflow.o $(GTEST)

build/rainflow.o: ./src/rainflow.cpp ./src/rainflow.h | build
	$(CXX) $(CXXFLAGS) ./src/rainflow.cpp -o ./build/rainflow.o

build/example_rainflow.o: ./example/example_rainflow.cpp ./src/rainflow.h | build
	$(CXX) $(CXXFLAGS) ./example/example_rainflow.cpp -o ./build/example_rainflow.o

build/test_rainflow.o: ./test/test_rainflow.cpp ./src/rainflow.h | build
	$(CXX) $(CXXFLAGS) ./test/test_rainflow.cpp -o ./build/test_rainflow.o

build:
	mkdir $@

.PHONY: example test clean

test: $(TEST)
	$(TEST)

clean:
	rm -rfv build