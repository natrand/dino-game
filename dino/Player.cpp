#include "Player.h"


Player::Player() : x(0), y(0), velocityX(0), velocityY(0), accX(0), accY(0), gravity(1), jumping(false), gameOver(false) {}

void Player::update(sf::RenderWindow& window) {
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
void Player::updatePosition(float deltaTime)
{
    x += velocityX * deltaTime; 
}

void Player::jump() {
        jumping = true;   
}

bool Player::isJumping() const
{
    return jumping;
}

float Player::getVelocityX() const {
    return velocityX;
}

float Player::getVelocityY() const {
    return velocityY;
}
void Player::setVelocityX(float newVelocityX)
{
    velocityX = newVelocityX;
}
void Player::setVelocityY(float newVelocityY)
{
    velocityY = newVelocityY;
}

float Player::getX() const
{
    return x;
}

float Player::getY() const
{
    return y;
}
void Player::startGame()
{
    gameStarted = true;
}

bool Player::isGameStarted() const
{
    return gameStarted;
}
float Player::getWidth() const
{
    
    return 50.0f;
}

sf::RectangleShape& Player::getRectangle() {
    return rectangle;
}
void Player::setGameOver(bool gameOverState)
{
    gameOver = gameOverState;
}

bool Player::isGameOver() const {
    return gameOver;
}
