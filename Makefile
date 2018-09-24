ANN_INCLUDE = C:/devlibs/ann_1.1.2/include
ANN_LIBRARY	= C:/devlibs/ann_1.1.2/lib/libANN.a
CXX =  g++

LIBRARIES = -I$(ANN_INCLUDE)

SOURCES_PATH = src/
OBJECTS_PATH = obj/
BINARY_PATH = bin/
DEBUG_PATH = debug/
TEST_PATH = test/

SUFFIXES ?= .o .cpp .exe .h
 .SUFFIXES: $(SUFFIXES) .

build: dtm $(SOURCES_PATH)distance_to_a_measure.cpp $(SOURCES_PATH)denoise.cpp
	 $(CXX) -O -o $(BINARY_PATH)dtm.exe $(SOURCES_PATH)distance_to_a_measure.cpp $(OBJECTS_PATH)dtm.o -I$(ANN_INCLUDE) $(ANN_LIBRARY)
	 $(CXX) -O -o $(BINARY_PATH)denoise.exe $(SOURCES_PATH)denoise.cpp $(OBJECTS_PATH)dtm.o -I$(ANN_INCLUDE) $(ANN_LIBRARY)

debug: $(SOURCES_PATH)distance_to_a_measure.cpp $(SOURCES_PATH)denoise.cpp $(SOURCES_PATH)dtm.cpp $(SOURCES_PATH)dtm.h
	 $(CXX) -g -c $(SOURCES_PATH)dtm.cpp -o $(OBJECTS_PATH)dtm.o -I$(ANN_INCLUDE) --std=c++0x
	 $(CXX) -g -o $(DEBUG_PATH)dtm.exe $(SOURCES_PATH)distance_to_a_measure.cpp $(OBJECTS_PATH)dtm.o -I$(ANN_INCLUDE) $(ANN_LIBRARY)
	 $(CXX) -g -o $(DEBUG_PATH)denoise.exe $(SOURCES_PATH)denoise.cpp $(OBJECTS_PATH)dtm.o -I$(ANN_INCLUDE) $(ANN_LIBRARY)

dtm: $(SOURCES_PATH)dtm.cpp $(SOURCES_PATH)dtm.h
	 $(CXX) -c $(SOURCES_PATH)dtm.cpp -o $(OBJECTS_PATH)dtm.o -I$(ANN_INCLUDE) --std=c++0x

test: $(SOURCES_PATH)dtm.cpp $(SOURCES_PATH)dtm.h $(TEST_PATH)test_dtm.cpp
	 $(CXX) -g -c $(SOURCES_PATH)dtm.cpp -o $(OBJECTS_PATH)dtm.o -I$(ANN_INCLUDE) --std=c++0x
	 $(CXX) -g -o $(TEST_PATH)test_dtm.exe $(TEST_PATH)test_dtm.cpp $(OBJECTS_PATH)dtm.o -I$(ANN_INCLUDE) $(ANN_LIBRARY)
	test/test_dtm.exe

doc: $(SOURCES_PATH)dtm.h
	doxygen Doxyfile

clean:
	rm $(OBJECTS_PATH)*
	rm $(BINARY_PATH)*
	rm $(TEST_PATH)*.exe
	rm $(DEBUG_PATH)*.exe

clean-doc:
	rm -r doc/*
