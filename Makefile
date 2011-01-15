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

compile: build

v3f = $(BUILD)/math/Vector3f.o
$(v3f): $(SRC)/math/Vector3f.cpp $(HEADER)/math/Vector3f.h
	$(GPP) -o $@ -c $<

v4f = $(BUILD)/math/Vector4f.o
$(v4f): $(SRC)/math/Vector4f.cpp $(HEADER)/math/Vector4f.h
	$(GPP) -o $@ -c $<

bie = $(BUILD)/BadIndexException.o
$(bie): $(SRC)/BadIndexException.cpp $(HEADER)/BadIndexException.h
	$(GPP) -o $@ -c $<

test: compile testVector3f testVector4f

run-test: test
	$(BUILD)/testVector3f
	$(BUILD)/testVector4f

testVector3f: $(TEST)/Vector3f.cpp $(v3f) $(bie)
	$(GPP) -o $(BUILD)/$@ $+

testVector4f: $(TEST)/Vector4f.cpp $(v3f) $(v4f) $(bie)
	$(GPP) -o $(BUILD)/$@ $+

.PHONY: clear
clear:
	-rm -rf $(BUILD)
