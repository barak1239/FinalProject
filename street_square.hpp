#ifndef STREET_SQUARE_HPP
#define STREET_SQUARE_HPP

#include "property.hpp"
#include "color_group.hpp"
#include <vector>

class StreetSquare : public Property {
private:
    ColorGroup* colorGroup;
    int houseCount;
    bool hotel;
    int housePrice;
    int hotelPrice;
    std::vector<int> rentPrices;

public:
    StreetSquare(const std::string& name, int price, int housePrice, ColorGroup* colorGroup, const std::vector<int>& rentPrices);
    
    bool canBuildHouse() const;
    bool canBuildHotel() const;
    void addHouse();
    void addHotel();
    int getHouseCount() const { return houseCount; }
    bool hasHotel() const { return hotel; }
    int getHousePrice() const { return housePrice; }
    int getHotelPrice() const { return hotelPrice; }
    ColorGroup* getColorGroup() const { return colorGroup; }

    // we override these functions
    int getRent() const override;
    void buyProperty(Player& buyer) override;
};

#endif // STREET_SQUARE_HPP