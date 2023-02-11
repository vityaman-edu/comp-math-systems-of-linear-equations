LDFLAGS   = 
CXXFLAGS  = -std=c++17 -Wall -I src
CXX       = g++

SRC_DIR   = src

BUILD_DIR = build
OBJ_DIR   = $(BUILD_DIR)/obj
BIN_DIR   = $(BUILD_DIR)/bin
SRCS     := $(wildcard $(SRC_DIR)/*.cpp)
OBJS     := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

TARGET    = app

run: $(BIN_DIR)/$(TARGET)
	./$(BIN_DIR)/$(TARGET)

clean:
	rm -rf $(BUILD_DIR)
	rm -rf ./**/*.o

$(BIN_DIR)/$(TARGET): $(BIN_DIR) $(OBJ_DIR) $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR): $(BUILD_DIR)
	mkdir -p $(OBJ_DIR)

$(BIN_DIR): $(BUILD_DIR)
	mkdir -p $(BIN_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

