//this is the main class for the game! it initializes the GUI and Game objects
#include "game.hpp"
#include "MonopolyGUI.hpp"
#include <iostream>

int main() {
    try {
        std::cout << "Creating Game object..." << std::endl;
        Game game;
        
        std::cout << "Adding players..." << std::endl;
        game.addPlayer("Player 1");
        game.addPlayer("Player 2");
        // game.addPlayer("Player 3");
        // game.addPlayer("Player 4");
        // game.addPlayer("Player 5");
        // game.addPlayer("Player 6");
        // game.addPlayer("Player 7");
        // game.addPlayer("Player 8");

        std::cout << "Creating MonopolyGUI object..." << std::endl;
        MonopolyGUI gui(game);

        std::cout << "Running GUI..." << std::endl;
        gui.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}