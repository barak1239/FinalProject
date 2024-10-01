#ifndef MONOPOLYGUI_HPP
#define MONOPOLYGUI_HPP
#include <SFML/Graphics.hpp>
#include "game.hpp"
#include <map>

class MonopolyGUI {
private:
    Game& game;
    sf::RenderWindow window;
    sf::Font font;
    sf::Texture boardTexture;
    sf::Sprite boardSprite;
    std::map<std::string, sf::Texture> playerTextures;
    std::map<std::string, sf::Sprite> playerSprites;
 
    sf::RectangleShape diceRollButton;
    sf::RectangleShape buyPropertyButton;
    sf::RectangleShape buildHouseButton;
    sf::RectangleShape buildHotelButton;
    sf::RectangleShape endTurnButton;
    sf::RectangleShape showDataButton;
    
    sf::Text diceRollText;
    sf::Text buyPropertyText;
    sf::Text buildHouseText;
    sf::Text buildHotelText;
    sf::Text endTurnText;
    sf::Text showDataText;

    void initializeButtons();
    void drawBoard();
    void drawPlayers();
    void drawPlayerInfo();
    void drawProperties();
    void handleEvents();
    void update();
    void render();
    sf::Vector2f calculatePlayerPosition(int boardPosition);
    void handleButtonClick(const sf::Vector2f& mousePos);
    void showPlayerData();

public:
    MonopolyGUI(Game& game);
    void run();
};

#endif // MONOPOLYGUI_HPP