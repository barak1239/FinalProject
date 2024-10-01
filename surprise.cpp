//This file has two classes, SurpriseCard and SurpriseDeck, the first represents a chance\chest card, the second contains the entire deck with each card having a function as the action
#include "surprise.hpp"
#include "player.hpp"
#include "game.hpp"
#include <algorithm>
#include <random>
#include <iostream>

SurpriseCard::SurpriseCard(const std::string& description, std::function<void(Player&, Game&)> action)
    : description(description), action(action) {}

void SurpriseCard::execute(Player& player, Game& game) {
    action(player, game);
}

std::string SurpriseCard::getDescription() const {
    return description;
}

SurpriseDeck::SurpriseDeck() : cards({
    SurpriseCard("Advance to GO", [](Player& p, Game& g) { g.movePlayerTo(p, 0); }),
    SurpriseCard("Go to Jail", [](Player& p, Game& g) { g.sendPlayerToJail(p); }),
    SurpriseCard("Get out of Jail Free", [](Player& p, Game&) { p.giveGetOutOfJailCard(); }),
    SurpriseCard("Collect $200", [](Player& p, Game&) { p.receiveMoney(200); }),
    SurpriseCard("Go to Jail", [](Player& p, Game& g) { g.sendPlayerToJail(p); }),
    SurpriseCard("Get out of Jail Free", [](Player& p, Game&) { p.giveGetOutOfJailCard(); }),
    SurpriseCard("Collect $500", [](Player& p, Game&) { p.receiveMoney(500); }),
    SurpriseCard("Debt $200", [](Player& p, Game&) { p.payMoney(200); }),
}) {}

void SurpriseDeck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g); //a way to shuffle the deck using stl
}

SurpriseCard SurpriseDeck::drawCard() {
    SurpriseCard card = cards.back();
    cards.pop_back();
    cards.insert(cards.begin(), card);
    return card;
}