#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "property.hpp"
#include "player.hpp"

class TestProperty : public Property {
public:
    TestProperty(const std::string& name, int price) : Property(name, price) {}
    int getRent() const override { return 50; }
    void buyProperty(Player& buyer) override { setOwner(&buyer); }
};

TEST_CASE("Property actions") {
    TestProperty prop("Test Street", 200);
    Player player1("Player 1");
    Player player2("Player 2");

    SUBCASE("Initial state") {
        CHECK(prop.getName() == "Test Street");
        CHECK(prop.getPrice() == 200);
        CHECK_FALSE(prop.isOwned());
        CHECK(prop.getOwner() == nullptr);
    }

    SUBCASE("Buying property") {
        prop.buyProperty(player1);
        CHECK(prop.isOwned());
        CHECK(prop.getOwner() == &player1);
    }

    SUBCASE("Paying rent") {
        prop.buyProperty(player1);
        int initialMoney = player2.getMoney();
        prop.landOn(player2);
        CHECK(player2.getMoney() == initialMoney - 50);
        CHECK(player1.getMoney() == 1550);
    }
}