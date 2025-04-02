//
// Created by Tiffanie Lim on 6/5/24.
//

#ifndef CS3A_TETRIS_GAME_H
#define CS3A_TETRIS_GAME_H
#include <SFML/Graphics.hpp>
#include "Field.h"
#include "SplashScreen.h"
#include "TetrisApp.h"

namespace te
{
    class Game
    {
    public:
        Game(int w, int h);
        void OnEvent(sf::Event e, sf::RenderWindow& window);
        void OnUpdate();
        void Render(sf::RenderTarget& wnd);

    private:
        int windowWidth;
        int windowHeight;
        sf::RenderWindow window;

        Field field;
        sf::Clock fieldClock;
        float updateSpeed = 0.20f;
        float timePassed = 0.0f;

        enum class State { Splash, Playing };
        State currentState;

        sf::Texture splashTexture;
        sf::Sprite splashSprite;
        sf::Font font;
        sf::Text nameText;
        sf::RectangleShape startButton;
        sf::Text startButtonText;
    };
}

#endif //CS3A_TETRIS_GAME_H
