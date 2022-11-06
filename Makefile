SRC_DIR = src
BUILD_DIR = build/debug
CC = gcc
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_NAME = play

COMPILER_FLAGS = -std=c11 -Wall -O0 -g -pedantic `pkg-config --cflags sdl2 SDL2_ttf`
LIBS=`pkg-config --libs sdl2 SDL2_ttf`

main:
	$(CC) $(COMPILER_FLAGS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME) $(LIBS)

client:
	$(CC) -std=c11 -Wall -O0 -g $(SRC_DIR)/socket/client.c -o $(BUILD_DIR)/client

server:
	$(CC) -std=c11 -Wall -O0 -g $(SRC_DIR)/socket/server.c -o $(BUILD_DIR)/server