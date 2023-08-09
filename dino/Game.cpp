#include "Game.h"


Game::Game() : x(0), y(0), velocityX(0), velocityY(0), accX(0), accY(0), gravity(1), gameStarted(false) {}


void Game::update(sf::RenderWindow& window) {
    if (y < 500) {
        velocityY += gravity;
    }
    else if (y > 500) {
        y = 500;
    }
    velocityX += accX;
    velocityY += accY;

    x += velocityX;
    y += velocityY;

}

void Game::startGame() {
    gameStarted = true;
}

bool Game::isGameStarted() const {
    return gameStarted;
}
