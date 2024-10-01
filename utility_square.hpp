#ifndef UTILITY_SQUARE_HPP
#define UTILITY_SQUARE_HPP

#include "property.hpp"

class UtilitySquare : public Property {
public:
    UtilitySquare(const std::string& name, int price);

    int getRent() const override;
    void buyProperty(Player& buyer) override;
    std::string getType() const override { return "Utility"; }

private:
    static int calculateRent(int ownedUtilities, int diceRoll);
};

#endif // UTILITY_SQUARE_HPP