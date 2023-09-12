
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Player.h"
#include "Obstacles.h"



int main()
{


    //window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dino Game");
    sf::Event ev;
    sf::View view(sf::FloatRect(0.f, 0.f, 800.f, 600.f)); //control view within the window

    sf::RectangleShape floor;
    floor.setSize(sf::Vector2f(window.getSize().x, 40)); // Set the size of the floor
    floor.setFillColor(sf::Color::Green); // Set the color of the floor
    floor.setPosition(0, window.getSize().y - floor.getSize().y); // Position the floor at the bottom of the window


    window.setFramerateLimit(60);

    //setting up square

    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(50, 50));
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setPosition(0, window.getSize().y - rectangle.getSize().y);

   
    Player player;
    const int maxObstacles = 5;
    Obstacles obstacles[maxObstacles];

    //bool isJumping = false;
    bool gameStarted = false;
    bool gameOver = false;
    float jumpHeight = 200.0f;  // jump height 
    float jumpSpeedY = -20.0f;  // Vertical jump speed
    bool canJump = false;        // Track if the player can jump
    

    //text
    /*
    sf::Text gameOverText; // Create a text object
    gameOverText.setFont(sf::Font()); // Set the font
    gameOverText.setCharacterSize(48); // Set the character size
    gameOverText.setString("Game Over"); // Set the text content
    gameOverText.setPosition(300, 200); // Set the position
    gameOverText.setFillColor(sf::Color::Red); // Set the text color
    */

    //game loop
    while (window.isOpen() && !gameOver)
    {
        //events
        while (window.pollEvent(ev))
        {
            switch (ev.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (ev.key.code == sf::Keyboard::Escape) //to exit we have to press esc button
                    window.close();

                //jumping
                else if (ev.key.code == sf::Keyboard::Space && canJump)
                {
                    player.jump();
                    player.update(window);
                    player.setVelocityY(jumpSpeedY);
                    player.startGame();

                    //isJumping = true;
                    gameStarted = true;
                    canJump = true;  // Prevent further jumping until player lands
                }
                break;
            case sf::Event::KeyReleased:
                if (ev.key.code == sf::Keyboard::Space) {
                    canJump = false;  // Allow jumping when the space key is released

                    
                }
                break;
            }


        }

        if (player.getY() >= window.getSize().y - floor.getSize().y - jumpHeight)
        {
            canJump = true;  
        }

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

        // Check collision between the rectangle and obstacles
        if (!gameOver)
        {
            for (int i = 0; i < maxObstacles; i++)
            {
                obstacles[i].update(1.0f / 60.0f, player.getVelocityX(), floor);
                if (obstacles[i].isActive() && rectangle.getGlobalBounds().intersects(obstacles[i].getShape().getGlobalBounds()))
                {
                    std::cout << "COLLISION!" << std::endl;
                    gameOver = true;
                    break;
                }
               
            }
        }

        player.update(window);

        rectangle.setPosition(player.getX(), player.getY());

        window.setView(view);
        window.clear(sf::Color::Black);

        

        for (int i = 0; i < maxObstacles; i++)
        {
            obstacles[i].draw(window);
        }
        /*
        if (gameOver)
        {
            window.draw(gameOverText);
        }*/
        window.draw(rectangle);
        window.draw(floor);
        window.display();
    }


    return 0;
}
