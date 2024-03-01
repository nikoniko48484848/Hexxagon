#include "Game.h"
#include "Player.h"

/**
 * @brief Constructs a Game object.
 * Initializes variables, buttons, window, fields, fonts, and sets the framerate limit to 60.
 */
Game::Game() : turnText(this->font), pointText(this->font), startText(this->font), startText1(this->font),
               gameOverText(this->font), gameOverText1(this->font), startText2(this->font) {
    this->initVariables();
    this->initButtons();
    this->initWindow();
    this->initFields();
    this->initFonts();
    this->initBoop();
    this->gameWindow->setFramerateLimit(60);
}

/**
 * @brief Destroys the Game object.
 * Deletes the game window.
 */
Game::~Game() {
    delete this->gameWindow;
}

/**
 * @brief Checks if the game is running.
 * @return True if the game window is open, false otherwise.
 */
bool Game::running() const {
    return this->gameWindow->isOpen();
}

/**
 * @brief Retrieves the endGame status.
 * @return True if the game has ended, false otherwise.
 */
bool Game::getEndGame() const {
    return this->endGame;
}

/**
 * @brief Polls events.
 * Handles window close event and the escape key press event to close the game.
 */
void Game::pollEvents() {

    // Event polling
    while (this->gameWindow->pollEvent(this->ev)) {
        switch (this->ev.type) {
            case sf::Event::Closed:
                this->gameWindow->close();
                break;
            case sf::Event::KeyPressed:
                if (ev.key.code == sf::Keyboard::Escape)
                    this->gameWindow->close();
                break;
        }
    }

}

/**
 * @brief Creates the game board.
 * Initializes and positions the fields on the board based on their coordinates.
 */

void Game::createBoard() {
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++){
            if (y % 2) {
                this->field.setPosition({110 + y * 45.f, 95 + x * 50.f});
            } else {
                this->field.setPosition({110 + y * 45.f, 70 + x * 50.f});
            }
            if ((y == 0 && (x == 0 || x == 1 || x == 7 || x == 8)) ||
                (y == 1 && (x == 0 || x == 7 || x == 8)) ||
                (y == 2 && (x == 0 || x == 8)) ||
                (y == 3 && (x == 8 || x == 4)) ||
                (y == 4 && x == 3) ||
                (y == 5 && (x == 8 || x == 4)) ||
                (y == 6 && (x == 0 || x == 8)) ||
                (y == 7 && (x == 0 || x == 7 || x == 8)) ||
                (y == 8 && (x == 0 || x == 1 || x == 7 || x == 8))) {
                this->field.setFillColor(sf::Color::Transparent);
                this->field.setOutlineColor(sf::Color::Transparent);
            } else {
                this->field.setFillColor(sf::Color(189, 134, 68));
                this->field.setOutlineColor(sf::Color(87, 54, 16));
            }
            this->fieldsVec.push_back(this->field);
        }
    }
}

/**
 * @brief Create pawns for the game.
 */

void Game::createPawns() {
    this->playerBase = Player();
    this->player1 = Player();
    this->player2 = Player();
    for (int y = 0; y < 9; y++) {
        for (float x = 0; x < 9; x++){
            if (y % 2) {
                this->playerBase.body.setPosition({105 + y * 45.f, 115 + x * 50.f});
            } else {
                this->playerBase.body.setPosition({105 + y * 45.f, 90 + x * 50.f});
            }
            if ((y == 0 && (x == 0 || x == 1 || x == 7 || x == 8)) ||
                (y == 1 && (x == 0 || x == 7 || x == 8)) ||
                (y == 2 && (x == 0 || x == 8)) ||
                (y == 3 && (x == 8 || x == 4)) ||
                (y == 4 && x == 3) ||
                (y == 5 && (x == 8 || x == 4)) ||
                (y == 6 && (x == 0 || x == 8)) ||
                (y == 7 && (x == 0 || x == 7 || x == 8)) ||
                (y == 8 && (x == 0 || x == 1 || x == 7 || x == 8))) {
                this->playerBase.body.setFillColor(sf::Color(0, 0, 0, 1));
            } else {
                this->playerBase.body.setFillColor(sf::Color::Transparent);

            }
            this->playerBase.pawnsVec.push_back(playerBase.body);
        }
    }
    this->setStartingPawns(44, 74, 2, sf::Color::White);
    this->setStartingPawns(6, 36, 78, sf::Color::Black);
    this->setRadiusesForPlayer(player1, 2, sf::Color::Red);
    this->bodyPos = playerBase.pawnsVec[2].getPosition();
    this->setRadiusesForPlayer(player2, 78, sf::Color::Transparent);
    this->player1.myTurn = true;
    this->player2.myTurn = false;
}

/**
 * @brief Set the starting pawns for a player.
 *
 * @param firstPawn Index of the first pawn.
 * @param secondPawn Index of the second pawn.
 * @param thirdPawn Index of the third pawn.
 * @param pawnColor Color of the pawns.
 */

void Game::setStartingPawns(int firstPawn, int secondPawn, int thirdPawn, sf::Color pawnColor) {
    this->playerBase.pawnsVec[firstPawn].setFillColor(pawnColor);
    this->playerBase.pawnsVec[secondPawn].setFillColor(pawnColor);
    this->playerBase.pawnsVec[thirdPawn].setFillColor(pawnColor);
}

/**
 * @brief Set the radiuses for a player.
 *
 * @param p Player for whom to set the radiuses.
 * @param x Index of the pawn.
 * @param radiusColor Color of the radius.
 */

void Game::setRadiusesForPlayer(Player& p, int x, sf::Color radiusColor) {
    p.dupeRadius.setPosition({playerBase.pawnsVec[x].getPosition().x - 35, playerBase.pawnsVec[x].getPosition().y - 35});
    p.moveRadius.setPosition({playerBase.pawnsVec[x].getPosition().x - 85, playerBase.pawnsVec[x].getPosition().y - 85});
    p.captureRadius.setPosition({playerBase.pawnsVec[x].getPosition().x - 65, playerBase.pawnsVec[x].getPosition().y - 65});
    p.botMoveRadius.setPosition({playerBase.pawnsVec[x].getPosition().x - 65, playerBase.pawnsVec[x].getPosition().y - 65});
    p.botMoveRadius.setOutlineColor(radiusColor);
    p.dupeRadius.setOutlineColor(radiusColor);
    p.moveRadius.setOutlineColor(radiusColor);
}

/**
 * @brief Update the mouse position.
 */

void Game::updateMousePos() {
    this->mousePosWindow = {sf::Mouse::getPosition(*this->gameWindow).x, sf::Mouse::getPosition(*this->gameWindow).y};
    this->mousePosView = this->gameWindow->mapPixelToCoords(this->mousePosWindow);
}

/**
 * @brief Update the game fields.
 */

void Game::updateFields() {
    //endgame
    for (int i = 0; i < playerBase.pawnsVec.size(); i++) {
        if (playerBase.pawnsVec[i].getFillColor() == sf::Color::Transparent) {
            this->countTransparentPawns++;
        }
    }
    if (this->countTransparentPawns == 0) {
        this->endGame = true;
    }
    this->countTransparentPawns = 0;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (this->mouseHeld == false) {
            this->mouseHeld = true;

        if (player1.myTurn) {

            for (int i = 0; i < this->playerBase.pawnsVec.size(); i++) {
                //Set dupe and move radius position for player1
                if (playerBase.pawnsVec[i].getGlobalBounds().contains(this->mousePosView) &&
                    playerBase.pawnsVec[i].getFillColor() == sf::Color::White) {
                    this->setRadiusesForPlayer(player1, i, sf::Color::Red);
                    this->bodyPos = playerBase.pawnsVec[i].getPosition();
                } else
                    //Duplicate for player1
                if (player1.dupeRadius.getOutlineColor() != sf::Color::Transparent && player1.dupeRadius.getGlobalBounds().contains(this->mousePosView) && playerBase.pawnsVec[i].getGlobalBounds().contains(this->mousePosView) && playerBase.pawnsVec[i].getFillColor() == sf::Color::Transparent && playerBase.pawnsVec[i].getPosition() != bodyPos) {
                    this->playerBase.pawnsVec[i].setFillColor(sf::Color::White);
                    this->setRadiusesForPlayer(player1, i, sf::Color::Transparent);
                    this->boop.play();
                    this->countWhitePawns++;
                    //Capture enemy pawns
                    for (int c = 0; c < playerBase.pawnsVec.size(); ++c) {
                        sf::Vector2f cPos = {playerBase.pawnsVec[c].getPosition().x + 15, playerBase.pawnsVec[c].getPosition().y + 15};
                        if (player1.dupeRadius.getGlobalBounds().contains(cPos) && playerBase.pawnsVec[c].getFillColor() == sf::Color::Black) {
                            playerBase.pawnsVec[c].setFillColor(sf::Color::White);
                            this->countWhitePawns++;
                            this->countBlackPawns--;
                            this->captured = true;
                        }
                    }
                    player2.myTurn = true;
                    player1.myTurn = false;
                } else
                    //Move for player1
                if (player1.moveRadius.getOutlineColor() != sf::Color::Transparent && player1.moveRadius.getGlobalBounds().contains(this->mousePosView) && !(playerBase.dupeRadius.getGlobalBounds().contains(this->mousePosView)) && playerBase.pawnsVec[i].getGlobalBounds().contains(this->mousePosView) && playerBase.pawnsVec[i].getFillColor() == sf::Color::Transparent) {
                    playerBase.pawnsVec[i].setFillColor(sf::Color::White);
                    this->setRadiusesForPlayer(player1, i, sf::Color::Transparent);
                    this->boop.play();
                    //Recolor last used pawn
                    for (int j = 0; j < playerBase.pawnsVec.size(); ++j) {
                        if (this->bodyPos == playerBase.pawnsVec[j].getPosition()) {
                            playerBase.pawnsVec[j].setFillColor(sf::Color::Transparent);
                        }
                    }
                    //Capture enemy pawns
                    for (int c = 0; c < playerBase.pawnsVec.size(); ++c) {
                        sf::Vector2f cPos = {playerBase.pawnsVec[c].getPosition().x + 15, playerBase.pawnsVec[c].getPosition().y + 15};
                        if (player1.dupeRadius.getGlobalBounds().contains(cPos) && playerBase.pawnsVec[c].getFillColor() == sf::Color::Black) {
                            playerBase.pawnsVec[c].setFillColor(sf::Color::White);
                            this->countWhitePawns++;
                            this->countBlackPawns--;
                        }
                    }
                    player2.myTurn = true;
                    player1.myTurn = false;
                }
            }
        }

        } else if (player2.myTurn) {

            for (int i = 0; i < this->playerBase.pawnsVec.size(); i++) {
                //Set dupe and move radius position for player2
                if (playerBase.pawnsVec[i].getGlobalBounds().contains(this->mousePosView) && playerBase.pawnsVec[i].getFillColor() == sf::Color::Black) {
                    this->setRadiusesForPlayer(player2, i, sf::Color::Blue);
                    bodyPos = playerBase.pawnsVec[i].getPosition();
                } else
                //Duplicate for player2
                if (player2.dupeRadius.getOutlineColor() != sf::Color::Transparent && player2.dupeRadius.getGlobalBounds().contains(this->mousePosView) && playerBase.pawnsVec[i].getGlobalBounds().contains(this->mousePosView) && playerBase.pawnsVec[i].getFillColor() == sf::Color::Transparent && playerBase.pawnsVec[i].getPosition() != bodyPos) {
                    playerBase.pawnsVec[i].setFillColor(sf::Color::Black);
                    this->setRadiusesForPlayer(player2, i, sf::Color::Transparent);
                    this->boop.play();
                    this->countBlackPawns++;
                    for (int c = 0; c < playerBase.pawnsVec.size(); ++c) {
                        sf::Vector2f cPos = {playerBase.pawnsVec[c].getPosition().x + 15, playerBase.pawnsVec[c].getPosition().y + 15};
                        if (player2.dupeRadius.getGlobalBounds().contains(cPos) && playerBase.pawnsVec[c].getFillColor() == sf::Color::White) {
                            playerBase.pawnsVec[c].setFillColor(sf::Color::Black);
                            this->countBlackPawns++;
                            this->countWhitePawns--;
                        }
                    }
                    player1.myTurn = true;
                    player2.myTurn = false;
                } else
                //Move for player2
                if (player2.moveRadius.getOutlineColor() != sf::Color::Transparent && player2.moveRadius.getGlobalBounds().contains(this->mousePosView) && !(playerBase.dupeRadius.getGlobalBounds().contains(this->mousePosView)) && playerBase.pawnsVec[i].getGlobalBounds().contains(this->mousePosView) && playerBase.pawnsVec[i].getFillColor() == sf::Color::Transparent && playerBase.pawnsVec[i].getPosition() != bodyPos) {
                    playerBase.pawnsVec[i].setFillColor(sf::Color::Black);
                    this->setRadiusesForPlayer(player2, i, sf::Color::Transparent);
                    this->boop.play();
                    //Recolor last used pawn
                    for (int j = 0; j < playerBase.pawnsVec.size(); ++j) {
                        if (this->bodyPos == playerBase.pawnsVec[j].getPosition()) {
                            playerBase.pawnsVec[j].setFillColor(sf::Color::Transparent);
                        }
                    }
                    for (int c = 0; c < playerBase.pawnsVec.size(); ++c) {
                        sf::Vector2f cPos = {playerBase.pawnsVec[c].getPosition().x + 15, playerBase.pawnsVec[c].getPosition().y + 15};
                        if (player2.dupeRadius.getGlobalBounds().contains(cPos) && playerBase.pawnsVec[c].getFillColor() == sf::Color::White) {
                            playerBase.pawnsVec[c].setFillColor(sf::Color::Black);
                            this->countBlackPawns++;
                            this->countWhitePawns--;
                        }
                    }
                    player1.myTurn = true;
                    player2.myTurn = false;
                }
            }

    }


    } else {
        this->mouseHeld = false;
    }
}

/**
 * @brief Update the game fields for the bot.
 */

void Game::updateFieldsBot() {
    //endgame
    for (int i = 0; i < playerBase.pawnsVec.size(); i++) {
        if (playerBase.pawnsVec[i].getFillColor() == sf::Color::Transparent) {
            this->countTransparentPawns++;
        }
    }
    if (this->countTransparentPawns == 0) {
        this->endGame = true;
    }
    this->countTransparentPawns = 0;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (this->mouseHeld == false) {
            this->mouseHeld = true;

            if (player1.myTurn) {

                for (int i = 0; i < this->playerBase.pawnsVec.size(); i++) {
                    //Set dupe and move radius position for player1
                    if (playerBase.pawnsVec[i].getGlobalBounds().contains(this->mousePosView) &&
                        playerBase.pawnsVec[i].getFillColor() == sf::Color::White) {
                        this->setRadiusesForPlayer(player1, i, sf::Color::Red);
                        this->bodyPos = playerBase.pawnsVec[i].getPosition();
                    } else
                        //Duplicate for player1
                    if (player1.dupeRadius.getOutlineColor() != sf::Color::Transparent && player1.dupeRadius.getGlobalBounds().contains(this->mousePosView) && playerBase.pawnsVec[i].getGlobalBounds().contains(this->mousePosView) && playerBase.pawnsVec[i].getFillColor() == sf::Color::Transparent && playerBase.pawnsVec[i].getPosition() != bodyPos) {
                        this->playerBase.pawnsVec[i].setFillColor(sf::Color::White);
                        this->setRadiusesForPlayer(player1, i, sf::Color::Transparent);
                        this->boop.play();
                        this->countWhitePawns++;
                        //Capture enemy pawns
                        for (int c = 0; c < playerBase.pawnsVec.size(); ++c) {
                            sf::Vector2f cPos = {playerBase.pawnsVec[c].getPosition().x + 15, playerBase.pawnsVec[c].getPosition().y + 15};
                            if (player1.dupeRadius.getGlobalBounds().contains(cPos) && playerBase.pawnsVec[c].getFillColor() == sf::Color::Black) {
                                playerBase.pawnsVec[c].setFillColor(sf::Color::White);
                                this->countWhitePawns++;
                                this->countBlackPawns--;
                                this->captured = true;
                            }
                        }
                        player2.myTurn = true;
                        player1.myTurn = false;
                    } else
                        //Move for player1
                    if (player1.moveRadius.getOutlineColor() != sf::Color::Transparent && player1.moveRadius.getGlobalBounds().contains(this->mousePosView) && !(playerBase.dupeRadius.getGlobalBounds().contains(this->mousePosView)) && playerBase.pawnsVec[i].getGlobalBounds().contains(this->mousePosView) && playerBase.pawnsVec[i].getFillColor() == sf::Color::Transparent) {
                        playerBase.pawnsVec[i].setFillColor(sf::Color::White);
                        this->setRadiusesForPlayer(player1, i, sf::Color::Transparent);
                        this->boop.play();
                        //Recolor last used pawn
                        for (int j = 0; j < playerBase.pawnsVec.size(); ++j) {
                            if (this->bodyPos == playerBase.pawnsVec[j].getPosition()) {
                                playerBase.pawnsVec[j].setFillColor(sf::Color::Transparent);
                            }
                        }
                        //Capture enemy pawns
                        for (int c = 0; c < playerBase.pawnsVec.size(); ++c) {
                            sf::Vector2f cPos = {playerBase.pawnsVec[c].getPosition().x + 15, playerBase.pawnsVec[c].getPosition().y + 15};
                            if (player1.dupeRadius.getGlobalBounds().contains(cPos) && playerBase.pawnsVec[c].getFillColor() == sf::Color::Black) {
                                playerBase.pawnsVec[c].setFillColor(sf::Color::White);
                                this->countWhitePawns++;
                                this->countBlackPawns--;
                            }
                        }
                        player2.myTurn = true;
                        player1.myTurn = false;
                    }
                }
            }

        } else if (player2.myTurn) {

            this->moved = false;


            //iterate through pawns
            for (int i = 0; i < playerBase.pawnsVec.size(); ++i) {

                int val = 0;
                bool taken = false;

                if (playerBase.pawnsVec[i].getFillColor() != sf::Color::Transparent){
                    taken = true;
                }

                if (!taken){

                    player2.captureRadius.setPosition({playerBase.pawnsVec[i].getPosition().x - 65, playerBase.pawnsVec[i].getPosition().y - 65});

                    for (int j = 0; j < playerBase.pawnsVec.size(); ++j) {
                        if (player2.captureRadius.getGlobalBounds().contains({playerBase.pawnsVec[j].getPosition().x + 15, playerBase.pawnsVec[j].getPosition().y + 15}) && playerBase.pawnsVec[j].getFillColor() == sf::Color::White) {
                            val++;

                        }
                    }
                }

                this->pawnValueVec.push_back(val);
            }

            int maxMoveVal = 0;
            int maxMoveIndex = 0;


            for (int i = 0; i < this->playerBase.pawnsVec.size(); i++) {

                int val = 0;

                if (playerBase.pawnsVec[i].getFillColor() == sf::Color::Black) {

                    setRadiusesForPlayer(player2, i, sf::Color::Transparent);

                    for (int c = 0; c < playerBase.pawnsVec.size(); ++c) {

                        sf::Vector2f pawnPos = {playerBase.pawnsVec[c].getPosition().x + 15, playerBase.pawnsVec[c].getPosition().y + 15};

                        if (player2.moveRadius.getGlobalBounds().contains(pawnPos) && playerBase.pawnsVec[c].getFillColor() == sf::Color::Transparent) {
                            val = pawnValueVec[c];
                            if (val >= maxMoveVal) {
                                maxMoveVal = val;
                                maxMoveIndex = c;

                            }
                        }
                    }
                }
            }

            for (int i = 0; i < playerBase.pawnsVec.size(); ++i) {

                setRadiusesForPlayer(player2, i , sf::Color::Transparent);

                if (playerBase.pawnsVec[i].getFillColor() == sf::Color::Black && player2.captureRadius.getGlobalBounds().contains({playerBase.pawnsVec[maxMoveIndex].getPosition().x + 15, playerBase.pawnsVec[maxMoveIndex].getPosition().y + 15})
                    && playerBase.pawnsVec[maxMoveIndex].getFillColor() == sf::Color::Transparent && playerBase.pawnsVec[maxMoveIndex].getFillColor() != sf::Color::White) {

                    playerBase.pawnsVec[maxMoveIndex].setFillColor(sf::Color::Black);

                    this->countBlackPawns++;

                    setRadiusesForPlayer(player2, maxMoveIndex, sf::Color::Transparent);

                    for (int c = 0; c < playerBase.pawnsVec.size(); ++c) {
                        sf::Vector2f cPos1 = {playerBase.pawnsVec[c].getPosition().x + 15, playerBase.pawnsVec[c].getPosition().y + 15};
                        if (player2.dupeRadius.getGlobalBounds().contains(cPos1) && playerBase.pawnsVec[c].getFillColor() == sf::Color::White) {
                            playerBase.pawnsVec[c].setFillColor(sf::Color::Black);

                            this->countBlackPawns++;
                            this->countWhitePawns--;
                        }
                    }
                    this->moved = true;
                    player1.myTurn = true;
                    player2.myTurn = false;

                } else if (playerBase.pawnsVec[i].getFillColor() == sf::Color::Black && !player2.captureRadius.getGlobalBounds().contains({playerBase.pawnsVec[maxMoveIndex].getPosition().x + 15, playerBase.pawnsVec[maxMoveIndex].getPosition().y + 15})
                           && player2.moveRadius.getGlobalBounds().contains({playerBase.pawnsVec[maxMoveIndex].getPosition().x + 15, playerBase.pawnsVec[maxMoveIndex].getPosition().y + 15}) && playerBase.pawnsVec[maxMoveIndex].getFillColor() == sf::Color::Transparent && playerBase.pawnsVec[maxMoveIndex].getFillColor() != sf::Color::White) {

                    playerBase.pawnsVec[maxMoveIndex].setFillColor(sf::Color::Black);
                    playerBase.pawnsVec[i].setFillColor(sf::Color::Transparent);
                    setRadiusesForPlayer(player2, maxMoveIndex, sf::Color::Transparent);

                    for (int c = 0; c < playerBase.pawnsVec.size(); ++c) {
                        sf::Vector2f cPos1 = {playerBase.pawnsVec[c].getPosition().x + 15, playerBase.pawnsVec[c].getPosition().y + 15};
                        if (player2.dupeRadius.getGlobalBounds().contains(cPos1) && playerBase.pawnsVec[c].getFillColor() == sf::Color::White) {
                            playerBase.pawnsVec[c].setFillColor(sf::Color::Black);

                            this->countBlackPawns++;
                            this->countWhitePawns--;
                        }
                    }
                    this->moved = true;
                    player1.myTurn = true;
                    player2.myTurn = false;
                }
            }
            if (!moved)
                this->endGame = true;
        }


    } else {
        this->mouseHeld = false;
    }
}
/**
 * @brief Updates the game state.
 */
void Game::update() {
    this->pollEvents();
    this->updateMousePos();

    if (!this->pvpChosen && !this->pveChosen) {
        this->updateStartingWindow();
        this->updateStartText();
    } else if (!this->endGame && this->countBlackPawns != 0 && this->countWhitePawns != 0) {
        if (this->pvpChosen) {
            this->updateFields();
        } else if (this->pveChosen) {
            this->updateFieldsBot();
        }
        this->updateText();
    } else {
        this->updateGameOverText();
    }
}

/**
 * @brief Renders the game fields.
 */
void Game::renderFields() {
    for (auto e : this->fieldsVec) {
        this->gameWindow->draw(e);
    }
}

/**
 * @brief Renders the game body.
 */
void Game::renderBody() {
    //draw pawns
    for (auto e : this->playerBase.pawnsVec) {
        this->gameWindow->draw(e);
    }

    //draw radius in which you can move
    this->gameWindow->draw(this->player1.moveRadius);
    this->gameWindow->draw(this->player2.moveRadius);
    this->gameWindow->draw(this->player1.captureRadius);

    //draw radius in which body will duplicate
    this->gameWindow->draw(this->player1.dupeRadius);
    this->gameWindow->draw(this->player2.dupeRadius);
}

/**
 * @brief Renders the game.
 */
void Game::render() {
    this->gameWindow->clear(sf::Color(135, 85, 46));
    if (!this->pvpChosen && !this->pveChosen) {
        this->renderButtons();
        this->renderStartText();
    } else if (!this->endGame && this->countBlackPawns != 0 && this->countWhitePawns != 0) {
        this->renderFields();
        this->renderBody();
        this->renderText();
    } else {
        this->renderGameOverText();
    }
    this->gameWindow->display();
}

/**
 * @brief Initializes the buttons.
 */
void Game::initButtons() {
    this->button.setSize({300, 60});
    this->button.setFillColor(sf::Color(189, 134, 68));
    this->button.setOutlineColor(sf::Color(87, 54, 16));
    this->button.setOutlineThickness(3);
    this->button.setPosition({150, 300});

    this->button1.setSize({300, 60});
    this->button1.setFillColor(sf::Color(189, 134, 68));
    this->button1.setOutlineColor(sf::Color(87, 54, 16));
    this->button1.setOutlineThickness(3);
    this->button1.setPosition({150, 380});
}

/**
 * @brief Initializes the variables.
 */
void Game::initVariables() {
    this->gameWindow = nullptr;
    this->ev;

    //Game logic
    this->mouseHeld = false;
    this->endGame = false;
}

/**
 * @brief Initializes the game window.
 */
void Game::initWindow() {
    this->videoMode.size = {600, 700};
    this->gameWindow= new sf::RenderWindow(this->videoMode, "HEXXAGON", sf::Style::Close | sf::Style::Titlebar);
    this->gameWindow->setFramerateLimit(120);
}

/**
 * @brief Initializes the game fields.
 */
void Game::initFields() {
    this->field.setRadius(25);
    this->field.rotate(sf::degrees(30));
    this->field.setPointCount(6);
    this->field.setFillColor(sf::Color::White);
    this->field.setOutlineColor(sf::Color(87, 54, 16));
    this->field.setOutlineThickness(3);
}

/**
 * @brief Initializes the fonts.
 */
void Game::initFonts() {
    if (!this->font.loadFromFile("Fonts/monogram.ttf")) {
        std::cout << "ERROR: COULDN'T LOAD FONT" << '\n';
    }
}

/**
 * @brief Updates the text displayed in the game.
 */
void Game::updateText() {
    this->turnText.setCharacterSize(50);
    if (player1.myTurn) {
        this->turnText.setPosition({20, 5});
        this->turnText.setString("White player's turn:");
        this->turnText.setFillColor(sf::Color::White);
    } else {
        this->turnText.setString("Black player's turn:");
        this->turnText.setFillColor(sf::Color::Black);
    }

    std::stringstream ss;
    ss << "White player's points: " << this->countWhitePawns << "        Black player's points: " << this->countBlackPawns;
    this->pointText.setPosition({20, 630});
    this->pointText.setString(ss.str());
    this->pointText.setCharacterSize(27);
    this->pointText.setFillColor(sf::Color::Black);
}

/**
 * @brief Renders the text in the game.
 */
void Game::renderText() {
    this->gameWindow->draw(this->turnText);
    this->gameWindow->draw(this->pointText);
}

/**
 * @brief Renders the start text.
 */
void Game::renderStartText() {
    this->gameWindow->draw(startText);
    this->gameWindow->draw(startText1);
    this->gameWindow->draw(startText2);
}

/**
 * @brief Updates the start text.
 */
void Game::updateStartText() {
    this->startText.setString("Hexxagon");
    this->startText.setCharacterSize(100);
    this->startText.setPosition({150, 100});
    this->startText.setFillColor(sf::Color::Black);

    this->startText1.setString("Player vs Player");
    this->startText1.setFillColor(sf::Color::Black);
    this->startText1.setCharacterSize(30);
    this->startText1.setPosition({212, 307});

    this->startText2.setString("Player vs Computer");
    this->startText2.setFillColor(sf::Color::Black);
    this->startText2.setCharacterSize(30);
    this->startText2.setPosition({206, 387});
}

/**
 * @brief Updates the starting window.
 */
void Game::updateStartingWindow() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->button.getGlobalBounds().contains(this->mousePosView)) {
        this->pvpChosen = true;
    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->button1.getGlobalBounds().contains(this->mousePosView)) {
        this->pveChosen = true;
    }
}

/**
 * @brief Renders the buttons.
 */
void Game::renderButtons() {
    this->gameWindow->draw(this->button);
    this->gameWindow->draw(this->button1);
}

/**
 * @brief Initializes the boop sound.
 */
void Game::initBoop() {
    if (!this->soundBuffer.loadFromFile("Music\\realBoop.wav")) {
        std::cout << "ERROR: COULDN'T LOAD SOUND" << '\n';
    }
    this->boop.setBuffer(soundBuffer);
}

/**
 * @brief Updates the game over text.
 */
void Game::updateGameOverText() {
    this->gameOverText.setString("Game Over");
    this->gameOverText.setFillColor(sf::Color::Black);
    this->gameOverText.setCharacterSize(100);
    this->gameOverText.setPosition({140, 150});

    std::string winner;

    if (countWhitePawns > countBlackPawns) {
        winner = "White player wins!!";
        this->gameOverText1.setFillColor(sf::Color::White);
    } else if (countWhitePawns < countBlackPawns) {
        winner = "Black player wins!!";
        this->gameOverText1.setFillColor(sf::Color::Black);
    } else {
        winner = "Tie??";
        this->gameOverText1.setFillColor(sf::Color::Red);
    }

    std::stringstream ss;
    ss << "White player's points: " << this->countWhitePawns << "    " << "Black player's points: " << this->countBlackPawns << '\n' << '\n' << "                 " << winner;
    this->gameOverText1.setString(ss.str());
    this->gameOverText1.setCharacterSize(27);
    this->gameOverText1.setPosition({40, 280});
}

/**
 * @brief Renders the game over text.
 */
void Game::renderGameOverText() {
    this->gameWindow->draw(gameOverText);
    this->gameWindow->draw(gameOverText1);
}








