SRC = ./src
BUILD = ./build
TEST = ./test

OPT = -Wall
GPP = g++ -I$(SRC) $(OPT)

: compile

build:
		mkdir -p $(BUILD);

compile: build


test: compile


.PHONY: clear
clear:
	-rm -rf $(BUILD)
