CXX = clang++
CXXFLAGS = -std=c++17 -IJeuDeLaVie -Wall -Wextra -Werror
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRC_DIR = JeuDeLaVie
TEST_DIR = tests
SRCS = $(wildcard $(SRC_DIR)/*.cpp) main.cpp
OBJS = $(SRCS:.cpp=.o)
TEST_TARGET = tests/test_grille
TEST_SRCS = $(TEST_DIR)/test_grille.cpp $(SRC_DIR)/Grille.cpp
TARGET = main

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_TARGET): $(TEST_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_SRCS) $(LDFLAGS)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(OBJS) $(TARGET) $(TEST_TARGET) test_*.txt
