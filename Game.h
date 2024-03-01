#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "Player.h"

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#ifndef HEXXAGON_GAME_H
#define HEXXAGON_GAME_H

class Game {
private:
    //Variables
    //Window

    sf::VideoMode videoMode;
    sf::Event ev{};

    //Mouse position
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //Resources
    Player playerBase;
    Player player1;
    Player player2;
    sf::Vector2f bodyPos;
    int countTransparentPawns = 0;
    int countWhitePawns = 3;
    int countBlackPawns = 3;
    bool endgame = false;
    bool pvpChosen = false;
    bool pveChosen = false;
    sf::RectangleShape button;
    sf::RectangleShape button1;
    bool captured = false;
    bool moved = false;
    std::vector<int> pawnValueVec;

    //Sounds
    sf::SoundBuffer soundBuffer;
    sf::Sound boop;
    sf::SoundBuffer soundBuffer1;
    sf::Sound money;

    //Text
    sf::Font font;
    sf::Text turnText;
    sf::Text pointText;
    sf::Text startText;
    sf::Text startText1;
    sf::Text startText2;
    sf::Text gameOverText;
    sf::Text gameOverText1;


    //Game logic
    bool mouseHeld{};
    bool endGame{};

    //Game objects
    std::vector<sf::CircleShape> fieldsVec;
    sf::CircleShape field;
    sf::CircleShape toDelete;

    //Private functions
    void initButtons();
    void initVariables();
    void initWindow();
    void initFields();
    void initFonts();
    void initBoop();

public:
    sf::RenderWindow* gameWindow{};
    //Constructors / Destructors
    Game();
    virtual ~Game();

    //Accessors
    bool running() const;
    bool getEndGame() const;

    //Functions
    void createBoard();
    void createPawns();
    void pollEvents();
    void updateStartingWindow();
    void updateMousePos();
    void setStartingPawns(int firstPawn, int secondPawn, int thirdPawn, sf::Color pawnColor);
    void setRadiusesForPlayer(Player& p, int x, sf::Color radiusColor);
    void updateFields();
    void updateFieldsBot();
    void updateText();
    void update();
    void renderButtons();
    void renderFields();
    void renderBody();
    void renderText();
    void renderStartText();
    void updateStartText();
    void render();
    void updateGameOverText();
    void renderGameOverText();


};


#endif //HEXXAGON_GAME_H