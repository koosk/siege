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

v3f = $(BUILD)/math/Vector3.o
$(v3f): $(SRC)/math/Vector3.cpp $(HEADER)/math/Vector3.h
	$(GPP) -o $@ -c $<

v4f = $(BUILD)/math/Vector4.o
$(v4f): $(SRC)/math/Vector4.cpp $(HEADER)/math/Vector4.h
	$(GPP) -o $@ -c $<
	
mtx16f = $(BUILD)/math/Matrix4.o
$(mtx16f): $(SRC)/math/Matrix4.cpp $(HEADER)/math/Matrix4.h $(bie) $(v3f) $(v4f) $(mathex)
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

mathex = $(BUILD)/math/MathException.o
$(mathex): $(SRC)/math/MathException.cpp $(HEADER)/math/MathException.h
	$(GPP) -o $@ -c $<

bsp = $(BUILD)/gunit/BSPStruct.o
$(bsp): $(SRC)/gunit/BSPStruct.cpp $(HEADER)/gunit/BSPStruct.h $(v3f) $(sie) $(bie) $(utils)
	$(GPP) -o $@ -c $<

compile: build 

tv3f = $(BUILD)/testVector3
$(tv3f): $(TEST)/Vector3.cpp $(v3f) $(bie) $(v4f)
	$(GPP) -o $@ $+

tv4f = $(BUILD)/testVector4
$(tv4f): $(TEST)/Vector4.cpp $(v3f) $(v4f) $(bie)
	$(GPP) -o $@ $+

tmsstruct = $(BUILD)/testMSStruct
$(tmsstruct): $(TEST)/MS3DStruct.cpp $(msstruct) $(v3f) $(v4f) $(bie) $(util) $(sie) $(mse)
	$(GPP) -o $@ $+

tmsdata = $(BUILD)/testMSData
$(tmsdata): $(TEST)/MS3DData.cpp $(msdata) $(msstruct) $(v3f) $(v4f) $(bie) $(mse) $(util) $(sie)
	$(GPP) -o $@ $+

tmodel = $(BUILD)/testMSmodel
$(tmodel): $(TEST)/MSModel.cpp $(msdata) $(msstruct) $(v3f) $(v4f) $(bie) $(mse) $(util) $(sie) $(model) $(msmodel) $(mtx16f) $(mathex) 
	$(GPP) -o $(tmodel) $+

tmat = $(BUILD)/Rottest.o
mattest: $(TEST)/Rottest.cpp $(msdata) $(msstruct) $(v3f) $(v4f) $(bie) $(mse) $(util) $(sie) $(mtx16f) $(mathex)
	$(GPP) -o $(tmat) $+
	$(tmat)
	
prbfile = $(BUILD)/prb
prb: $(TEST)/prb.cpp $(msdata) $(msstruct) $(v3f) $(v4f) $(bie) $(mse) $(util) $(sie) $(mtx16f) $(mathex)
	$(GPP) -o $(prbfile) $+
	$(prbfile)


tmatrix = $(BUILD)/testMatrix4
$(tmatrix): $(TEST)/Matrix4.cpp $(v3f) $(v4f) $(bie) $(mtx16f) $(mathex)
	$(GPP) -o $@ $+

tbsp = $(BUILD)/testBSPStruct
$(tbsp): $(TEST)/BSPStruct.cpp $(v3f) $(v4f)  $(bie) $(bsp) $(util) $(sie)
	$(GPP) -o $@ $+

run-model: compile $(tmodel)
	$(tmodel)

test: compile $(tv3f) $(tv4f) $(tmsstruct) $(tmsdata) $(tmodel) $(tmatrix) $(tbsp)

run-test: test
	$(tv3f)
	$(tv4f)
	$(tmsstruct)
	$(tmsdata)
	$(tmatrix)
	$(tbsp)

.PHONY: clear
clear:
	-rm -rf $(BUILD)
