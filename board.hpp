#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <memory>
#include <string>
#include "property.hpp"

class Square;
class ColorGroup;
class StreetSquare;
class RailroadSquare;
class UtilitySquare;
class SpecialSquare;

class Board {
private:
    std::vector<std::unique_ptr<Square>> squares;
    std::vector<std::shared_ptr<ColorGroup>> colorGroups;
    void initializeSquare(int index);

public:
    Board();
    Square* getSquare(int position) const;
    int getSize() const { return squares.size(); }
    int findPropertyPosition(const Property* property) const;
};

#endif // BOARD_HPP