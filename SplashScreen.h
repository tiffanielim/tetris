//
// Created by Tiffanie Lim on 6/9/24.
//

///Manages the splash screen UI before the game starts
///Displays a title, an image, and a prompt to start
///Handles input to transition from splash to gameplau

#ifndef CS3A_TETRIS_SPLASHSCREEN_H
#define CS3A_TETRIS_SPLASHSCREEN_H
#include <SFML/Graphics.hpp>
#include <iostream>

class SplashScreen {
public:
    SplashScreen(float width, float height);
    void Render(sf::RenderWindow &window);
    bool HandleEvent(sf::Event &event); //returns true if Enter is pressed to start game

private:
    sf::Texture splashTexture; //background image
    sf::Sprite splashSprite;
    sf::Font font;
    sf::Text title;
    sf::Text startButton; //text prompt to press enter
};

#endif //CS3A_TETRIS_SPLASHSCREEN_H
