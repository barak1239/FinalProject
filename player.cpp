//this is the implementation of the player class, it has everything to do with player actions, such as moving positions, paying money, etc
#include "player.hpp"
#include "property.hpp"
#include <algorithm>
#include "game.hpp"

Player::Player(const std::string& name)
    : name(name), money(Constants::INITIAL_MONEY), position(0), inJail(false) {}

void Player::receiveMoney(int amount) {
    money += amount;
}

bool Player::payMoney(int amount) {
    if (money >= amount) {
        money -= amount;
        return true;
    }
    return false;
}

void Player::moveToPosition(int newPosition) {
    position = newPosition % Constants::BOARD_SIZE;
}

void Player::moveForward(int spaces) {
    position = (position + spaces) % Constants::BOARD_SIZE;
}

void Player::goToJail() {
    moveToPosition(Constants::JAIL_POSITION);
    inJail = true;
}

void Player::getOutOfJail() {
    inJail = false;
}

void Player::addProperty(Property* property) {
    properties.push_back(property);
}

void Player::removeProperty(Property* property) {
    properties.erase(std::remove(properties.begin(), properties.end(), property), properties.end());
}

bool Player::ownsProperty(const Property* property) const {
    return std::find(properties.begin(), properties.end(), property) != properties.end();
}

bool Player::wantsToBuy(const Property& property) const {
    return canAfford(property.getPrice());
}

void Player::buyProperty(Property& property) {
    if (canAfford(property.getPrice())) {
        payMoney(property.getPrice());
        addProperty(&property);
        property.setOwner(this);
    }
}

void Player::payRent(int amount, Player& recipient) {
    if (payMoney(amount)) {
        recipient.receiveMoney(amount);
    }
}

bool Player::hasGetOutOfJailCard() const {
    return getOutOfJailCard;
}

bool Player::canPayBail() const {
    return money >= Constants::JAIL_BAIL_COST;
}

void Player::useGetOutOfJailCard(Game& game) {
    if (hasGetOutOfJailCard()) {
        getOutOfJailCard = false;
        game.returnGetOutOfJailCard();
        inJail = false;
    }
}

void Player::payBail(Game& game) {
    if (canPayBail()) {
        money -= Constants::JAIL_BAIL_COST;
        game.receivePayment(Constants::JAIL_BAIL_COST);
        inJail = false;
    }
}

void Player::takeTurn(Game& game, Dice& dice) {
    if (inJail) {
        if (hasGetOutOfJailCard()) {
            useGetOutOfJailCard(game);
        } else if (canPayBail()) {
            payBail(game);
        } else {
            dice.roll();
            if (dice.isDouble()) {
                inJail = false;
            } else {
                return;
            }
        }
    }
    
    int doublesCount = 0;
    do {
        dice.roll();
        int spaces = dice.getTotal();
        game.movePlayer(*this, spaces);
        Square* landedSquare = game.getBoard().getSquare(getPosition());
        game.handleLanding(*this, landedSquare);
        if (dice.isDouble()) {
            doublesCount++;
            if (doublesCount == 3) {
                goToJail();
                return;
            }
        } else {
            break;
        }
    } while (true);
}

void Player::giveGetOutOfJailCard() {
    getOutOfJailCard = true;
}

void Player::setHasRolledDice(bool Boolean) {
    hasRolledDice = Boolean;
}

bool Player::getHasRolledDice() {
    return hasRolledDice;
}

void Player::addCard(const std::string& card) {
    cards.push_back(card);
}

const std::vector<std::string>& Player::getCards() const {
    return cards;
}