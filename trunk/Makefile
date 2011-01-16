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
		mkdir -p $(BUILD)/gunit

v3f = $(BUILD)/math/Vector3f.o
$(v3f): $(SRC)/math/Vector3f.cpp $(HEADER)/math/Vector3f.h
	$(GPP) -o $@ -c $<

v4f = $(BUILD)/math/Vector4f.o
$(v4f): $(SRC)/math/Vector4f.cpp $(HEADER)/math/Vector4f.h
	$(GPP) -o $@ -c $<

bie = $(BUILD)/BadIndexException.o
$(bie): $(SRC)/BadIndexException.cpp $(HEADER)/BadIndexException.h
	$(GPP) -o $@ -c $<

mse = $(BUILD)/gunit/MS3DException.o
$(mse): $(SRC)/gunit/MS3DException.cpp $(HEADER)/gunit/MS3DException.h
	$(GPP) -o $@ -c $<

msstruct = $(BUILD)/gunit/MS3DStruct.o
$(msstruct): $(SRC)/gunit/MS3DStruct.cpp $(HEADER)/gunit/MS3DStruct.h $(v3f) $(v4f) $(bie) $(mse)
	$(GPP) -o $@ -c $<

compile: build

tv3f = $(BUILD)/testVector3f
$(tv3f): $(TEST)/Vector3f.cpp $(v3f) $(bie)
	$(GPP) -o $@ $+

tv4f = $(BUILD)/testVector4f
$(tv4f): $(TEST)/Vector4f.cpp $(v3f) $(v4f) $(bie)
	$(GPP) -o $@ $+

tmsstruct = $(BUILD)/testMSStruct
$(tmsstruct): $(TEST)/MS3DStruct.cpp $(msstruct) $(v3f) $(v4f) $(bie) $(mse)
	$(GPP) -o $@ $+

test: compile $(tv3f) $(tv4f) $(tmsstruct)

run-test: test
	$(tv3f)
	$(tv4f)
	$(tmsstruct)

.PHONY: clear
clear:
	-rm -rf $(BUILD)
