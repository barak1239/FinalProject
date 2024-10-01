//this class initializes the board and has many useful functions
#include "board.hpp"
#include "square.hpp"
#include "street_square.hpp"
#include "railroad_square.hpp"
#include "utility_square.hpp"
#include "special_square.hpp"
#include "color_group.hpp"

Board::Board() : squares(40) {
    // Initialize color groups
    colorGroups = {
        std::make_shared<ColorGroup>("Brown", 2),
        std::make_shared<ColorGroup>("Light Blue", 3),
        std::make_shared<ColorGroup>("Pink", 3),
        std::make_shared<ColorGroup>("Orange", 3),
        std::make_shared<ColorGroup>("Red", 3),
        std::make_shared<ColorGroup>("Yellow", 3),
        std::make_shared<ColorGroup>("Green", 3),
        std::make_shared<ColorGroup>("Dark Blue", 2)
    };
    for(size_t i = 0; i<squares.size(); i++){
        initializeSquare(i);
    }
}

Square* Board::getSquare(int position) const {
    if (position >= 0 && position < static_cast<int>(squares.size())) {
        return squares[position].get();
    }
    return nullptr;
}

void Board::initializeSquare(int index) {
    switch(index) {
        case 0:
            squares[index] = std::make_unique<SpecialSquare>("GO");
            break;
        case 1:
            squares[index] = std::make_unique<StreetSquare>("Mediterranean Avenue", 60, 50, colorGroups[0].get(), std::vector<int>{2,10,30,90,160,250});
            break;
        case 2:
            squares[index] = std::make_unique<SpecialSquare>("Community Chest");
            break;
        case 3:
            squares[index] = std::make_unique<StreetSquare>("Baltic Avenue", 60, 50, colorGroups[0].get(), std::vector<int>{4,20,60,180,320,450});
            break;
        case 4:
            squares[index] = std::make_unique<SpecialSquare>("Income Tax");
            break;
        case 5:
            squares[index] = std::make_unique<RailroadSquare>("Reading Railroad", 200);
            break;
        case 6:
            squares[index] = std::make_unique<StreetSquare>("Oriental Avenue", 100, 50, colorGroups[1].get(), std::vector<int>{6,30,90,270,400,550});
            break;
        case 7:
            squares[index] = std::make_unique<SpecialSquare>("Chance");
            break;
        case 8:
            squares[index] = std::make_unique<StreetSquare>("Vermont Avenue", 100, 50, colorGroups[1].get(), std::vector<int>{6,30,90,270,400,550});
            break;
        case 9:
            squares[index] = std::make_unique<StreetSquare>("Connecticut Avenue", 120, 50, colorGroups[1].get(), std::vector<int>{8,40,100,300,450,600});
            break;
        case 10:
            squares[index] = std::make_unique<SpecialSquare>("Jail");
            break;
        case 11:
            squares[index] = std::make_unique<StreetSquare>("St. Charles Place", 140, 100, colorGroups[2].get(), std::vector<int>{10,50,150,450,625,750});
            break;
        case 12:
            squares[index] = std::make_unique<UtilitySquare>("Electric Company", 150);
            break;
        case 13:
            squares[index] = std::make_unique<StreetSquare>("States Avenue", 140, 100, colorGroups[2].get(), std::vector<int>{10,50,150,450,625,750});
            break;
        case 14:
            squares[index] = std::make_unique<StreetSquare>("Virginia Avenue", 160, 100, colorGroups[2].get(), std::vector<int>{12,60,180,500,700,900});
            break;
        case 15:
            squares[index] = std::make_unique<RailroadSquare>("Pennsylvania Railroad", 200);
            break;
        case 16:
            squares[index] = std::make_unique<StreetSquare>("St. James Place", 180, 100, colorGroups[3].get(), std::vector<int>{14,70,200,550,750,950});
            break;
        case 17:
            squares[index] = std::make_unique<SpecialSquare>("Community Chest");
            break;
        case 18:
            squares[index] = std::make_unique<StreetSquare>("Tennessee Avenue", 180, 100, colorGroups[3].get(), std::vector<int>{14,70,200,550,750,950});
            break;
        case 19:
            squares[index] = std::make_unique<StreetSquare>("New York Avenue", 200, 100, colorGroups[3].get(), std::vector<int>{16,80,220,600,800,1000});
            break;
        case 20:
            squares[index] = std::make_unique<SpecialSquare>("Free Parking");
            break;
        case 21:
            squares[index] = std::make_unique<StreetSquare>("Kentucky Avenue", 220, 150, colorGroups[4].get(), std::vector<int>{18,90,250,700,875,1050});
            break;
        case 22:
            squares[index] = std::make_unique<SpecialSquare>("Chance");
            break;
        case 23:
            squares[index] = std::make_unique<StreetSquare>("Indiana Avenue", 220, 150, colorGroups[4].get(), std::vector<int>{18,90,250,700,875,1050});
            break;
        case 24:
            squares[index] = std::make_unique<StreetSquare>("Illinois Avenue", 240, 150, colorGroups[4].get(), std::vector<int>{20,100,300,750,925,1100});
            break;
        case 25:
            squares[index] = std::make_unique<RailroadSquare>("B. & O. Railroad", 200);
            break;
        case 26:
            squares[index] = std::make_unique<StreetSquare>("Atlantic Avenue", 260, 150, colorGroups[5].get(), std::vector<int>{22,110,330,800,975,1150});
            break;
        case 27:
            squares[index] = std::make_unique<StreetSquare>("Ventnor Avenue", 260, 150, colorGroups[5].get(), std::vector<int>{22,110,330,800,975,1150});
            break;
        case 28:
            squares[index] = std::make_unique<UtilitySquare>("Water Works", 150);
            break;
        case 29:
            squares[index] = std::make_unique<StreetSquare>("Marvin Gardens", 280, 150, colorGroups[5].get(), std::vector<int>{24,120,360,850,1025,1200});
            break;
        case 30:
            squares[index] = std::make_unique<SpecialSquare>("Go To Jail");
            break;
        case 31:
            squares[index] = std::make_unique<StreetSquare>("Pacific Avenue", 300, 200, colorGroups[6].get(), std::vector<int>{26,130,390,900,1100,1275});
            break;
        case 32:
            squares[index] = std::make_unique<StreetSquare>("North Carolina Avenue", 300, 200, colorGroups[6].get(), std::vector<int>{26,130,390,900,1100,1275});
            break;
        case 33:
            squares[index] = std::make_unique<SpecialSquare>("Community Chest");
            break;
        case 34:
            squares[index] = std::make_unique<StreetSquare>("Pennsylvania Avenue", 320, 200, colorGroups[6].get(), std::vector<int>{28,150,450,1000,1200,1400});
            break;
        case 35:
            squares[index] = std::make_unique<RailroadSquare>("Short Line", 200);
            break;
        case 36:
            squares[index] = std::make_unique<SpecialSquare>("Chance");
            break;
        case 37:
            squares[index] = std::make_unique<StreetSquare>("Park Place", 350, 200, colorGroups[7].get(), std::vector<int>{35,175,500,1100,1300,1500});
            break;
        case 38:
            squares[index] = std::make_unique<SpecialSquare>("Luxury Tax");
            break;
        case 39:
            squares[index] = std::make_unique<StreetSquare>("Boardwalk", 400, 200, colorGroups[7].get(), std::vector<int>{50,200,600,1400,1700,2000});
            break;
        default:
            squares[index] = std::make_unique<SpecialSquare>("Unknown");
    }
}
int Board::findPropertyPosition(const Property* property) const {
    for (size_t i = 0; i < squares.size(); ++i) {
        if (squares[i].get() == property) {
            return static_cast<int>(i);
        }
    }
    return -1;  // if the property was not found
}