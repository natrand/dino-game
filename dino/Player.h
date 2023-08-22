#pragma once
#include <SFML/Graphics.hpp>


//game engine
class Player
{
public:
	Player();
	void update(sf::RenderWindow& window);
	void jump();
	bool isJumping() const;
	void setVelocityX(float newVelocityX);
	void setVelocityY(float newVelocityY);
	float getVelocityX() const;
	float getVelocityY() const;
	float getX() const;
	float getY() const;
	float getWidth() const;
	bool isGameStarted() const;
	void startGame(); // Add this function
	sf::RectangleShape& getRectangle();
	void updatePosition(float deltaTime);

private:
	float x;
	float y;
	float velocityX;
	float velocityY;
	float accX;
	float accY;
	float gravity;
	bool jumping;
	sf::RectangleShape rectangle;
	bool gameStarted;
};