//this is the GUI implementation, it uses SFML and takes care of graphics logic
#include "MonopolyGUI.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>
#include "street_square.hpp"
#include "game.hpp"
MonopolyGUI::MonopolyGUI(Game& game) 
    : game(game), window(sf::VideoMode(800, 800), "Monopoly") {
    
    if (!font.loadFromFile("kabel.ttf")) {
        std::cerr << "Error loading font. Please ensure a .ttf font file is available." << std::endl;
        exit(1);
    }

    if (!boardTexture.loadFromFile("monopoly_board.png")) {
        std::cerr << "Error loading board texture. Please ensure 'monopoly_board.png' is in the current directory." << std::endl;
        exit(1);
    }

    boardSprite.setTexture(boardTexture);
    boardSprite.setScale(
        800.0f / boardTexture.getSize().x,
        800.0f / boardTexture.getSize().y
    );

    // Initialize players using icon images from real game :)
    std::vector<std::string> playerImages = {"player1.png", "player2.png", "player3.png", "player4.png", "player5.png", "player6.png", "player7.png", "player8.png"};
    int i = 0;
    for (const auto& player : game.players) {
        sf::Texture texture;
        if (!texture.loadFromFile(playerImages[i % playerImages.size()])) {
            std::cerr << "Error loading player texture." << std::endl;
            exit(1);
        }
        playerTextures[player->getName()] = texture;
        playerSprites[player->getName()].setTexture(playerTextures[player->getName()]);
        playerSprites[player->getName()].setScale(0.5f, 0.5f);  // scale adjustment
        i++;
    }

    initializeButtons();
}

void MonopolyGUI::initializeButtons() {
    sf::Vector2f buttonSize(100, 50);
    float buttonY = 450;

    diceRollButton = sf::RectangleShape(buttonSize);
    diceRollButton.setPosition(150, buttonY);
    diceRollButton.setFillColor(sf::Color::Green);

    buyPropertyButton = sf::RectangleShape(buttonSize);
    buyPropertyButton.setPosition(255, buttonY);
    buyPropertyButton.setFillColor(sf::Color::Blue);

    buildHouseButton = sf::RectangleShape(buttonSize);
    buildHouseButton.setPosition(360, buttonY);
    buildHouseButton.setFillColor(sf::Color::Yellow);

    buildHotelButton = sf::RectangleShape(buttonSize);
    buildHotelButton.setPosition(360, buttonY + 50);
    buildHotelButton.setFillColor(sf::Color::Cyan);

    endTurnButton = sf::RectangleShape(buttonSize);
    endTurnButton.setPosition(465, buttonY);
    endTurnButton.setFillColor(sf::Color::Red);

    showDataButton = sf::RectangleShape(buttonSize);
    showDataButton.setPosition(570, buttonY);
    showDataButton.setFillColor(sf::Color::Magenta);

    // Initialize button texts
    auto initText = [this](sf::Text& text, const std::string& str, const sf::RectangleShape& button) {
        text.setFont(font);
        text.setString(str);
        text.setCharacterSize(12);
        text.setFillColor(sf::Color::White);
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
        text.setPosition(button.getPosition().x + button.getSize().x/2.0f, button.getPosition().y + button.getSize().y/2.0f);
    };

    initText(diceRollText, "Roll Dice", diceRollButton);
    initText(buyPropertyText, "Buy Property", buyPropertyButton);
    initText(buildHouseText, "Build House", buildHouseButton);
    initText(buildHotelText, "Build Hotel", buildHotelButton);
    initText(endTurnText, "End Turn", endTurnButton);
    initText(showDataText, "Show Data", showDataButton);
}

void MonopolyGUI::run() {
    game.startGame();

    while (window.isOpen() && !game.isGameOver()) {
        handleEvents();
        update();
        render();
    }
    
    // Game over screen
    window.clear(sf::Color::White);
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("Game Over!");
    gameOverText.setCharacterSize(40);
    gameOverText.setFillColor(sf::Color::Black);
    gameOverText.setPosition(300, 300);
    window.draw(gameOverText);
    window.display();

    sf::Event event;
    while (window.waitEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void MonopolyGUI::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                handleButtonClick(mousePos);
            }
        }
    }
}

void MonopolyGUI::handleButtonClick(const sf::Vector2f& mousePos) {
    if (diceRollButton.getGlobalBounds().contains(mousePos)) {
        game.playTurn();
    } else if (buyPropertyButton.getGlobalBounds().contains(mousePos)) {
        game.buyPropertyForCurrentPlayer();
    } else if (buildHouseButton.getGlobalBounds().contains(mousePos)) {
        game.buildHouseForCurrentPlayer();
    } else if (endTurnButton.getGlobalBounds().contains(mousePos)) {
        game.nextPlayer();
    } else if (showDataButton.getGlobalBounds().contains(mousePos)) {
        showPlayerData();
    } else if (buildHotelButton.getGlobalBounds().contains(mousePos)) {
        game.buildHotelForCurrentPlayer();
    }
}

void MonopolyGUI::update() {
    for (const auto& player : game.players) {
        sf::Vector2f pos = calculatePlayerPosition(player->getPosition());
        playerSprites[player->getName()].setPosition(pos);
    }
}

void MonopolyGUI::render() {
    window.clear(sf::Color::White);
    drawBoard();
    drawPlayers();
    drawPlayerInfo();
    window.draw(diceRollButton);
    window.draw(diceRollText);
    window.draw(buyPropertyButton);
    window.draw(buyPropertyText);
    window.draw(buildHouseButton);
    window.draw(buildHouseText);
    window.draw(buildHotelButton);
    window.draw(buildHotelText);
    window.draw(endTurnButton);
    window.draw(endTurnText);
    window.draw(showDataButton);
    window.draw(showDataText);
    window.display();
}

void MonopolyGUI::drawBoard() {
    window.draw(boardSprite);
}

void MonopolyGUI::drawPlayers() {
    for (const auto& sprite : playerSprites) {
        window.draw(sprite.second);
    }
}

void MonopolyGUI::drawPlayerInfo() {
    Player* currentPlayer = game.getCurrentPlayer();
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setString("Current Player: " + currentPlayer->getName() + 
                   "\nMoney: $" + std::to_string(currentPlayer->getMoney()) +
                   "\nSquare: " + game.getBoard().getSquare(currentPlayer->getPosition())->getName());
    text.setPosition(10, 10);
    window.draw(text);
}

sf::Vector2f MonopolyGUI::calculatePlayerPosition(int boardPosition) {
    const float boardSize = 800.0f;
    const float squareSize = boardSize / 11.0f;
    const float offset = squareSize / 2.0f;

    if (boardPosition < 10) {
        return sf::Vector2f(boardSize - offset - (boardPosition * squareSize), boardSize - offset);
    } else if (boardPosition < 20) {
        return sf::Vector2f(offset, boardSize - offset - ((boardPosition - 10) * squareSize));
    } else if (boardPosition < 30) {
        return sf::Vector2f(offset + ((boardPosition - 20) * squareSize), offset);
    } else {
        return sf::Vector2f(boardSize - offset, offset + ((boardPosition - 30) * squareSize));
    }
}

void MonopolyGUI::showPlayerData() {
    std::string dataInfo;
    for (const auto& player : game.players) {
        dataInfo += player->getName() + ":\n";
        dataInfo += "  Money: $" + std::to_string(player->getMoney()) + "\n";
        
        // Properties
        dataInfo += "  Properties owned:\n";
        for (const auto& property : player->getProperties()) {
            dataInfo += "    - " + property->getName();
            if (auto* street = dynamic_cast<StreetSquare*>(property)) {
                if (!street->hasHotel()){
                    dataInfo += " (Houses: " + std::to_string(street->getHouseCount()) + ")";
                }
                else {
                    dataInfo += " (Hotel!)";
                }
            }
            dataInfo += "\n";
        }
        
        // cards
        dataInfo += "  Cards:\n";
        const auto& playerCards = player->getCards();
        if (playerCards.empty()) {
            dataInfo += "    No cards\n";
        } else {
            for (const auto& card : playerCards) {
                dataInfo += "    - " + card + "\n";
            }
        }
        dataInfo += "\n";
    }

    sf::Text dataText;
    dataText.setFont(font);
    dataText.setString(dataInfo);
    dataText.setCharacterSize(16);
    dataText.setFillColor(sf::Color::Black);

    sf::RectangleShape background(sf::Vector2f(600, 400));
    background.setFillColor(sf::Color(255, 255, 255, 230));
    background.setPosition(100, 200);

    dataText.setPosition(120, 220);

    window.draw(background);
    window.draw(dataText);
    window.display();
    sf::Event event;
    while (window.waitEvent(event)) {
        if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::Closed) {
            break;
        }
    }
}