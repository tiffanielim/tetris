//
// Created by Tiffanie Lim on 6/3/24.
//

#ifndef CS3A_TETRIS_BLOCK_H
#define CS3A_TETRIS_BLOCK_H
#include <SFML/Graphics/RenderTarget.hpp>
#include <vector>

namespace te
{
    class Block
    {
    public:
        enum Type
        {
            I,
            O,
            T,
            S,
            Z,
            J,
            L,
            Count,
            None
        };

        static void Render(sf::RenderTarget& window, Type type, int x, int y, int tileSize, int rota);

        static std::vector<char> GetBlockData(Type type, int rota);
        static std::vector<sf::Vector2i> GetCollisionTiles(Type type, int rota);

        static sf::Color GetColor(Type type);

    private:

    };
}

#endif //CS3A_TETRIS_BLOCK_H
