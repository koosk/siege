SRC = ./src
HEADER = $(SRC)/headers
BUILD = ./build
TEST = ./test

OPT = -Wall
LIBS=-lGL -lGLU -lSDL -lSDL_image -lm
GPP = g++ -I$(HEADER) $(LIBS) $(OPT)


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
	
mtx16f = $(BUILD)/math/Matrix16f.o
$(mtx16f): $(SRC)/math/Matrix16f.cpp $(HEADER)/math/Matrix16f.h $(bie) $(v3f) $(v4f)
	$(GPP) -o $@ -c $<

bie = $(BUILD)/BadIndexException.o
$(bie): $(SRC)/BadIndexException.cpp $(HEADER)/BadIndexException.h
	$(GPP) -o $@ -c $<

sie = $(BUILD)/SiegeException.o
$(sie): $(SRC)/SiegeException.cpp $(HEADER)/SiegeException.h
	$(GPP) -o $@ -c $<

mse = $(BUILD)/gunit/MS3DException.o
$(mse): $(SRC)/gunit/MS3DException.cpp $(HEADER)/gunit/MS3DException.h
	$(GPP) -o $@ -c $<

msstruct = $(BUILD)/gunit/MS3DStruct.o
$(msstruct): $(SRC)/gunit/MS3DStruct.cpp $(HEADER)/gunit/MS3DStruct.h $(v3f) $(v4f) $(bie) $(mse) $(util)
	$(GPP) -o $@ -c $<

msdata = $(BUILD)/gunit/MS3DData.o
$(msdata): $(SRC)/gunit/MS3DData.cpp $(HEADER)/gunit/MS3DData.h $(msstruct)
	$(GPP) -o $@ -c $<

util = $(BUILD)/utils.o
$(util):$(SRC)/utils.cpp $(HEADER)/utils.h
	$(GPP) -o $@ -c $<

model = $(BUILD)/gunit/Model.o
$(model): $(SRC)/gunit/Model.cpp $(HEADER)/gunit/Model.h
	$(GPP) -o $@ -c $<

msmodel = $(BUILD)/gunit/MS3DModel.o
$(msmodel): $(SRC)/gunit/MS3DModel.cpp $(HEADER)/gunit/MS3DModel.h $(model)
	$(GPP) -o $@ -c $<

compile: build

tv3f = $(BUILD)/testVector3f
$(tv3f): $(TEST)/Vector3f.cpp $(v3f) $(bie) $(v4f)
	$(GPP) -o $@ $+

tv4f = $(BUILD)/testVector4f
$(tv4f): $(TEST)/Vector4f.cpp $(v3f) $(v4f) $(bie)
	$(GPP) -o $@ $+

tmsstruct = $(BUILD)/testMSStruct
$(tmsstruct): $(TEST)/MS3DStruct.cpp $(msstruct) $(v3f) $(v4f) $(bie) $(util) $(sie)
	$(GPP) -o $@ $+

tmsdata = $(BUILD)/testMSData
$(tmsdata): $(TEST)/MS3DData.cpp $(msdata) $(msstruct) $(v3f) $(v4f) $(bie) $(mse) $(util) $(sie)
	$(GPP) -o $@ $+

tmodel = $(BUILD)/testMSmodel
$(tmodel): $(TEST)/MSModel.cpp $(msdata) $(msstruct) $(v3f) $(v4f) $(bie) $(mse) $(util) $(sie) $(model) $(msmodel)
	$(GPP) -o $(tmodel) $+

tmatrix = $(BUILD)/testMatrix16f
$(tmatrix): $(TEST)/Matrix16f.cpp $(v3f) $(v4f) $(bie) $(mtx16f)
	$(GPP) -o $@ $+

run-model: compile $(tmodel)
	$(tmodel)

test: compile $(tv3f) $(tv4f) $(tmsstruct) $(tmsdata) $(tmodel) $(tmatrix)

run-test: test
	$(tv3f)
	$(tv4f)
	$(tmsstruct)
	$(tmsdata)

.PHONY: clear
clear:
	-rm -rf $(BUILD)
