//
// Created by Tiffanie Lim on 6/3/24.
//

///Represents the game board where tetrominoes fall and interact
///Handles spawning, moving, placing blocks, clearing lines, and rendering

#ifndef CS3A_TETRIS_FIELD_H
#define CS3A_TETRIS_FIELD_H
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <queue>
#include "Settings.h"
#include "Block.h"

namespace te
{
    class Field
    {
    public:
        Field(int tileSize);

        void SetPosition(int x, int y); //set board's screen position
        void Spawn(Block::Type t);
        void PlaceBlock();
        inline std::queue<Block::Type> GetQueue() { return queue; } //get upcoming blocks
        void Reset(); //clear map and refill block queue

        void OnEvent(sf::Event e); //handle keyboard input
        void OnUpdate(); //advance block downward, place it if needed
        void Render(sf::RenderTarget& wnd); //draw current state of board

    private:
        sf::VertexBuffer grid;
        sf::RenderStates position;
        int translateX, translateY, tileSize;
        Block::Type map[FIELD_WIDTH][FIELD_HEIGHT];

        std::queue<Block::Type> queue;
        Block::Type current;
        int currentRotation = 0;
        int blockOffset = 3;
        int blockHeight = -4;

        bool checkLeftBounds();
        bool checkRightBounds();
        inline Block::Type getRandomBlock() { return (Block::Type)(rand() % Block::Type::Count); }
    };
}

#endif //CS3A_TETRIS_FIELD_H
