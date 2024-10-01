// This Class represents the Water\Electricity squares. there are two of these in our board
#include "utility_square.hpp"
#include "player.hpp"

UtilitySquare::UtilitySquare(const std::string& name, int price)
    : Property(name, price) {}

int UtilitySquare::getRent() const {
    if (!isOwned()) return 0;
    int ownedUtilities = 0;
    for (const auto& property : getOwner()->getProperties()) {
        if (property->getType() == "Utility") {
            ownedUtilities++;
        }
    }
    return calculateRent(ownedUtilities, 10);
}

void UtilitySquare::buyProperty(Player& buyer) {
    setOwner(&buyer);
    buyer.payMoney(getPrice());
    buyer.addProperty(this);
}

int UtilitySquare::calculateRent(int ownedUtilities, int diceRoll) {
    if (ownedUtilities == 1) {
        return 4 * diceRoll;
    } else if (ownedUtilities == 2) {
        return 10 * diceRoll;
    }
    return 0;
}