//
// Created by Tiffanie Lim on 6/5/24.
//
#include "Game.h"
#include "Settings.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

namespace te
{
    Game::Game(int w, int h) :
            field((h - BG_MARGIN * 2) / FIELD_HEIGHT),
            updateSpeed(NORMAL_SPEED), //initialize updateSpeed
            timePassed(0.f) //initialize timePassed
    {
        windowWidth = w;
        windowHeight = h;
        currentState = State::Splash;

        //load and set splash screen image
        if (!splashTexture.loadFromFile("Images/TetrisImage.png"))
        {
            std::cerr << "Failed to load splash image" << std::endl;
        }
        splashSprite.setTexture(splashTexture);
        splashSprite.setScale(0.45f, 0.45f);
        splashSprite.setPosition(windowWidth / 2 - splashSprite.getGlobalBounds().width / 2, 50);

        //load and set font
        if (!font.loadFromFile("Fonts/Minecraft.ttf"))
        {
            std::cerr << "Failed to load font" << std::endl;
        }

        //set name tag text on splash screen
        nameText.setFont(font);
        nameText.setString("Tiffanie Lim - Spr24_CS003A_37045");
        nameText.setCharacterSize(25);
        nameText.setFillColor(sf::Color::White);
        nameText.setPosition(windowWidth / 2 - nameText.getGlobalBounds().width / 2, windowHeight/2 + 300);

        //set up start button appearance and position
        startButton.setSize(sf::Vector2f(200, 50));
        startButton.setFillColor(sf::Color(255, 204, 229));
        startButton.setPosition(windowWidth / 2 - startButton.getSize().x / 2, 550);

        //set up "Start" button label
        startButtonText.setFont(font);
        startButtonText.setString("Start");
        startButtonText.setCharacterSize(30);
        startButtonText.setFillColor(sf::Color::Black);
        startButtonText.setPosition(startButton.getPosition().x + startButton.getSize().x / 2 - startButtonText.getGlobalBounds().width / 2,
                                    startButton.getPosition().y + startButton.getSize().y / 2 - startButtonText.getGlobalBounds().height / 2);
    }

    void Game::OnEvent(sf::Event e, sf::RenderWindow& window)
    {
        if (currentState == State::Splash)
        {
            if (e.type == sf::Event::MouseButtonPressed)
            {
                //mouse button pressed and the mouse button is within the bounds of the button
                sf::FloatRect startButtonBounds = startButton.getGlobalBounds();
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window); // set mouse position relative to a window

                //check if click is inside button area
                if (startButtonBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
                {
                    currentState = State::Playing;
                    timePassed = 0.f;
                    fieldClock.restart(); //reset drop timer
                }
            }
        }
        else if (currentState == State::Playing)
        {
            //handle soft drop speed toggle
            if (e.type == sf::Event::KeyPressed)
            {
                sf::Keyboard::Key kc = e.key.code;

                if (kc == sf::Keyboard::Down || kc == sf::Keyboard::S)
                    updateSpeed = NORMAL_SPEED / SPEED_UP_DIVIDER;
            }
            else if (e.type == sf::Event::KeyReleased)
            {
                sf::Keyboard::Key kc = e.key.code;

                if (kc == sf::Keyboard::Down || kc == sf::Keyboard::S)
                    updateSpeed = NORMAL_SPEED;
            }

            //pass movement/rotation keys to field
            field.OnEvent(e);
        }
    }

    void Game::OnUpdate()
    {
        if (currentState == State::Playing)
        {
            timePassed += fieldClock.restart().asSeconds(); //track time since last drop
            while (timePassed >= updateSpeed) //if enough time passed, update field logic
            {
                field.OnUpdate();
                timePassed -= updateSpeed;
            }
        }
    }

    void Game::Render(sf::RenderTarget& wnd)
    {
        if (currentState == State::Splash)
        {
            wnd.draw(splashSprite);
            wnd.draw(nameText);
            wnd.draw(startButton);
            wnd.draw(startButtonText);
        }
        else if (currentState == State::Playing)
        {
            sf::RectangleShape bg;
            bg.setFillColor(sf::Color(30, 30, 30));

            //draw background for upcoming queue area
            bg.setPosition(BG_MARGIN, BG_MARGIN);
            bg.setSize(sf::Vector2f(1.f / 3.f * (windowWidth - BG_MARGIN * 3), windowHeight - BG_MARGIN * 2));
            wnd.draw(bg);

            //draw upcoming block queue
            sf::Vector2f qOffset = bg.getPosition();
            std::queue<Block::Type> blocks = field.GetQueue();
            int queueTileSize = bg.getSize().x / 6.f; //width split into 6 (1 margin + 4 tiles + 1 margin)
            int vertSlots = (bg.getSize().y / queueTileSize) / 5;  //height divided into blocks (1 margin + 4 tiles)
            for (int i = 0; i <= std::min<int>(vertSlots, QUEUE_SIZE); i++)
            {
                Block::Type type = blocks.front();
                blocks.pop();

                //center non-I and non-O blocks
                float multiplier = 1.f;
                if (type != Block::Type::I && type != Block::Type::O)
                    multiplier = 0.5f;

                Block::Render(wnd, type, qOffset.x + queueTileSize * multiplier, qOffset.y + i * queueTileSize * 5, queueTileSize, 0);
            }

            //draw background behind actual tetris field
            bg.setPosition(20 + bg.getSize().x + BG_MARGIN, BG_MARGIN);
            bg.setSize(sf::Vector2f(2.f / 3.f * (windowWidth - BG_MARGIN * 3), windowHeight - BG_MARGIN * 2));
            wnd.draw(bg);

            //update field’s drawing position and render it
            field.SetPosition(bg.getPosition().x, bg.getPosition().y);
            field.Render(wnd);
        }
    }
}
