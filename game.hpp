#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <memory>
#include "board.hpp"
#include "player.hpp"
#include "dice.hpp"
#include "constants.hpp"
#include "surprise.hpp"
#include "street_square.hpp"

class Game {
private:
    Board board;
    Dice dice;
    int currentPlayerIndex;
    int availableGetOutOfJailCards;
    int bankMoney;
    SurpriseDeck chanceDeck;
    SurpriseDeck communityChestDeck;

public:
    Game();
    std::vector<std::unique_ptr<Player>> players;

    void returnGetOutOfJailCard();
    void receivePayment(int amount);
    void addPlayer(const std::string& name);
    void startGame();
    void playTurn();
    Player* getCurrentPlayer() const;
    const Board& getBoard() const { return board; }
    void movePlayer(Player& player, int spaces);
    void handleLanding(Player& player, Square* square);
    bool isGameOver() const;
    void buildHouse(Player& player, StreetSquare& property);
    void buildHotel(Player& player, StreetSquare& property);
    void movePlayerTo(Player& player, int position);
    void sendPlayerToJail(Player& player);
    void nextPlayer();
    void buyPropertyForCurrentPlayer();
    void buildHouseForCurrentPlayer();
    void buildHotelForCurrentPlayer();
    std::vector<Property*> getProperties() const;
    void initializeDecks();
};

#endif // GAME_HPP