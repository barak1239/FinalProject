//this class represents the normal properties, they have houses and hotels and functions to help with rent
#include "street_square.hpp"
#include "player.hpp"

StreetSquare::StreetSquare(const std::string& name, int price, int housePrice, ColorGroup* colorGroup, const std::vector<int>& rentPrices)
    : Property(name, price), colorGroup(colorGroup), houseCount(0), hotel(false), housePrice(housePrice), hotelPrice(housePrice * 5), rentPrices(rentPrices) {}

bool StreetSquare::canBuildHouse() const {
    return houseCount < 4 && !hotel;
}

bool StreetSquare::canBuildHotel() const {
    return houseCount == 4 && !hotel;
}

void StreetSquare::addHouse() {
    if (canBuildHouse()) {
        houseCount++;
    }
}

void StreetSquare::addHotel() {
    if (canBuildHotel()) {
        hotel = true;
        houseCount = 0;
    }
}

int StreetSquare::getRent() const {
    if (hotel) {
        return rentPrices.back();
    } else if (houseCount > 0) {
        return rentPrices[houseCount];
    } else if (colorGroup->hasMonopoly()) {
        return rentPrices[0] * 2;
    } else {
        return rentPrices[0];
    }
}

void StreetSquare::buyProperty(Player& buyer) {
    setOwner(&buyer);
    buyer.payMoney(getPrice());
    buyer.addProperty(this);
    colorGroup->addProperty(this);
}