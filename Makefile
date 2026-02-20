# Makefile for jyy_os projects

CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -O2
CXXFLAGS = -Wall -Wextra -O2

# Build directory
BUILD_DIR = build

# Source files
C_SRCS = hello.c main.c list_dir.c
CPP_SRCS = hello.cpp

# Target executables (in build directory)
TARGETS = $(BUILD_DIR)/hello $(BUILD_DIR)/hello_c $(BUILD_DIR)/main $(BUILD_DIR)/list_dir

# Default target: build all programs
all: $(BUILD_DIR) $(TARGETS)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build C++ program
$(BUILD_DIR)/hello: hello.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $<

# Build C programs
$(BUILD_DIR)/hello_c: hello.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/main: main.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/list_dir: list_dir.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) *.o

# Rebuild everything
rebuild: clean all

# Run targets
run-hello-cpp: $(BUILD_DIR)/hello
	$(BUILD_DIR)/hello

run-hello-c: $(BUILD_DIR)/hello_c
	$(BUILD_DIR)/hello_c

run-main: $(BUILD_DIR)/main
	$(BUILD_DIR)/main

run-list-dir: $(BUILD_DIR)/list_dir
	$(BUILD_DIR)/list_dir

# Phony targets
.PHONY: all clean rebuild run-hello-cpp run-hello-c run-main run-list-dir
