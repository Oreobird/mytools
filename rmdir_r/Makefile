CUR_DIR=$(shell pwd)
CC=gcc
CP=cp
RM=rm
CFLAGS=-Wall	
BIN_NAME=$(notdir $(CUR_DIR))
LIB_NAME=$(addsuffix .so, $(addprefix lib, $(BIN_NAME))) 
SO_NAME=$(BIN_NAME)
SRC_NAME=$(addsuffix .c, $(BIN_NAME))
BIN_DIR=~/bin
LIB_DIR=/usr/lib

all: bin lib

lib:
	@$(CC) $(CFLAGS) -fPIC -shared -Wl,-soname,$(LIB_NAME) -o $(LIB_NAME) $(SRC_NAME)

bin: lib
	@$(CC) $(CFLAGS) -o $(BIN_NAME) -l$(SO_NAME) -L$(CUR_DIR) main.c

install: all
	@$(CP) $(BIN_NAME) $(BIN_DIR) 
	@$(CP) $(LIB_NAME) $(LIB_DIR)
	
clean:
	@$(RM) -rf *.o $(BIN_NAME) *.so*
