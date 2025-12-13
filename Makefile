CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

BIN_DIR = bin
TARGET = $(BIN_DIR)/testBSTreeDict
SRC = testBSTreeDict.cpp

HEADERS = Dict.h BSTreeDict.h BSTree.h BSNode.h TableEntry.h

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -rf $(BIN_DIR)
	
