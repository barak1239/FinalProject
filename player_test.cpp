#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "player.hpp"
#include "property.hpp"

TEST_CASE("Player actions") {
    Player player("Test Player");

    SUBCASE("Initial state") {
        CHECK(player.getName() == "Test Player");
        CHECK(player.getMoney() == 1500);
        CHECK(player.getPosition() == 0);
        CHECK_FALSE(player.isInJail());
    }

    SUBCASE("Money transactions") {
        player.receiveMoney(500);
        CHECK(player.getMoney() == 2000);
        CHECK(player.payMoney(300));
        CHECK(player.getMoney() == 1700);
        CHECK_FALSE(player.payMoney(2000));
        CHECK(player.getMoney() == 1700);
    }

    SUBCASE("Movement") {
        player.moveForward(5);
        CHECK(player.getPosition() == 5);
        player.moveForward(37);
        CHECK(player.getPosition() == 2);
    }

    SUBCASE("Jail") {
        player.goToJail();
        CHECK(player.isInJail());
        CHECK(player.getPosition() == 10);
        player.getOutOfJail();
        CHECK_FALSE(player.isInJail());
    }
}