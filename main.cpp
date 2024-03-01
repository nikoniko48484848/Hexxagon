#include "Game.h"

/**
 * @brief Main function for the game.
 *
 * @return 0 upon successful execution.
 */
int main() {
    // Init game
    Game game;
    game.createBoard();
    game.createPawns();

    sf::Music music;
    if (!music.openFromFile("Music\\sans.ogg")) {
        std::cout << "Error, music file couldn't open" << '\n';
    }

    music.play();
    music.setLoop(true);

    // Game loop
    while (game.running()) {
        // Update
        game.update();

        // Render
        game.render();
    }

    music.stop();

    return 0;
}