//
// Created by Tiffanie Lim on 6/10/24.
//

#include "TetrisApp.h"

void TetrisApp::run()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(600, 760), "Tetris", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(30);
    sf::Event event;

    te::Game game(window.getSize().x, window.getSize().y);

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            game.OnEvent(event, window);
        }

        game.OnUpdate();
        window.clear();
        game.Render(window);
        window.display();
    }
}