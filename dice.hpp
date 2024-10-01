//this class implements the dice, rolls, totals, etc
#ifndef DICE_HPP
#define DICE_HPP

#include <array>
#include <random>
#include <chrono>

class Dice {
private:
    std::array<int, 2> lastRoll;
    std::mt19937 rng;

public:
    Dice() : lastRoll{0, 0}, rng(std::chrono::system_clock::now().time_since_epoch().count()) {}

    void roll() {
        std::uniform_int_distribution<int> dist(1, 6);
        lastRoll[0] = dist(rng);
        lastRoll[1] = dist(rng);
    }

    int getTotal() const {
        return lastRoll[0] + lastRoll[1];
    }

    bool isDouble() const {
        return lastRoll[0] == lastRoll[1];
    }

    std::array<int, 2> getLastRoll() const {
        return lastRoll;
    }
};

#endif // DICE_HPP