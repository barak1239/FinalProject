#ifndef SURPRISE_HPP
#define SURPRISE_HPP

#include <vector>
#include <string>
#include <functional>

// Forward declarations
class Player;
class Game;

class SurpriseCard {
public:
    SurpriseCard(const std::string& description, std::function<void(Player&, Game&)> action);
    void execute(Player& player, Game& game);
    std::string getDescription() const;

private:
    std::string description;
    std::function<void(Player&, Game&)> action;
};

class SurpriseDeck {
public:
    SurpriseDeck();
    void shuffle();
    SurpriseCard drawCard();

private:
    std::vector<SurpriseCard> cards;
};

#endif // SURPRISE_HPP