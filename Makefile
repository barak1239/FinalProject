CXX = g++
CXXFLAGS = -std=c++14 -Wall -I.
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
TESTS = dice_test player_test property_test
MAIN = monopoly
COMMON_OBJS = board.o street_square.o color_group.o property.o player.o game.o utility_square.o railroad_square.o special_square.o surprise.o
GUI_OBJS = MonopolyGUI.o

.PHONY: all clean $(TESTS) run main

all: $(TESTS) $(MAIN)

$(MAIN): main.cpp $(COMMON_OBJS) $(GUI_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS)

run: $(MAIN)
	./$(MAIN)

main: $(MAIN)
	./$(MAIN)

dice_test: dice_test.cpp dice.hpp
	$(CXX) $(CXXFLAGS) -o $@ dice_test.cpp
	./$@

player_test: player_test.cpp $(COMMON_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	./$@

property_test: property_test.cpp $(COMMON_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	./$@

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

MonopolyGUI.o: MonopolyGUI.cpp MonopolyGUI.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TESTS) $(MAIN) *.o

# Run all tests
tests: $(TESTS)
	for test in $(TESTS); do ./$$test; done