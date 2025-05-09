CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic
SRC_DIR = .
BUILD_DIR = build
TARGET = labo1

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Détection du système d'exploitation
ifeq ($(OS),Windows_NT)
    # Sous Windows
    RM = del /q
    MKDIR = mkdir
    EXEC = .\$(TARGET).exe
else
    # Sous Linux/Mac
    RM = rm -rf
    MKDIR = mkdir -p
    EXEC = ./$(TARGET)
endif

all: create-build-dir $(TARGET)

create-build-dir:
	@$(MKDIR) $(BUILD_DIR)
	
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(BUILD_DIR) $(TARGET)

run: all
	$(EXEC)

docker-build:
	docker build -t ift630-cpp-lab1 .

docker-run: docker-build 
		docker run \
		--rm --privileged \
		--network host \
		--pid host \
		ift630-cpp-lab1

.PHONY: all clean run create-build-dir docker-build docker-run