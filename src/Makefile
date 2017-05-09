CC = g++
EXE_NAME = angry-donuts
SOURCE_FILES = $(filter-out nodejs.cpp, $(wildcard *.cpp))
OBJ_FILES = $(SOURCE_FILES:.cpp=.o)
CCFLAGS = -std=c++11 -Wall -pedantic
LDFLAGS = -luuid

all : $(EXE_NAME)

clean : 
	rm -f $(EXE_NAME) $(OBJ_FILES)

$(EXE_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXE_NAME) $(OBJ_FILES) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CCFLAGS) -o $@ -c $<

.PHONY : clean
