CC = g++
EXE_NAME = angry-donuts
SOURCE_FILES = $(wildcard *.cpp)
OBJ_FILES = $(SOURCE_FILES:.cpp=.o)
CCFLAGS =
LDFLAGS =

all : $(EXE_NAME)

clean : 
	rm -f $(EXE_NAME) $(OBJ_FILES)

$(EXE_NAME) : $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $(EXE_NAME) $(OBJ_FILES)

%.o: %.cpp
	$(CC) $(CCFLAGS) -o $@ -c $<

.PHONY : clean
