#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Player.h"
#include "Obstacles.h"


void drawSun(sf::RenderWindow& window) {
    sf::CircleShape sun(30);
    sun.setFillColor(sf::Color::Yellow);
    sun.setPosition(500, 50);
    window.draw(sun);
  
}

int main()
{


    sf::RenderWindow window(sf::VideoMode(600, 400), "Dino Game");
    sf::Event ev;
    sf::View view(sf::FloatRect(0.f, 0.f, 600, 400));
    sf::RectangleShape floor;
    sf::Texture floorTexture;
    if (!floorTexture.loadFromFile("Assets/desert.png")) {
        std::cerr << "Error: Floor texture loading failed." << std::endl;
    }

    floor.setTexture(&floorTexture);
    floor.setTextureRect(sf::IntRect(0, 0, window.getSize().x, floorTexture.getSize().y));
    floor.setSize(sf::Vector2f(window.getSize().x, 30.0f));
    floor.setPosition(0, window.getSize().y - floor.getSize().y);

    sf::Color topColor(255, 165, 0); 
    sf::Color bottomColor(255, 69, 0); 

    sf::VertexArray background(sf::Quads, 4);
    background[0].color = topColor;
    background[1].color = topColor;
    background[2].color = bottomColor;
    background[3].color = bottomColor;

    background[0].position = sf::Vector2f(0, 0);
    background[1].position = sf::Vector2f(window.getSize().x, 0);
    background[2].position = sf::Vector2f(window.getSize().x, window.getSize().y);
    background[3].position = sf::Vector2f(0, window.getSize().y);


    sf::Texture rectangleTexture;
    if (!rectangleTexture.loadFromFile("Assets/dino.png")) {
        std::cerr << "Error: Image loading failed." << std::endl;
    }
    window.setFramerateLimit(60);
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(80, 80));
    rectangle.setTexture(&rectangleTexture);
    rectangle.setPosition(10, window.getSize().y - floor.getSize().y - rectangle.getSize().y);

    Player player;
    const int maxObstacles = 5;
    Obstacles obstacles[maxObstacles];

    int score = 0;

    bool gameStarted = false;
    bool gameOver = false;
    float jumpHeight = 200.0f;
    float jumpSpeedY = -25.0f;
    bool canJump = false;

    sf::Font font;
    if (!font.loadFromFile("Assets/joystix monospace.otf"))
    {
        std::cerr << "Error: Font loading failed." << std::endl;
    }

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(32);
    scoreText.setPosition(30, 20);
    scoreText.setFillColor(sf::Color::Black);


    while (window.isOpen() && !gameOver)
    {
        while (window.pollEvent(ev))
        {
            switch (ev.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (ev.key.code == sf::Keyboard::Escape)
                    window.close();

                else if (ev.key.code == sf::Keyboard::Space && canJump)
                {
                    player.jump();
                    player.update(window);
                    player.setVelocityY(jumpSpeedY);
                    player.startGame();

                    gameStarted = true;
                    canJump = true;
                }
                break;
            case sf::Event::KeyReleased:
                if (ev.key.code == sf::Keyboard::Space) {
                    canJump = false;
                }
                break;
            }
        }
        if (player.getY() >= window.getSize().y - floor.getSize().y - jumpHeight)
        {
            canJump = true;
        }
        float floorHeight = window.getSize().y - floor.getSize().y - jumpHeight;

        float moveAmount = 0.25f;
        float backgroundSpeed = 5.f;


        player.update(window);
        player.updatePosition(1.0f / 60.0f);

        if (player.getX() + player.getWidth() >= view.getCenter().x + view.getSize().x / 2)
        {
            float playerVelocityX = player.getVelocityX();
            view.move(-moveAmount * backgroundSpeed, 0.f);
            floor.move(-moveAmount * backgroundSpeed, 0.f);

        }

        if (!gameOver)
        {
            for (int i = 0; i < maxObstacles; i++)
            {
                if (!obstacles[i].isActive())
                {
                    obstacles[i].startSpawn(floor);
                }
                else
                {
                    obstacles[i].updatePosition(1.0f / 60.0f);
                    obstacles[i].checkCollisionWithPlayer(player);

                    if (rectangle.getGlobalBounds().intersects(obstacles[i].getShape().getGlobalBounds()))
                    {
                        std::cout << "GAME OVER! TRY AGAIN..." << std::endl;
                        std::cout << "Your Score: " << score << std::endl;
                        gameOver = true;
                        break;
                    }
                }
                if (obstacles[i].isActive() && player.getX() > obstacles[i].getX() + obstacles[i].getWidth())
                {
                    score++;
                }
            }
        }
        scoreText.setString("Score: " + std::to_string(score));
        player.update(window);

        rectangle.setPosition(player.getX(), player.getY());

        window.setView(view);
        window.clear();
        window.draw(background);
        window.draw(floor);
        for (int i = 0; i < maxObstacles; i++)
        {
            obstacles[i].draw(window);
        }
        drawSun(window);

        window.draw(scoreText);
        window.draw(rectangle);
        window.display();
    }


    return 0;
}