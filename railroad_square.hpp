#ifndef RAILROAD_SQUARE_HPP
#define RAILROAD_SQUARE_HPP

#include "property.hpp"

class RailroadSquare : public Property {
public:
    RailroadSquare(const std::string& name, int price);

    int getRent() const override;
    void buyProperty(Player& buyer) override;
    std::string getType() const override { return "Railroad"; }

private:
    static int calculateRent(int ownedRailroads);
};

#endif // RAILROAD_SQUARE_HPP