//this is also a generic Property class, it holds prices and ownership and such
#include "property.hpp"
#include "player.hpp"
#include "board.hpp"
Property::Property(const std::string& name, int price)
    : Square(name), price(price), owner(nullptr) {}

int Property::getPrice() const {
    return price;
}

Player* Property::getOwner() const {
    return owner;
}

void Property::setOwner(Player* newOwner) {
    owner = newOwner;
}

bool Property::isOwned() const {
    return owner != nullptr;
}

void Property::landOn(Player& player) {
    if (isOwned()) {
        if (owner != &player) {
            // Pay rent
            int rentAmount = getRent();
            player.payRent(rentAmount, *owner);
        }
    }
}

std::string Property::getType() const {
    return "Property";
}

int Property::getPosition(const Board* b) const {
    if (b) {
        for (int i = 0; i < b->getSize(); ++i) {
            if (b->getSquare(i) == this) {
                return i;
            }
        }
    }
    
    // we return -1 if the property is not found on the board
    return -1;
}