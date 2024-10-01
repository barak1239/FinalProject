#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include "square.hpp"
#include "constants.hpp"

class Player; // Forward declaration
class Board;

class Property : public Square {
protected:
    int price;
    Player* owner;

public:
    Property(const std::string& name, int price);
    virtual ~Property() = default;

    int getPrice() const;
    Player* getOwner() const;
    void setOwner(Player* newOwner);
    bool isOwned() const;

    // Pure virtual functions we will impement them in other classes
    virtual int getRent() const = 0;
    virtual void buyProperty(Player& buyer) = 0;

    //we override from Square
    void landOn(Player& player) override;
    std::string getType() const override;
    virtual int getPosition(const Board* b) const;
};

#endif // PROPERTY_HPP