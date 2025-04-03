//
// Created by Tiffanie Lim on 6/3/24.
//

/// The Block class represents the individual tetromino shapes.
/// Each block type corresponds to a Tetris shape (I, O, T, S, Z, J, L).

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
        //draws a block of a given type at a specific position, size, and rotation
        static void Render(sf::RenderTarget& window, Type type, int x, int y, int tileSize, int rota);

        //returns the raw block layout data (as characters) for a given type and rotation
        static std::vector<char> GetBlockData(Type type, int rota);

        //returns the positions of tiles occupied by the block, used for collision checking
        static std::vector<sf::Vector2i> GetCollisionTiles(Type type, int rota);

        static sf::Color GetColor(Type type);

    private:

    };
}

#endif //CS3A_TETRIS_BLOCK_H
