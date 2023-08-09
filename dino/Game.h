#pragma once
#include <SFML/Graphics.hpp>


//game engine
class Game
{
public:
	Game();
	void update(sf::RenderWindow& window);
	void startGame();
	bool isGameStarted() const;

	float x;
	float y;
	float velocityX;
	float velocityY;
	float accX;
	float accY;
	float gravity;

	bool gameStarted;
};
