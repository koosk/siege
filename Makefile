SRC = ./src
HEADER = $(SRC)/headers
BUILD = ./build
TEST = ./test

OPT = -Wall
GPP = g++ -I$(HEADER) $(OPT)

ALL: compile

build:
		mkdir -p $(BUILD);
		mkdir -p $(BUILD)/math

compile: build Vector3f.o Vector4f.o BadIndexException.o

Vector3f.o: $(SRC)/math/Vector3f.cpp $(HEADER)/math/Vector3f.h
	$(GPP) -o $(BUILD)/math/$@ -c $<

Vector4f.o: $(SRC)/math/Vector4f.cpp $(HEADER)/math/Vector4f.h
	$(GPP) -o $(BUILD)/math/$@ -c $<

BadIndexException.o: $(SRC)/BadIndexException.cpp $(HEADER)/BadIndexException.h
	$(GPP) -o $(BUILD)/$@ -c $<

test: compile testVector3f testVector4f

run-test: test
	$(BUILD)/testVector3f
	$(BUILD)/testVector4f

testVector3f: $(TEST)/Vector3f.cpp $(BUILD)/math/Vector3f.o $(BUILD)/BadIndexException.o
	$(GPP) -o $(BUILD)/$@ $+

testVector4f: $(TEST)/Vector4f.cpp $(BUILD)/math/Vector3f.o $(BUILD)/math/Vector4f.o $(BUILD)/BadIndexException.o
	$(GPP) -o $(BUILD)/$@ $+

.PHONY: clear
clear:
	-rm -rf $(BUILD)
