//this is the main class called game, it handles almost everything, including decks, boards, players, etc. it has many loggic functions
#include "game.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include "street_square.hpp"
#include "surprise.hpp"
#include "color_group.hpp"

Game::Game() : currentPlayerIndex(0), availableGetOutOfJailCards(0), bankMoney(0) {
    initializeDecks();
}

void Game::addPlayer(const std::string& name) {
    if (players.size() >= Constants::MAX_PLAYERS) {
        throw std::runtime_error("Maximum number of players reached");
    }
    players.push_back(std::make_unique<Player>(name));
}

void Game::startGame() {
    if (players.size() < Constants::MIN_PLAYERS) {
        throw std::runtime_error("Not enough players to start the game");
    }
    initializeDecks();
}

void Game::playTurn() {
    Player* currentPlayer = getCurrentPlayer();
    if (!currentPlayer || currentPlayer->getHasRolledDice()) return;


    if (currentPlayer->isInJail()) {
        if (currentPlayer->hasGetOutOfJailCard()) {
            currentPlayer->useGetOutOfJailCard(*this);
        } else if (currentPlayer->canPayBail()) {
            currentPlayer->payBail(*this);
        } else {
            dice.roll();
            if (dice.isDouble()) {
                currentPlayer->getOutOfJail();
                currentPlayer->setHasRolledDice(true);
                return;
            } else {
                currentPlayer->setHasRolledDice(true);
                return;
            }
        }
    }


    dice.roll();
    int spaces = dice.getTotal();

    movePlayer(*currentPlayer, spaces);
    
    currentPlayer->setHasRolledDice(true);
}

bool Game::isGameOver() const {
    int activePlayers = 0;
    Player* wealthyPlayer = nullptr;
    
    for (const auto& player : players) {
        if (player->getMoney() > 0) {
            activePlayers++;
            if (player->getMoney() >= 4000) {
                wealthyPlayer = player.get();
            }
        }
    }
    
    return activePlayers <= 1 || wealthyPlayer != nullptr;
}

Player* Game::getCurrentPlayer() const {
    if (players.empty()) return nullptr;
    return players[currentPlayerIndex].get();
}

void Game::movePlayer(Player& player, int spaces) {
    int newPosition = (player.getPosition() + spaces) % board.getSize();
    if (newPosition < player.getPosition()) {
        player.receiveMoney(Constants::PASS_GO_MONEY);
    }
    player.moveToPosition(newPosition);

    Square* landedSquare = board.getSquare(player.getPosition());
    Game::handleLanding(player, landedSquare);
}

void Game::handleLanding(Player& player, Square* square) {
    if (square) {
        if (square->getName() == "Chance") {
            SurpriseCard card = chanceDeck.drawCard();
            player.addCard("Chance: " + card.getDescription());
            card.execute(player, *this);
        } else if (square->getName() == "Community Chest") {
            SurpriseCard card = communityChestDeck.drawCard();
            player.addCard("Community Chest: " + card.getDescription());
            card.execute(player, *this);
        }
        square->landOn(player);
    }
}

void Game::returnGetOutOfJailCard() {
    availableGetOutOfJailCards++;
}

void Game::receivePayment(int amount) {
    bankMoney += amount;
}

void Game::buildHouse(Player& player, StreetSquare& property) {
    if (property.canBuildHouse() && player.canAfford(property.getHousePrice())) {
        if (property.getColorGroup()->hasEvenDevelopment(property)) {
            player.payMoney(property.getHousePrice());
            property.addHouse();
        } else {
        }
    }
}

void Game::buildHotel(Player& player, StreetSquare& property) {
    if (property.canBuildHotel() && player.canAfford(property.getHotelPrice())) {
        if (property.getColorGroup()->hasEvenDevelopment(property)) {
            player.payMoney(property.getHotelPrice());
            property.addHotel();
            std::cout << player.getName() << " built a hotel on " << property.getName() << std::endl;
        } else {
            std::cout << "You must build evenly across the color group." << std::endl;
        }
    } else {
        std::cout << "Cannot build a hotel on this property." << std::endl;
    }
}

void Game::movePlayerTo(Player& player, int position) {
    int oldPosition = player.getPosition();
    player.moveToPosition(position);
    
    if (position < oldPosition && position != 0) {
        player.receiveMoney(Constants::PASS_GO_MONEY);
        std::cout << player.getName() << " passed GO and collected " << Constants::PASS_GO_MONEY << std::endl;
    }
    
    Square* landedSquare = board.getSquare(position);
    handleLanding(player, landedSquare);
}

void Game::sendPlayerToJail(Player& player) {
    player.goToJail();
    movePlayerTo(player, Constants::JAIL_POSITION);
    std::cout << player.getName() << " has been sent to Jail!" << std::endl;
}

void Game::nextPlayer() {
    Player* currentPlayer = getCurrentPlayer();
    if (!currentPlayer) return;
    if (!currentPlayer->getHasRolledDice()) return;

    currentPlayer->setHasRolledDice(false);
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
}

void Game::buyPropertyForCurrentPlayer() {
    Player* currentPlayer = getCurrentPlayer();
    if (!currentPlayer) return;

    Square* currentSquare = board.getSquare(currentPlayer->getPosition());
    Property* property = dynamic_cast<Property*>(currentSquare);
    
    if (property && !property->isOwned()) {
        if (currentPlayer->canAfford(property->getPrice())) {
            currentPlayer->buyProperty(*property);
            std::cout << currentPlayer->getName() << " bought " << property->getName() << std::endl;
        } else {
            std::cout << currentPlayer->getName() << " cannot afford " << property->getName() << std::endl;
        }
    } else {
        std::cout << "This square cannot be purchased or is already owned." << std::endl;
    }
}

void Game::buildHouseForCurrentPlayer() {
    Player* currentPlayer = getCurrentPlayer();
    if (!currentPlayer) return;

    Square* currentSquare = board.getSquare(currentPlayer->getPosition());
    if (StreetSquare* street = dynamic_cast<StreetSquare*>(currentSquare)) {
        if (street->getOwner() == currentPlayer && street->canBuildHouse()) {
            buildHouse(*currentPlayer, *street);
        }
    }
}

void Game::buildHotelForCurrentPlayer() {
    Player* currentPlayer = getCurrentPlayer();
    if (!currentPlayer) return;

    Square* currentSquare = board.getSquare(currentPlayer->getPosition());
    if (StreetSquare* street = dynamic_cast<StreetSquare*>(currentSquare)) {
        if (street->getOwner() == currentPlayer && street->canBuildHotel()) {
            buildHotel(*currentPlayer, *street);
        }
    }
}

std::vector<Property*> Game::getProperties() const {
    std::vector<Property*> properties;
    for (int i = 0; i < board.getSize(); ++i) {
        Square* square = board.getSquare(i);
        if (Property* property = dynamic_cast<Property*>(square)) {
            if (property == nullptr) {
                std::cout << "Warning: Null property at position " << i << std::endl;
            } else {
                properties.push_back(property);
            }
        }
    }
    return properties;
}

void Game::initializeDecks() {
    chanceDeck.shuffle();
    communityChestDeck.shuffle();
}