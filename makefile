CC=gcc
CPP=g++
TARGET_NAME=cod4x_sqlite_plugin

ifeq ($(OS),Windows_NT)
EXT=dll
CFLAGS=-m32 -Wall -O1 -g -mtune=core2
LFLAGS=-m32 -g -shared -static-libgcc -static-libstdc++ 
LIBS=-L.. -lcom_plugin
else
EXT=so
CFLAGS=-m32 -Wall -O1 -g -fvisibility=hidden -mtune=core2
LFLAGS=-m32 -g -shared
LIBS=
endif

SQLITE_DIR=sqlite
OBJ_DIR=obj
BIN_DIR=bin

SQLITE_SRC=$(wildcard $(SQLITE_DIR)/*.c)
CPP_SRC=$(wildcard *.cpp)

OBJ_FILES=$(addprefix $(OBJ_DIR)/,$(notdir $(SQLITE_SRC:.c=.o)) $(notdir $(CPP_SRC:.cpp=.o)))

all: $(BIN_DIR)/$(TARGET_NAME).$(EXT)

$(BIN_DIR)/$(TARGET_NAME).$(EXT): $(OBJ_FILES)
	$(CPP) $(LFLAGS) -o $@ $^ $(LIBS)

$(OBJ_DIR)/%.o: $(SQLITE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: %.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/$(TARGET_NAME).$(EXT)