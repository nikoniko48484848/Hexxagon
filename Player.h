#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#ifndef HEXXAGON_PLAYER_H
#define HEXXAGON_PLAYER_H


class Player {
public:
    sf::CircleShape body;
    sf::CircleShape dupeRadius;
    sf::CircleShape moveRadius;
    sf::CircleShape captureRadius;
    sf::CircleShape botMoveRadius;
    std::vector<sf::CircleShape> pawnsVec;
    bool myTurn;

    Player();
    virtual ~Player();

    void initBody();
    void initDupeRadius();
    void initMoveRadius();
    void initCaptureRadius();
    void initBotMoveRadius();
};


#endif //HEXXAGON_PLAYER_H