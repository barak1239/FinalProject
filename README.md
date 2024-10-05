# Monopoly Game in C++

## Project Overview

This project is a C++ implementation of the classic Monopoly board game. It includes both the core game logic and a graphical interface for player interaction. Players can roll dice, move around the board, buy properties, and manage their finances just like in the real game.

## Project Structure

- **Makefile**: Instructions for compiling the project.
- **Source Code**:
  - `MonopolyGUI.cpp/hpp`: Handles the graphical user interface (GUI) of the game.
  - `board.cpp/hpp`: Contains the implementation of the game board, including the setup of squares (properties, railroads, utilities, special squares).
  - `color_group.cpp/hpp`: Manages groups of properties with the same color (used for determining rents, houses, and hotels).
  - `game.cpp/hpp`: Manages the overall game flow, player turns, and interaction with other game components.
  - `player.cpp/hpp`: Implements player-related features such as movement, property ownership, and financial management.
  - `property.cpp/hpp`: Handles properties that players can purchase, mortgage, and improve with houses/hotels.
  - `railroad_square.cpp/hpp`: Implements railroad-specific logic (special property type in Monopoly).
  - `special_square.cpp/hpp`: Represents squares that have special actions (e.g., Go To Jail, Chance).
  - `street_square.cpp/hpp`: Manages standard street properties (buying, rent, improvements).
  - `surprise.cpp/hpp`: Manages surprise cards (Chance/Community Chest).
  - `utility_square.cpp/hpp`: Handles utility-specific properties (Electric Company, Water Works).
  - `dice.hpp`: Manages dice rolling and random number generation for the game.

- **Test Files**:
  - `dice_test.cpp`: Unit tests for the dice functionality.
  - `player_test.cpp`: Unit tests for the player behavior.
  - `property_test.cpp`: Unit tests for property-related logic.

- **Assets**:
  - `monopoly_board.png`: Image of the Monopoly board.
  - `player1.png` to `player8.png`: Images representing player tokens.
  - `kabel.ttf`: Font used in the GUI.

## Compilation

To compile the project, simply run the following command in the root directory:

```bash
make
