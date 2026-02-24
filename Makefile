# Makefile for jyy_os projects

CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -O2
CXXFLAGS = -Wall -Wextra -O2

# Build directory
BUILD_DIR = build

# Source files
C_SRCS = hello.c main.c list_dir.c cjson_demo.c
CPP_SRCS = hello.cpp nlohmann_json_demo.cpp rapidjson_demo.cpp

# Target executables (in build directory)
BASE_TARGETS = $(BUILD_DIR)/hello $(BUILD_DIR)/hello_c $(BUILD_DIR)/main $(BUILD_DIR)/list_dir
JSON_TARGETS = $(BUILD_DIR)/nlohmann_json_demo $(BUILD_DIR)/rapidjson_demo $(BUILD_DIR)/cjson_demo

TARGETS = $(BASE_TARGETS) $(JSON_TARGETS)

# Default target: build base programs
all: $(BUILD_DIR) $(BASE_TARGETS)

# Build JSON demos (requires libraries)
json: $(BUILD_DIR) $(JSON_TARGETS)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build C++ programs
$(BUILD_DIR)/hello: hello.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $<

# nlohmann/json - header-only, requires: sudo apt install nlohmann-json3-dev
$(BUILD_DIR)/nlohmann_json_demo: nlohmann_json_demo.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $<

# RapidJSON - header-only, requires: sudo apt install rapidjson-dev
$(BUILD_DIR)/rapidjson_demo: rapidjson_demo.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $<

# Build C programs
$(BUILD_DIR)/hello_c: hello.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/main: main.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/list_dir: list_dir.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<

# cJSON - requires: sudo apt install libcjson-dev
$(BUILD_DIR)/cjson_demo: cjson_demo.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $< -lcjson

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

# JSON demo runners
run-nlohmann: $(BUILD_DIR)/nlohmann_json_demo
	$(BUILD_DIR)/nlohmann_json_demo

run-rapidjson: $(BUILD_DIR)/rapidjson_demo
	$(BUILD_DIR)/rapidjson_demo

run-cjson: $(BUILD_DIR)/cjson_demo
	$(BUILD_DIR)/cjson_demo

# Install dependencies (Ubuntu/Debian)
deps:
	@echo "Installing JSON library dependencies..."
	 sudo apt install -y nlohmann-json3-dev rapidjson-dev libcjson-dev

# Phony targets
.PHONY: all json clean rebuild run-hello-cpp run-hello-c run-main run-list-dir run-nlohmann run-rapidjson run-cjson deps
