//this class is for the railroad properties, with rent calculated with a switch case
#include "railroad_square.hpp"
#include "player.hpp"

RailroadSquare::RailroadSquare(const std::string& name, int price)
    : Property(name, price) {}

int RailroadSquare::getRent() const {
    if (!isOwned()) return 0;
    int ownedRailroads = 0;
    for (const auto& property : getOwner()->getProperties()) {
        if (property->getType() == "Railroad") {
            ownedRailroads++;
        }
    }
    return calculateRent(ownedRailroads);
}

void RailroadSquare::buyProperty(Player& buyer) {
    setOwner(&buyer);
    buyer.payMoney(getPrice());
    buyer.addProperty(this);
}

int RailroadSquare::calculateRent(int ownedRailroads) {
    switch (ownedRailroads) {
        case 1: return 25;
        case 2: return 50;
        case 3: return 100;
        case 4: return 200;
        default: return 0;
    }
}