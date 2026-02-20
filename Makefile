# Makefile for hello.c and hello.cpp

CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -O2
CXXFLAGS = -Wall -Wextra -O2

# Targets
TARGETS = hello hello_c

# Default target: build both programs
all: $(TARGETS)

# Build C++ program
hello: hello.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Build C program
hello_c: hello.c
	$(CC) $(CFLAGS) -o $@ $<

# Clean build artifacts
clean:
	rm -f $(TARGETS) *.o

# Rebuild everything
rebuild: clean all

# Run C++ program
run-cpp: hello
	./hello

# Run C program
run-c: hello_c
	./hello_c

# Phony targets
.PHONY: all clean rebuild run-cpp run-c
