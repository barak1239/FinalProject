#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dice.hpp"
#include <algorithm>
#include <numeric>

TEST_CASE("Dice initialization") {
    Dice dice;
    auto initial_roll = dice.getLastRoll();
    CHECK(initial_roll[0] == 0);
    CHECK(initial_roll[1] == 0);
}

TEST_CASE("Dice rolling") {
    Dice dice;
    dice.roll();
    auto roll = dice.getLastRoll();
    CHECK(roll[0] >= 1);
    CHECK(roll[0] <= 6);
    CHECK(roll[1] >= 1);
    CHECK(roll[1] <= 6);
}

TEST_CASE("Dice total") {
    Dice dice;
    dice.roll();
    int total = dice.getTotal();
    CHECK(total >= 2);
    CHECK(total <= 12);
    CHECK(total == (dice.getLastRoll()[0] + dice.getLastRoll()[1]));
}

TEST_CASE("Dice doubles") {
    Dice dice;
    bool found_double = false;
    bool found_non_double = false;
    for (int i = 0; i < 100; ++i) {
        dice.roll();
        if (dice.isDouble()) {
            found_double = true;
            CHECK(dice.getLastRoll()[0] == dice.getLastRoll()[1]);
        } else {
            found_non_double = true;
            CHECK(dice.getLastRoll()[0] != dice.getLastRoll()[1]);
        }
        if (found_double && found_non_double) break;
    }
    CHECK(found_double);
    CHECK(found_non_double);
}

TEST_CASE("Dice distribution") {
    Dice dice;
    std::array<int, 13> frequency = {0};
    const int rolls = 10000;
    for (int i = 0; i < rolls; ++i) {
        dice.roll();
        ++frequency[dice.getTotal()];
    }
    // Check that all possible totals (2-12) have occurred
    for (int i = 2; i <= 12; ++i) {
        CHECK(frequency[i] > 0);
    }
    // Check that impossible totals have not occurred
    CHECK(frequency[0] == 0);
    CHECK(frequency[1] == 0);
}