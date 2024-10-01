#ifndef SPECIAL_SQUARE_HPP
#define SPECIAL_SQUARE_HPP

#include "square.hpp"

class SpecialSquare : public Square {
public:
    SpecialSquare(const std::string& name);
    
    void landOn(Player& player) override;
    std::string getType() const override { return "Special"; }
};

#endif // SPECIAL_SQUARE_HPP