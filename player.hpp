#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>
#include <vector>
#include "constants.hpp"
#include "dice.hpp"

class Property;
class Square;
class Game;

class Player {
private:
    std::string name;
    int money;
    int position;
    bool inJail;
    std::vector<Property*> properties;
    bool getOutOfJailCard = false;
    bool hasRolledDice = false;
    std::vector<std::string> cards;

public:
    Player(const std::string& name);
    
    // Getters
    std::string getName() const { return name; }
    int getMoney() const { return money; }
    int getPosition() const { return position; }
    bool isInJail() const { return inJail; }
    const std::vector<Property*>& getProperties() const { return properties; }
    
    // Money management
    void receiveMoney(int amount);
    bool payMoney(int amount);
    bool canAfford(int amount) const { return money >= amount; }
    
    // Movement
    void moveToPosition(int newPosition);
    void moveForward(int spaces);
    
    // Jail
    void goToJail();
    void getOutOfJail();
    
    // Property management
    void addProperty(Property* property);
    void removeProperty(Property* property);
    bool ownsProperty(const Property* property) const;
    
    // Game actions
    bool wantsToBuy(const Property& property) const;
    void buyProperty(Property& property);
    void payRent(int amount, Player& recipient);
    
    // Turn actions
    void takeTurn(Game& game, Dice& dice);
    bool hasGetOutOfJailCard() const;
    void useGetOutOfJailCard(Game& game);
    bool canPayBail() const;
    void payBail(Game& game);
    void giveGetOutOfJailCard();
    void setHasRolledDice(bool Boolean);
    bool getHasRolledDice();

    // Card management
    void addCard(const std::string& card);
    const std::vector<std::string>& getCards() const;
};

#endif // PLAYER_HPP