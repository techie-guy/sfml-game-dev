CC = clang++
CFLAGS = -Wall -std=c++17 -g
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
SOURCE_FILES = src/*.cpp
INCLUDE_DIR = include
OUTPUT_DIR = bin
ASSETS_DIR = assets
TARGET_NAME = game

all: build run

build:
	@mkdir -p $(OUTPUT_DIR)
	@cp -r $(ASSETS_DIR) $(OUTPUT_DIR)
	@cd $(OUTPUT_DIR) ;\
	$(CC) $(CFLAGS) -c ../$(SOURCE_FILES) -I ../$(INCLUDE_DIR) ;\
	$(CC) *.o -o $(TARGET_NAME) $(LFLAGS) ;

run:
	./$(OUTPUT_DIR)/$(TARGET_NAME)

debug:
	@lldb ./$(OUTPUT_DIR)/$(TARGET_NAME).exe

clean:
	@rm -r $(OUTPUT_DIR)
