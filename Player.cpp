#include "Player.h"

/**
 * @brief Initializes the player's body.
 */
void Player::initBody() {
    this->body.setRadius(15);
}

/**
 * @brief Initializes the player's duplication radius.
 */
void Player::initDupeRadius() {
    this->dupeRadius.setFillColor(sf::Color::Transparent);
    this->dupeRadius.setOutlineThickness(2);
    this->dupeRadius.setPointCount(6);
    this->dupeRadius.setRadius(50);
}

/**
 * @brief Initializes the player's movement radius.
 */
void Player::initMoveRadius() {
    this->moveRadius.setFillColor(sf::Color::Transparent);
    this->moveRadius.setOutlineThickness(3);
    this->moveRadius.setPointCount(6);
    this->moveRadius.setRadius(100);
}

/**
 * @brief Initializes the player's capture radius.
 */
void Player::initCaptureRadius() {
    this->captureRadius.setFillColor(sf::Color::Transparent);
    this->captureRadius.setOutlineColor(sf::Color::Transparent);
    this->captureRadius.setOutlineThickness(3);
    this->captureRadius.setRadius(80);
}

/**
 * @brief Initializes the player's bot movement radius.
 */
void Player::initBotMoveRadius() {
    this->botMoveRadius.setFillColor(sf::Color::Black );
    this->botMoveRadius.setOutlineColor(sf::Color::Black);
    this->botMoveRadius.setOutlineThickness(3);
    this->botMoveRadius.setRadius(90);
}

/**
 * @brief Default constructor for Player class.
 * Initializes the player's body and various radius components.
 */
Player::Player() {
    this->initBody();
    this->initDupeRadius();
    this->initMoveRadius();
    this->initCaptureRadius();
    this->initBotMoveRadius();
}

/**
 * @brief Destructor for Player class.
 */
Player::~Player() = default;



