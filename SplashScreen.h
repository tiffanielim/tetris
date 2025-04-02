//
// Created by Tiffanie Lim on 6/9/24.
//

#ifndef CS3A_TETRIS_SPLASHSCREEN_H
#define CS3A_TETRIS_SPLASHSCREEN_H
#include <SFML/Graphics.hpp>

class SplashScreen {
public:
    SplashScreen(float width, float height);
    void Render(sf::RenderWindow &window);
    bool HandleEvent(sf::Event &event);

private:
    sf::Texture splashTexture;
    sf::Sprite splashSprite;
    sf::Font font;
    sf::Text title;
    sf::Text startButton;
};

#endif //CS3A_TETRIS_SPLASHSCREEN_H
