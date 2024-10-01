//this class has a few special squares and their actions in a if chain
#include "special_square.hpp"
#include "player.hpp"
#include "constants.hpp"

SpecialSquare::SpecialSquare(const std::string& name)
    : Square(name) {}

void SpecialSquare::landOn(Player& player) {
    if (getName() == "GO") {
        player.receiveMoney(Constants::PASS_GO_MONEY);
    } else if (getName() == "Income Tax") {
        player.payMoney(200);
    } else if (getName() == "Luxury Tax") {
        player.payMoney(75);
    } else if (getName() == "Go To Jail") {
        player.goToJail();
    }
}