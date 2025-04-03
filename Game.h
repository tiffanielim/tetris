//
// Created by Tiffanie Lim on 6/5/24.
//

///Controls the overall game loop, splash screen, and transition to the playing state
///Handles user input, block drop timing, rendering splash UI and game field

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
        Game(int w, int h); //constructor that sets up window size, splash screen, & font
        void OnEvent(sf::Event e, sf::RenderWindow& window); //handles events based on game state
        void OnUpdate(); //updates the game logic at a timed interval
        void Render(sf::RenderTarget& wnd); //renders both splash screen and playing field

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
