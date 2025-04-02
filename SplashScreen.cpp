//
// Created by Tiffanie Lim on 6/9/24.
//

#include "SplashScreen.h"

SplashScreen::SplashScreen(float width, float height) {
    if (!splashTexture.loadFromFile("Images/TetrisImage.png")) {

    }
    splashSprite.setTexture(splashTexture);

    if (!font.loadFromFile("Fonts/Minecraft.ttf")) {

    }

    title.setFont(font);
    title.setString("Tiffanie Lim - Spr24_CS003A_37045");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition(sf::Vector2f(width / 2 - title.getLocalBounds().width / 2, height / 4));

    startButton.setFont(font);
    startButton.setString("Press Enter to Start");
    startButton.setCharacterSize(30);
    startButton.setFillColor(sf::Color::White);
    startButton.setPosition(sf::Vector2f(width / 2 - startButton.getLocalBounds().width / 2, height / 2));
}

void SplashScreen::Render(sf::RenderWindow &window) {
    window.draw(splashSprite);
    window.draw(title);
    window.draw(startButton);
}

bool SplashScreen::HandleEvent(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        return true; // Signal to transition to the game state
    }
    return false;
}
