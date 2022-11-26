CXX := clang++
CXXFLAGS := -Wall -std=c++20 -g
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system
SOURCE_DIR := src
INCLUDE_DIR := include
OUTPUT_DIR := bin
ASSETS_DIR := assets
TARGET_NAME := game

all: build run

build: $(SOURCE_DIR)/*.cpp
	@mkdir -p $(OUTPUT_DIR)
	@cp -r $(ASSETS_DIR) $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c $(wildcard $(SOURCE_DIR)/*.cpp) -I $(INCLUDE_DIR)
	$(CXX) *.o -o $(OUTPUT_DIR)/$(TARGET_NAME) $(LDFLAGS)

run:
	./$(OUTPUT_DIR)/$(TARGET_NAME)

clean:
	@rm -r $(OUTPUT_DIR)
