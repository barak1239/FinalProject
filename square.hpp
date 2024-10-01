//this is a generic class for the squares in the board
#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <string>

class Player; // Forward declaration

class Square {
protected:
    std::string name;

public:
    Square(const std::string& name) : name(name) {}
    virtual ~Square() = default;

    std::string getName() const { return name; }
    virtual void landOn(Player& player) = 0;
    virtual std::string getType() const = 0;
};

#endif // SQUARE_HPP